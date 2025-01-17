#include <algorithm>
#include <vector>

#include "algo.h"
#include "parlay/primitives.h"

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

SeqNestedVs SeqAlgo::createTestGraph() {
  auto getNeighbours = [&](int v){
    auto [x,y,z] = SeqAlgo::getCoord(v);
    SeqVs res;
    if (x > 0) res.push_back(getNum({x - 1, y, z}));
    if (y > 0) res.push_back(getNum({x, y - 1, z}));
    if (z > 0) res.push_back(getNum({x, y, z - 1}));
    if (z < SIDE_MINUS_ONE) res.push_back(getNum({x, y, z + 1}));
    if (y < SIDE_MINUS_ONE) res.push_back(getNum({x, y + 1, z}));
    if (x < SIDE_MINUS_ONE) res.push_back(getNum({x + 1, y, z}));
    return res;
  };

  SeqNestedVs res;
  res.reserve(SIDE3);
  for(int i = 0; i<SIDE3; i++) {
    res.push_back(getNeighbours(i));
  }
  return res;
}

SeqNestedVs SeqAlgo::bfs(SeqNestedVs gr) {
  std::vector<bool> visited(SIDE3, false);
  SeqNestedVs res{};
  //                 vertex level
  std::queue<std::pair<int, int>> queue;
  // std::vector<bool> visited(SIDE3, false);
  // std::unordered_set<int> visited;

  int maxDepth = -1;
  visited[0] = true;
  // visited.insert(0);
  queue.push({0, 0});

  while (!queue.empty()) {
    int currentVertex = queue.front().first;
    int depth = queue.front().second;
    if(depth > maxDepth) {
      depth++;
      res.push_back({});
    }
    res.back().push_back(currentVertex);
    queue.pop();

    for (int neighbor : gr[currentVertex]) {
      if (!visited[neighbor] /*visited.find(neighbor) == visited.end()*/) {
        // res[neighbor] = depth + 1;
        //visited.insert(neighbor);
        visited[neighbor] = true;
        queue.push({neighbor, depth + 1});
      }
    }
  }
  return res;
}