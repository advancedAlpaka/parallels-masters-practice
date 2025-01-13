#include <__format/format_functions.h>
#include <parlay/primitives.h>
#include <parlay/sequence.h>

#include <cassert>
#include <iostream>
#include <tuple>
#include <utility>

#include "algo.h"
#include "parlay/parallel.h"
#include "parlay/range.h"
#include "parlay/slice.h"

template <typename Iterator>
void insertion_sort(Iterator begin, Iterator end) {
    using T = typename std::iterator_traits<Iterator>::value_type;
    
    if (begin == end) return;
    
    for (Iterator i = begin + 1; i != end; ++i) {
        T key = std::move(*i);
        
        Iterator j = std::upper_bound(begin, i, key);
        
        for (Iterator k = i; k != j; --k) {
            *k = std::move(*(k - 1));
        }
        
        *j = std::move(key);
    }
}

const std::pair<long, long> & leftInd = {1, 0}, &rightInd = {0, 1},
                            &pivotInd = {0, 0};

const auto monoidSumPair = parlay::make_monoid(
                [](std::pair<long, long> p1, std::pair<long, long> p2) {
                  return std::make_pair(p1.first + p2.first,
                                        p1.second + p2.second);
                },
                pivotInd);

template <typename T>
using Slice = parlay::slice<T*, T*>;

template <typename T>
void parallel_quicksort(Slice<T> arr, Slice<T> out) {
  long n = arr.size();
  if(n <= SMALL_BORDER) {
    parlay::copy(arr, out);
    insertion_sort(out.begin(), out.end());
    return;
  }

  if (n < BORDER) {
    parlay::copy(arr, out);
    _quicksort(out.begin(), out.end());
    return;
  }

  auto candidatePivots = parlay::tabulate(PIVOTS_SELECTION_SIZE, [&](long i) {
    return arr[i * (n-1) / (PIVOTS_SELECTION_SIZE-1)];
  });
  insertion_sort(candidatePivots.begin(), candidatePivots.end());
  auto pivot = candidatePivots[PIVOTS_MEDIAN];

  auto inds = parlay::map(arr, [&](T el) {
    return (el < pivot) ? leftInd : ((el == pivot) ? pivotInd : rightInd);
  }, BLOCK_SIZE);

  auto [lCount, gCount] = parlay::scan_inplace(inds, monoidSumPair);

  parlay::sequence<T> less, greater;
  less.reserve(lCount);
  greater.reserve(gCount);
  parlay::parallel_for(0, n, [&](long i) {
    if (arr[i] < pivot) {
      less[inds[i].first] = arr[i];
    } else if (arr[i] > pivot) {
      greater[inds[i].second] = arr[i];
    }
  }, BLOCK_SIZE);

  parlay::parallel_for(lCount, n - gCount, [&](long i) { 
    out[i] = pivot;
  }, BLOCK_SIZE);
  
  if (lCount > 0 && gCount > 0) {
    parlay::par_do(
      [&]() { parallel_quicksort(less.cut(0, lCount), out.cut(0, lCount)); },
      [&]() { parallel_quicksort(greater.cut(0, gCount), out.cut(n - gCount, n)); }
    );
  } else if (lCount > 0) {
    parallel_quicksort(less.cut(0, lCount), out.cut(0, lCount));
  } else if (gCount > 0) {
    parallel_quicksort(greater.cut(0, gCount), out.cut(n - gCount, n));
  }
}

ParVec ParAlgo::quicksort(ParVec& v) {
  int n = v.size();
  ParVec res(n);
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

ParVs ParAlgo::getNeighbors(int vertex) {
  auto [x, y, z] = getMyCoord(vertex);
  ParVs res;
  res.reserve(6);
  if (x > 0) res.push_back(getMyNum(x - 1, y, z));
  if (y > 0) res.push_back(getMyNum(x, y - 1, z));
  if (z > 0) res.push_back(getMyNum(x, y, z - 1));
  if (z < SIDE_MINUS_ONE) res.push_back(getMyNum(x, y, z + 1));
  if (y < SIDE_MINUS_ONE) res.push_back(getMyNum(x, y + 1, z));
  if (x < SIDE_MINUS_ONE) res.push_back(getMyNum(x + 1, y, z));
  return res;
}

ParNestedVs ParAlgo::bfs() {
  parlay::sequence<std::atomic_bool> visited(SIDE3);
  //      parlay::tabulate<std::atomic_bool>(125000000,
  //                                         [](int i) { return false; });
  visited[0].store(true);
  parlay::sequence<ParVs> frontiers;
  ParVs pastFrontier{0};
  while (!pastFrontier.empty()) {
    frontiers.push_back(pastFrontier);
    ParVs edgesToNextFrontier = parlay::flatten(
        parlay::map(pastFrontier, [&](int i) { return getNeighbors(i); }));
    pastFrontier = parlay::filter(edgesToNextFrontier, [&](int i) {
      bool expected = false;
      return visited[i].compare_exchange_strong(expected, true);
    });
  }
  /*for(auto f: frontiers) {
    for(auto v : f) {
      auto xyz = getCoord(v);
      std::cout << "{" << std::get<0>(xyz) << " " << std::get<1>(xyz) << " " <<
  std::get<2>(xyz) << "} ";
    }
    std::cout << std::endl;
  }*/
  return frontiers;
}