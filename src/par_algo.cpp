#include <parlay/primitives.h>
#include <parlay/sequence.h>
#include <tuple>

#include "algo.h"

template <typename T>
std::pair<parlay::sequence<T>, parlay::sequence<T>> partition(
    const parlay::sequence<T>& arr, T pivot) {
  parlay::sequence<T> less, greater;
  less.reserve(arr.size());
  greater.reserve(arr.size());

  parlay::parallel_for(0, arr.size(), [&](size_t i) {
    if (arr[i] < pivot) {
      less.push_back(arr[i]);
    } else if (arr[i] > pivot) {
      greater.push_back(arr[i]);
    }
  });

  return {less, greater};
}

template <typename T>
void parallel_quicksort(parlay::sequence<T>& arr) {
  if (arr.size() <= 1) return;
  if (arr.size() < 10000) {
    _quicksort(arr.begin(), arr.end());
    return;
  }

  size_t prev_size = arr.size();
  T pivot = arr[arr.size() / 2];

  auto [less, greater] = partition(arr, pivot);

  parlay::par_do([&]() { parallel_quicksort(less); },
                 [&]() { parallel_quicksort(greater); });

  arr.clear();
  arr.insert(arr.end(), less.begin(), less.end());
  arr.insert(arr.end(), prev_size - less.size() - greater.size(), pivot);
  arr.insert(arr.end(), greater.begin(), greater.end());
}

void ParAlgo::quicksort(ParVec& v) { parallel_quicksort(v); }

ParVec ParAlgo::createTestVec(int n) {
  parlay::random_generator gen;
  std::uniform_int_distribution<long> dis(LONG_MIN, LONG_MAX);

  ParVec data(n);
  parlay::parallel_for(0, n, [&](long i) {
    auto r = gen[i];
    data[i] = dis(r);
  });

  return data;
}

// |----------------------|
// | Breadth-first search |
// |----------------------|

ParVs ParAlgo::getNeighbors(int vertex) {
  int x = vertex / SIDE2;
  int y = (vertex / SIDE) % SIDE;
  int z = vertex % SIDE;
  auto xyz = getMyCoord(vertex);
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
      std::cout << "{" << std::get<0>(xyz) << " " << std::get<1>(xyz) << " " << std::get<2>(xyz) << "} ";
    }
    std::cout << std::endl;
  }*/
  return frontiers;
}