#include <benchmark/benchmark.h>
#include "../src/algo.h"

template <class TestingAlgo>
class QuicksortFixture : public benchmark::Fixture {
 protected:
  TestingAlgo algo = TestingAlgo();
  TestingAlgo::Vec v;

 public:
  void SetUp(::benchmark::State& state) { 
    state.counters["PARLAY_NUM_THREADS"] = std::stoi(std::getenv("PARLAY_NUM_THREADS"));
    v = algo.createTestVec(100000000);
  }

  void TearDown(::benchmark::State& state) {}
};

BENCHMARK_TEMPLATE_DEFINE_F(QuicksortFixture, SeqQuicksortTest, SeqAlgo)
(benchmark::State& st) {
  for (auto _ : st) {
    algo.quicksort(v);
  }
};

//BENCHMARK_REGISTER_F(QuicksortFixture, SeqQuicksortTest)->Repetitions(5);

BENCHMARK_TEMPLATE_DEFINE_F(QuicksortFixture, ParQuicksortTest, ParAlgo)
(benchmark::State& st) {
  for (auto _ : st) {
    algo.quicksort(v);
  }
};

//BENCHMARK_REGISTER_F(QuicksortFixture, ParQuicksortTest)->Repetitions(5);

template <class TestingAlgo>
class BreadthFirstSearchFixture : public benchmark::Fixture {
 protected:
  TestingAlgo algo = TestingAlgo();
  
 public:
  void SetUp(::benchmark::State& state) {
    //state.counters["PARLAY_NUM_THREADS"] = std::stoi(std::getenv("PARLAY_NUM_THREADS"));
  }

  void TearDown(::benchmark::State& state) {}
};

BENCHMARK_TEMPLATE_DEFINE_F(BreadthFirstSearchFixture, SeqBreadthFirstSearchTest, SeqAlgo)
(benchmark::State& st) {
  for (auto _ : st) {
    algo.bfs();
  }
};

BENCHMARK_REGISTER_F(BreadthFirstSearchFixture, SeqBreadthFirstSearchTest)->Repetitions(5);

BENCHMARK_TEMPLATE_DEFINE_F(BreadthFirstSearchFixture, ParBreadthFirstSearchTest, ParAlgo)
(benchmark::State& st) {
  for (auto _ : st) {
    algo.bfs();
  }
};

BENCHMARK_REGISTER_F(BreadthFirstSearchFixture, ParBreadthFirstSearchTest)->Repetitions(5);

BENCHMARK_MAIN();