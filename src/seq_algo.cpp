#include <algorithm>
#include <vector>

#include "algo.h"

void SeqAlgo::quicksort(SeqVec& v) { _quicksort(v.begin(), v.end()); }

SeqVec SeqAlgo::createTestVec(int n) {
  std::mt19937 gen;
  std::uniform_int_distribution<long> dis(0, n);

  std::vector<long> data(n);
  std::generate(data.begin(), data.end(), [&]() { return dis(gen); });
  return data;
}

// 500^3 = 125_000_000
SeqVs SeqAlgo::getNeighbors(int vertex) {
  int x = vertex / SIDE2;
  int y = (vertex / SIDE) % SIDE;
  int z = vertex % SIDE;
  SeqVs res;
  res.reserve(6);
  if (x > 0) res.push_back(getMyNum(x - 1, y, z));
  if (y > 0) res.push_back(getMyNum(x, y - 1, z));
  if (z > 0) res.push_back(getMyNum(x, y, z - 1));
  if (z < SIDE_MINUS_ONE) res.push_back(getMyNum(x, y, z + 1));
  if (y < SIDE_MINUS_ONE) res.push_back(getMyNum(x, y + 1, z));
  if (x < SIDE_MINUS_ONE) res.push_back(getMyNum(x + 1, y, z));
  return res;
}

SeqVs SeqAlgo::bfs() {
  SeqVs res;
  //res.reserve(SIDE3);
  std::queue<int> queue;
  std::vector<bool> visited(SIDE3, false);
  //std::unordered_set<int> visited;

  visited[0] = true;
  //visited.insert(0);
  queue.push(0);

  while (!queue.empty()) {
    int currentVertex = queue.front();
    res.push_back(currentVertex);
    queue.pop();

    for (int neighbor : SeqAlgo::getNeighbors(currentVertex)) {
      if (!visited[neighbor] /*visited.find(neighbor) == visited.end()*/) {
        visited[neighbor] = true;
        //visited.insert(neighbor);
        queue.push(neighbor);
      }
    }
  }
  return res;
}