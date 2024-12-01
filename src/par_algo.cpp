#include "algo.h"

template <typename T>
std::pair<parlay::sequence<T>, parlay::sequence<T>> partition(const parlay::sequence<T>& arr, T pivot) {
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

    T pivot = arr[arr.size() / 2];

    auto [less, greater] = partition(arr, pivot);

    parlay::par_do(
        [&]() { parallel_quicksort(less); },
        [&]() { parallel_quicksort(greater); }
    );

    arr.clear();
    arr.insert(arr.end(), less.begin(), less.end());
    arr.insert(arr.end(), greater.begin(), greater.end());
}

void ParAlgo::quicksort(ParVec& v) {
  parallel_quicksort(v);
}

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
