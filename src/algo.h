#include <parlay/primitives.h>
#include <parlay/sequence.h>

#include <vector>

const int SIDE = 500;
const int SIDE_MINUS_ONE = SIDE - 1;
const int SIDE2 = SIDE * SIDE;
const int SIDE3 = SIDE2 * SIDE;

template <class Vec, class GrVertexes, class BFSGrVertexes>
struct Algo {
  static int getMyNum(int x, int y, int z) { return SIDE2 * x + SIDE * y + z; };

  static std::tuple<int, int, int> getMyCoord(int num) {
    return {num / SIDE2, (num / SIDE) % SIDE, num % SIDE};
  }

  virtual Vec createTestVec(int n) = 0;
  virtual GrVertexes getNeighbors(int vertex) = 0;

  virtual void quicksort(Vec& v) = 0;
  virtual BFSGrVertexes bfs() = 0;
};

using SeqVec = std::vector<long>;
using SeqVs = std::vector<int>;

struct SeqAlgo : Algo<SeqVec, SeqVs, SeqVs> {
  using Vec = SeqVec;

  SeqVec createTestVec(int n);
  void quicksort(SeqVec& v);

  SeqVs getNeighbors(int vertex);
  SeqVs bfs();
};

using ParVec = parlay::sequence<long>;
using ParVs = parlay::sequence<int>;
using ParNestedVs = parlay::sequence<ParVs>;

struct ParAlgo : Algo<ParVec, ParVs, ParNestedVs> {
  using Vec = ParVec;

  ParVec createTestVec(int n);
  void quicksort(ParVec& v);
  ParVs getNeighbors(int vertex);
  ParNestedVs bfs();
};

template <typename Iterator>
Iterator partition(Iterator first, Iterator last) {
  Iterator i = first;
  Iterator j = last - 1;
  auto pivot = *(i + (j - i) / 2);
  while (i <= j) {
    while (*i < pivot) i++;
    while (pivot < *j) j--;
    if (i >= j) break;
    std::iter_swap(i++, j--);
  }
  return j;
}

template <typename Iterator>
void _quicksort(Iterator first, Iterator last) {
  if (last - first > 1) {
    Iterator q = partition(first, last);
    _quicksort(first, q);
    _quicksort(q + 1, last);
  }
}