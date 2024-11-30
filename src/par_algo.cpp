#include "algo.h"

int partition(ParVec& v, int l, int r) {
  long middle = v[(l + r) / 2];
  int i = l;
  int j = r;
  while (i <= j) {
    while (v.at(i) < middle) i++;
    while (v.at(j) > middle) j--;
    if (i >= j) break;
    std::iter_swap(v.begin() + i++, v.begin() + j--);
  }
  return j;
}

void seq_quicksort(ParVec& v, int l, int r) {
  if (l < r) {
    int q = partition(v, l, r);
    seq_quicksort(v, l, q);
    seq_quicksort(v, q + 1, r);
  }
}

void par_quicksort(ParVec& v, int l, int r) {
  if (l < r) {
    if (r - l < 1000) {
      seq_quicksort(v, l, r);
    } else {
      int q = partition(v, l, r);
      parlay::par_do([&]() { par_quicksort(v, l, q); },
                     [&]() { par_quicksort(v, q + 1, r); });
    }
  }
}

void ParAlgo::quicksort(ParVec& v) { par_quicksort(v, 0, v.size() - 1); }

ParVec ParAlgo::createTestVec(int n) {
  parlay::random_generator gen;
  std::uniform_int_distribution<long> dis(LONG_MIN, LONG_MAX);

  // generate random long values
  auto data = parlay::tabulate(n, [&](long i) {
    auto r = gen[i];
    return dis(r);
  });

  return data;
}