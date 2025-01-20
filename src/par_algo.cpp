#include <__atomic/aliases.h>
#include <parlay/primitives.h>
#include <parlay/sequence.h>

#include <cassert>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <tuple>
#include <utility>

#include "algo.h"
#include "parlay/delayed.h"
#include "parlay/parallel.h"
#include "parlay/range.h"
#include "parlay/slice.h"

const std::pair<long, long>&leftInd = {1, 0}, &rightInd = {0, 1},
                      &pivotInd = {0, 0};

const auto monoidSumPair = parlay::make_monoid(
    [](std::pair<long, long> p1, std::pair<long, long> p2) {
      return std::make_pair(p1.first + p2.first, p1.second + p2.second);
    },
    pivotInd);

template <typename T>
using Slice = parlay::slice<T*, T*>;

template <typename T>
void parallel_quicksort(Slice<T> arr, Slice<T> out) {
  long n = arr.size();

  if (n < BORDER) {
    parlay::copy(arr, out);
    _quicksort(out.begin(), out.end());
    return;
  }

  auto candidatePivots = parlay::tabulate(
      PIVOTS_SELECTION_SIZE,
      [&](long i) { return arr[i * (n - 1) / PIVOTS_SELECTION_SIZE]; });

  auto pivot = *(modified_quicksort_nth_element(
      candidatePivots.begin(), candidatePivots.end(), PIVOTS_MEDIAN));

  auto inds = parlay::map(
      arr,
      [&](T el) {
        return (el < pivot) ? leftInd : ((el > pivot) ? rightInd : pivotInd);
      },
      BLOCK_SIZE);

  auto [lCount, gCount] = parlay::scan_inplace(inds, monoidSumPair);

  parlay::sequence<T> less, greater;
  less.reserve(lCount);
  greater.reserve(gCount);
  parlay::parallel_for(
      0, n,
      [&](long i) {
        if (arr[i] < pivot) {
          less[inds[i].first] = arr[i];
        } else if (arr[i] > pivot) {
          greater[inds[i].second] = arr[i];
        }
      });

  for (int i = lCount; i < n - gCount; i++) out[i] = pivot;

  parlay::par_do(
      [&]() { parallel_quicksort(less.cut(0, lCount), out.cut(0, lCount)); },
      [&]() {
        parallel_quicksort(greater.cut(0, gCount), out.cut(n - gCount, n));
      });
}

ParVec ParAlgo::quicksort(ParVec& v) {
  int n = v.size();
  ParVec res(n);
  //res.reserve(n);
  parallel_quicksort(v.cut(0, n), res.cut(0, n));
  return res;
}

ParVec ParAlgo::createTestVec() {
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine gen(seed);
  std::uniform_int_distribution<long> dis(0, SIZE);
  return parlay::tabulate(SIZE, [&](long i) { return dis(gen); });
}

// |----------------------|
// | Breadth-first search |
// |----------------------|

ParNestedVs ParAlgo::createTestGraph() {
  auto getNeighbours = [&](int vertex) {
    auto [x, y, z] = getCoord(vertex);
    ParVs res;
    res.reserve(6);
    if (x > 0) res.push_back(getNum({x - 1, y, z}));
    if (y > 0) res.push_back(getNum({x, y - 1, z}));
    if (z > 0) res.push_back(getNum({x, y, z - 1}));
    if (z < SIDE_MINUS_ONE) res.push_back(getNum({x, y, z + 1}));
    if (y < SIDE_MINUS_ONE) res.push_back(getNum({x, y + 1, z}));
    if (x < SIDE_MINUS_ONE) res.push_back(getNum({x + 1, y, z}));
    return res;
  };

  return parlay::tabulate(SIDE3, [&](int i) { return getNeighbours(i); });
}

ParVs ParAlgo::bfs(ParNestedVs& gr) {
  int n = gr.size();
  parlay::sequence<std::atomic_int> parent = parlay::tabulate<std::atomic_int>(n, [&](int){ return -1;} );
  parent[0] = 0;

  auto edgeFun = [&](std::pair<int, int> edgeVU) -> std::optional<int> {
    auto [v, u] = edgeVU;
    int expect = -1;
    if( parent[u] == -1 && parent[u].compare_exchange_strong(expect, v)) 
      return std::make_optional(u);
    else
      return std::nullopt;
  };

  ParVs frontier(1, 0);  // 1 < size < ~280000
  while (frontier.size() > 0) {
    auto rawOutEdges = parlay::delayed::map(frontier, [&](int v) { 
      return parlay::delayed_tabulate(gr[v].size(), [&, v](int uInd) {
        return std::make_pair(v, gr[v][uInd]);
      });
    });
    auto outEdges = parlay::delayed::flatten(rawOutEdges);

    frontier = parlay::delayed::to_sequence(
        parlay::delayed::map_maybe(outEdges, edgeFun));
  }

  return parlay::map(parent, [&](auto&& av){ return av.load();});
}

bool ParAlgo::checkBFS(ParVs &res) {
  return parlay::all_of(parlay::zip(parlay::iota(res.size()), res), [&](std::pair<int, int> indValue){
    auto [v, parent] = indValue;
    if(v == 0) return true;
    auto [xV, yV, zV] = getCoord(v);
    auto [xP, yP, zP] = getCoord(parent);
    return xP + yP + zP + 1 == xV + yV + zV;
  });
}