#include <iostream>
#include <vector>

#include "algo.h"

int main() {
  std::cout << "Hello World!" << std::endl;
  parlay::sequence<long> ex{1, 5, 43, 4, 6, 8, 3, 4, 5, 7, 89, 54, 3, 5, 79};
  auto a = ParAlgo();
  a.quicksort(ex);
  for (auto el : ex) std::cout << el << " ";
  std::cout << std::endl;
}