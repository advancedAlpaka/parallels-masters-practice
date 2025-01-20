#include <algorithm>
#include <iostream>
#include <vector>

#include "algo.h"
#include "parlay/internal/get_time.h"
#include "parlay/primitives.h"
#include "parlay/sequence.h"

int main() {
  /*parlay::sequence<int> v{1,2,3}, a{4,5,6};

  parlay::filter_into_uninitialized(a, v, [](int e){ return e % 2 == 1; });

  for(int i= 0; i<v.size(); i++) {
      std::cout << v[i] << " ";
  }
  parlay::sequence<int> v = parlay::tabulate(101, [&](int i){ return i; });
  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(v.begin(), v.end(), g);

  for(int i= 0; i<101; i++) {
      std::cout << v[i] << " ";
  }
  std::cout << "\n";
  bool isGood = true;
  for(int i= 0; i<101; i++) {
      auto e = modified_quicksort_nth_element(v.begin(), v.end(), i);
      isGood = *e == i;
      std::cout << *e << " ";
  }
  std::cout << "\n" << isGood;*/

  /*const int RUNS = 1000;
  parlay::sequence<long> vec;
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine gen(seed);
  std::uniform_int_distribution<long> dis(0, SIZE);
  double seq_time = 0, par_time = 0;

  for (int run = 0; run < RUNS; run++) {
      vec = parlay::tabulate(31, [&](long i) { return dis(gen); });
      auto t1 = std::chrono::high_resolution_clock::now();
      insertion_sort(vec.begin(), vec.end());
      auto t2 = std::chrono::high_resolution_clock::now();
      seq_time += std::chrono::duration<double>(t2-t1).count();

      vec = parlay::tabulate(31, [&](long i) { return dis(gen); });
      t1 = std::chrono::high_resolution_clock::now();
      _quicksort(vec.begin(), vec.end());
      t2 = std::chrono::high_resolution_clock::now();
      par_time += std::chrono::duration<double>(t2-t1).count();
  }

  std::cout << "Average Insertion Sort: " << seq_time/RUNS << "s\n";
  std::cout << "Average Quick Sort: " << par_time/RUNS << "s\n";
  std::cout << "Speedup: " << seq_time/par_time << "x\n";
  */

  const int RUNS = 5;
  SeqAlgo seq = SeqAlgo();
  ParAlgo par = ParAlgo();

  std::cout << "--------------QuickSort----------------\n";
  double seq_time = 0, par_time = 0;

  for (int run = 0; run < RUNS; run++) {
    std::cout << "run " << run << " seq\n";
    SeqVec seqData = seq.createTestVec();
    auto t1 = std::chrono::high_resolution_clock::now();
    auto seq_result = seq.quicksort(seqData);
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "status " << parlay::is_sorted(seq_result) << "\n";
    seq_time += std::chrono::duration<double>(t2 - t1).count();

    std::cout << "run " << run << " par\n";
    ParVec parData = par.createTestVec();
    t1 = std::chrono::high_resolution_clock::now();
    auto par_result = par.quicksort(parData);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "status " << parlay::is_sorted(par_result) << "\n";
    par_time += std::chrono::duration<double>(t2 - t1).count();
  }

  std::cout << "Average Sequential Time: " << seq_time / RUNS << "s\n";
  std::cout << "Average Parallel Time: " << par_time / RUNS << "s\n";
  std::cout << "Speedup: " << seq_time / par_time << "x\n";
  std::cout << "--------------BFS----------------\n";
  seq_time = 0;
  par_time = 0;

  auto seqGr = seq.createTestGraph();
  auto parGr = par.createTestGraph();

  for (int run = 0; run < RUNS; run++) {
    std::cout << "run " << run << " seq\n";
    auto t1 = std::chrono::high_resolution_clock::now();
    auto seq_result = seq.bfs(seqGr);
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "status " << seq.checkBFS(seq_result) << "\n";
    seq_time += std::chrono::duration<double>(t2 - t1).count();

    std::cout << "run " << run << " par\n";
    t1 = std::chrono::high_resolution_clock::now();
    auto par_result = par.bfs(parGr);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "status " << par.checkBFS(par_result) << "\n";
    par_time += std::chrono::duration<double>(t2 - t1).count();
  }

  std::cout << "Average Sequential Time: " << seq_time / RUNS << "s\n";
  std::cout << "Average Parallel Time: " << par_time / RUNS << "s\n";
  std::cout << "Speedup: " << seq_time / par_time << "x\n";

  return 0;
}