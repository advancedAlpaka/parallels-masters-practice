#include <algorithm>
#include <vector>

#include "algo.h"

int partition(SeqVec& v, int l, int r) {
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

void _quicksort(SeqVec& v, int l, int r) {
  if (l < r) {
    int q = partition(v, l, r);
    _quicksort(v, l, q);
    _quicksort(v, q + 1, r);
  }
}

void SeqAlgo::quicksort(SeqVec& v) { _quicksort(v, 0, v.size() - 1); }

SeqVec SeqAlgo::createTestVec(int n) {
  std::mt19937 gen;

  std::vector<long> data;
  std::generate_n(std::back_insert_iterator(data), n, std::ref(gen));
  return data;
}