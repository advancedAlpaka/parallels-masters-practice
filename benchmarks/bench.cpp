#include <benchmark/benchmark.h>
#include "../src/algo.h"

template <class TestingAlgo>
class QuicksortFixture : public benchmark::Fixture {
 protected:
  TestingAlgo algo = TestingAlgo();
  TestingAlgo::Vec v;

 public:
  void SetUp(::benchmark::State& state) { 
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

BENCHMARK_REGISTER_F(QuicksortFixture, SeqQuicksortTest)->Repetitions(5);

BENCHMARK_TEMPLATE_DEFINE_F(QuicksortFixture, ParQuicksortTest, ParAlgo)
(benchmark::State& st) {
  for (auto _ : st) {
    algo.quicksort(v);
  }
};

BENCHMARK_REGISTER_F(QuicksortFixture, ParQuicksortTest)->Repetitions(5);

BENCHMARK_MAIN();
