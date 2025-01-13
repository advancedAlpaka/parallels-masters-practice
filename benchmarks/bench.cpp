#include <benchmark/benchmark.h>
#include <cassert>
#include <functional>
#include "../src/algo.h"
#include "parlay/primitives.h"

template<typename Container>
std::size_t compute_hash(const Container& container) {
    std::size_t seed = container.size();
    for (const auto& element : container) {
        seed ^= std::hash<typename Container::value_type>{}(element) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    return seed;
}

template <class TestingAlgo>
class QuicksortFixture : public benchmark::Fixture {
 protected:
  TestingAlgo algo = TestingAlgo();
  TestingAlgo::Vec v;
  TestingAlgo::Vec res;

 public:
  void SetUp(::benchmark::State& state) { 
    state.counters["PARLAY_NUM_THREADS"] = std::stoi(std::getenv("PARLAY_NUM_THREADS"));
    v = algo.createTestVec();
    state.counters["HASH_ARRAY"] = compute_hash(v);
  }

  void TearDown(::benchmark::State& state) {
    state.counters["IS_GOOD"] = parlay::equal(parlay::sort(v), res); 
    res.clear();
    v.clear();
  }
};

BENCHMARK_TEMPLATE_DEFINE_F(QuicksortFixture, SeqQuicksortTest, SeqAlgo)
(benchmark::State& st) {
  for (auto _ : st) {
    res = algo.quicksort(v);
  }
};

BENCHMARK_REGISTER_F(QuicksortFixture, SeqQuicksortTest)->Repetitions(5);

BENCHMARK_TEMPLATE_DEFINE_F(QuicksortFixture, ParQuicksortTest, ParAlgo)
(benchmark::State& st) {
  for (auto _ : st) {
    res = algo.quicksort(v);
  }
};

BENCHMARK_REGISTER_F(QuicksortFixture, ParQuicksortTest)->Repetitions(5);

template <class TestingAlgo>
class BreadthFirstSearchFixture : public benchmark::Fixture {
 protected:
  TestingAlgo algo = TestingAlgo();
  
 public:
  void SetUp(::benchmark::State& state) {
    state.counters["PARLAY_NUM_THREADS"] = std::stoi(std::getenv("PARLAY_NUM_THREADS"));
  }

  void TearDown(::benchmark::State& state) {}
};

BENCHMARK_TEMPLATE_DEFINE_F(BreadthFirstSearchFixture, SeqBreadthFirstSearchTest, SeqAlgo)
(benchmark::State& st) {
  for (auto _ : st) {
    algo.bfs();
  }
};

//BENCHMARK_REGISTER_F(BreadthFirstSearchFixture, SeqBreadthFirstSearchTest)->Repetitions(5);

BENCHMARK_TEMPLATE_DEFINE_F(BreadthFirstSearchFixture, ParBreadthFirstSearchTest, ParAlgo)
(benchmark::State& st) {
  for (auto _ : st) {
    algo.bfs();
  }
};

//BENCHMARK_REGISTER_F(BreadthFirstSearchFixture, ParBreadthFirstSearchTest)->Repetitions(5);

BENCHMARK_MAIN();