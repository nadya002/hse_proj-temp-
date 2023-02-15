#include <benchmark/benchmark.h>
#include <cuckoofilter.h>

using cuckoofilter::CuckooFilter;

int fun(CuckooFilter<int, 12> &filt, int n) {
    for (int i = 0; i < n; i++) {
        filt.Add(i);
    }
    return 0;
}

void IntToString(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        CuckooFilter<int, 12> filt(state.range(0));
        state.ResumeTiming();
        //benchmark::DoNotOptimize(
        fun(filt, state.range(0));
        //);
    }
}

size_t N = 1e5;
BENCHMARK(IntToString)->Arg(N);


BENCHMARK_MAIN();