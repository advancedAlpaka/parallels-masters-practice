#include <parlay/primitives.h>
#include <parlay/sequence.h>

#include <vector>

template <class Vec, class Gr>
struct Algo {
  virtual Vec createTestVec(int n) = 0;
  // virtual Vec getNeihbours(int vertex) = 0;

  virtual void quicksort(Vec& v) = 0;
  // virtual Vec bfs() = 0;
};

using SeqVec = std::vector<long>;
using SeqGr = std::vector<SeqVec>;

struct SeqAlgo : Algo<SeqVec, SeqGr> {
  using Vec = SeqVec;

  SeqVec createTestVec(int n);
  void quicksort(SeqVec& v);
};

using ParVec = parlay::sequence<long>;
using ParGr = parlay::sequence<ParVec>;

struct ParAlgo : Algo<ParVec, ParGr> {
  using Vec = ParVec;

  ParVec createTestVec(int n);
  void quicksort(ParVec& v);
};

template <typename Iterator>  //  [              )
Iterator partition(Iterator first, Iterator last) {
  auto middle = *(first + (last - first - 1) / 2);
  Iterator i = first;
  Iterator j = last - 1;

  while (true) {
    while (*i < middle) ++i;
    while (*j > middle) --j;
    if (i >= j) break;
    std::iter_swap(i++, j--);
  }
  return j;
}

template <typename Iterator>
void _quicksort(Iterator first, Iterator last) {
  if (first < last - 1) {
    Iterator q = partition(first, last);
    _quicksort(first, q);
    _quicksort(q, last);
  }
}