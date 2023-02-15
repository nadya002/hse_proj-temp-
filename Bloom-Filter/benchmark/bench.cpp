#include <benchmark/benchmark.h>
#include <Bloom_filt.h>

int fun(BloomFilter<int> &filt, int n) {
    for (int i = 0; i < n; i++) {
        filt.insert(i);
    }
    return 0;
}

void IntToString(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        BloomFilter<int> filt(state.range(0));
        state.ResumeTiming();
        //benchmark::DoNotOptimize(
        fun(filt, state.range(0));
        //);
    }
}

size_t N = 1e5;
BENCHMARK(IntToString)->Arg(N);


BENCHMARK_MAIN();