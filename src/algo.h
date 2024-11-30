#include <parlay/sequence.h>
#include <parlay/primitives.h>

#include <vector>

template <class Vec, class Gr>
struct Algo {
//  std::iostream log = std::basic_iostream("");
  
  virtual Vec createTestVec(int n) = 0;
  //virtual Vec getNeihbours(int vertex) = 0;

  virtual void quicksort(Vec& v) = 0;
  // virtual Vec bfs(Gr gr) = 0;
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