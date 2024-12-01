#include <algorithm>
#include <vector>

#include "algo.h"

void SeqAlgo::quicksort(SeqVec& v) { _quicksort(v.begin(), v.end()); }

SeqVec SeqAlgo::createTestVec(int n) {
  std::mt19937 gen;
  std::uniform_int_distribution<long> dis(LONG_MIN, LONG_MAX);

  std::vector<long> data(n);
  std::generate(data.begin(), data.end(), [&]() { return dis(gen); });
  return data;
}