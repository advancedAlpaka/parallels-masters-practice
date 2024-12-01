#include <iostream>
#include <vector>

#include "algo.h"

int main() {
  std::cout << "Hello World!" << std::endl;
  auto a1 = ParAlgo();
    parlay::sequence<long> ex1 = a1.createTestVec(100000000);
  a1.quicksort(ex1);
  //for (auto el : ex1) std::cout << el << " ";
  //std::cout << std::endl;
  auto a2 = SeqAlgo();
    std::vector<long> ex2 = a2.createTestVec(100000000);
  a2.quicksort(ex2);
  //for (auto el : ex2) std::cout << el << " ";
  //std::cout << std::endl;
}