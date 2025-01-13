#include <parlay/primitives.h>
#include <parlay/sequence.h>

#include <vector>

const int BLOCK_SIZE = 10000;
const int SMALL_BORDER = 32;
const int BORDER =  25000000;
const int SIZE =   100000000;
const int PIVOTS_SELECTION_SIZE = 257;
const int PIVOTS_MEDIAN = PIVOTS_SELECTION_SIZE / 2;
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

  virtual Vec createTestVec() = 0;
  virtual GrVertexes getNeighbors(int vertex) = 0;

  virtual Vec quicksort(Vec& v) = 0;
  virtual BFSGrVertexes bfs() = 0;
};

using SeqVec = std::vector<long>;
using SeqVs = std::vector<int>;

struct SeqAlgo : Algo<SeqVec, SeqVs, SeqVs> {
  using Vec = SeqVec;
  std::mt19937 gen;

  SeqVec createTestVec();
  SeqVec quicksort(SeqVec& v);

  SeqVs getNeighbors(int vertex);
  SeqVs bfs();
};

using ParVec = parlay::sequence<long>;
using ParVs = parlay::sequence<int>;
using ParNestedVs = parlay::sequence<ParVs>;

struct ParAlgo : Algo<ParVec, ParVs, ParNestedVs> {
  using Vec = ParVec;
  parlay::random_generator gen;

  ParVec createTestVec();
  ParVec quicksort(ParVec& v);
  ParVs getNeighbors(int vertex);
  ParNestedVs bfs();
};

template <typename Iterator>
//                 [               )
Iterator partition(Iterator first, Iterator last) {
  Iterator i = first;
  Iterator j = last - 1;
  auto pivot = *(first + (last - first) / 2);
  while (i <= j) {
    while (*i < pivot) i++;
    while (pivot < *j) j--;
    if (i >= j) break;
    std::iter_swap(i++, j--);
  }
  return i;
}

template <typename Iterator>
void _quicksort(Iterator first, Iterator last) {
  if (last - first > 1) {
    Iterator q = partition(first, last);
    _quicksort(first, q);
    _quicksort(q, last);
  }
}