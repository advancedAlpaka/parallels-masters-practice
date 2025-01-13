#include <algorithm>
#include <vector>

#include "algo.h"

SeqVec SeqAlgo::quicksort(SeqVec& v) {
  SeqVec res(v);
  _quicksort(res.begin(), res.end());
  return res;
}

SeqVec SeqAlgo::createTestVec() {
  std::uniform_int_distribution<long> dis(0, SIZE);

  std::vector<long> data(SIZE);
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
  SeqVs res(SIDE3, -1);
  res.reserve(SIDE3);
  std::queue<int> queue;
  // std::vector<bool> visited(SIDE3, false);
  // std::unordered_set<int> visited;

  res[0] = 0;
  // visited[0] = true;
  // visited.insert(0);
  queue.push(0);

  while (!queue.empty()) {
    int currentVertex = queue.front();
    int depth = res[currentVertex];
    queue.pop();

    for (int neighbor : SeqAlgo::getNeighbors(currentVertex)) {
      if (res[neighbor] == -1 /*visited.find(neighbor) == visited.end()*/) {
        res[neighbor] = depth + 1;
        // visited.insert(neighbor);
        queue.push(neighbor);
      }
    }
  }
  return res;
}