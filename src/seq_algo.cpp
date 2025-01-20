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

SeqVs SeqAlgo::bfs(SeqNestedVs & gr) {
  const int n = gr.size();
    std::vector<int> parent(n, -1);  // -1 indicates unvisited vertex
    std::queue<int> q;
    
    // Start from vertex 0
    q.push(0);
    parent[0] = 0;  // root is its own parent
    
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        
        for (int neighbor : gr[current]) {
            if (parent[neighbor] == -1) {  // if unvisited
                parent[neighbor] = current;  // set parent
                q.push(neighbor);
            }
        }
    }
    
    return parent;
}

bool SeqAlgo::checkBFS(SeqVs &res) {
  return parlay::all_of(parlay::zip(parlay::iota(res.size()), res), [&](std::pair<int, int> indValue){
    auto [v, parent] = indValue;
    if(v == 0) return true;
    auto [xV, yV, zV] = getCoord(v);
    auto [xP, yP, zP] = getCoord(parent);
    return xP + yP + zP + 1 == xV + yV + zV;
  });
}