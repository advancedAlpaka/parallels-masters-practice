#include "algo.h"

template <typename Iterator>
void par_quicksort(Iterator l, Iterator r) {
  if (l < r) {
    if (r - l < 100000) {
      _quicksort(l, r);
    } else {
      Iterator q = partition(l, r);
      parlay::par_do([&]() { par_quicksort(l, q); },
                     [&]() { par_quicksort(q, r); });
    }
  }
}

void ParAlgo::quicksort(ParVec& v) { par_quicksort(v.begin(), v.end()); }

ParVec ParAlgo::createTestVec(int n) {
  parlay::random_generator gen;
  std::uniform_int_distribution<long> dis(LONG_MIN, LONG_MAX);

  ParVec data(n);
  parlay::parallel_for(0,n,[&](long i) {
    auto r = gen[i];
    data[i] = dis(r);
  }); 

  return data;
}