#include <parlay/primitives.h>
#include <parlay/sequence.h>

#include <vector>

const int SIZE = 100000000;
const int BORDER =  1 + SIZE / 4;
const int SMALL_BORDER = 32;
const int PIVOTS_SELECTION_SIZE = 101;
const int PIVOTS_MEDIAN = PIVOTS_SELECTION_SIZE / 2;
const int PIVOT_BLOCK_SIZE = PIVOTS_SELECTION_SIZE * 0.26;
const int BLOCK_SIZE = BORDER;

const int GRAPH_BLOCK_SIZE = 1000;
const int SIDE = 500;
const int SIDE_MINUS_ONE = SIDE - 1;
const int SIDE2 = SIDE * SIDE;
const int SIDE3 = SIDE2 * SIDE;

template <class Vec, class GrVertexes, class TreeVs>
struct Algo {
  using _Vxs = GrVertexes;
  using _Tree = TreeVs;

  static int getNum(std::tuple<int, int, int> xyz) { 
    auto [x, y, z] = xyz;
    return SIDE2 * x + SIDE * y + z; };

  static std::tuple<int, int, int> getCoord(int num) {
    return {num / SIDE2, (num / SIDE) % SIDE, num % SIDE};
  }

  virtual Vec createTestVec() = 0;
  virtual GrVertexes createTestGraph() = 0;

  virtual Vec quicksort(Vec& v) = 0;
  virtual TreeVs bfs(GrVertexes &gr) = 0;
  virtual bool checkBFS(TreeVs& res) = 0;
};

using SeqVec = std::vector<long>;
using SeqVs = std::vector<int>;
using SeqNestedVs = std::vector<SeqVs>;

struct SeqAlgo : Algo<SeqVec, SeqNestedVs, SeqVs> {
  using Vec = SeqVec;
  std::mt19937 gen;

  SeqVec createTestVec();
  SeqVec quicksort(SeqVec& v);

  SeqNestedVs createTestGraph();
  SeqVs bfs(SeqNestedVs &gr);
  bool checkBFS(SeqVs& res);
};

using ParVec = parlay::sequence<long>;
using ParVs = parlay::sequence<int>;
using ParNestedVs = parlay::sequence<ParVs>;

struct ParAlgo : Algo<ParVec, ParNestedVs, ParVs> {
  using Vec = ParVec;
  parlay::random_generator gen;

  ParVec createTestVec();
  ParVec quicksort(ParVec& v);
  
  ParNestedVs createTestGraph();
  ParVs bfs(ParNestedVs &gr);
  bool checkBFS(ParVs& res);
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

template <typename Iterator>
Iterator modified_quicksort_nth_element(Iterator begin, Iterator end, int n) {
  if (end - begin > 1) {
    Iterator q = partition(begin, end);
    if(n < q - begin) {
      return modified_quicksort_nth_element(begin, q, n);
    } else if (n == q - begin) {
      return q;
    } else {
      return modified_quicksort_nth_element(q + 1, end, n - (q - begin) - 1);
    }
  }
  return begin;
}