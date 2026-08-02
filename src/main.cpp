#include <benchmark/benchmark.h>
#include <random>

#define MAT_THREAD_NUMS 16
#include "mat.hpp"

static void BM_MatMul(benchmark::State& state) {
    using T = float;

    int64_t p = state.range(0);
    int64_t q = state.range(1);
    int64_t s = state.range(2);

    std::normal_distribution<T> dist(0., 1.);

    mat<T> A(p, q, dist);
    mat<T> B(q, s, dist);

    for (auto _ : state) {
        mat<T> C = A * B;
        benchmark::DoNotOptimize(C.pData);
    }

    double flops = 2.0 * p * q * s;
    state.counters["GFLOPS"] = benchmark::Counter(flops / 1e9, benchmark::Counter::kIsRate);
}

BENCHMARK(BM_MatMul)
->Args({ 512, 512, 512 })
->Args({ 1024, 1024, 1024 })
->Args({ 2048, 2048, 2048 })
->Args({ 2312, 3431, 4343 });

BENCHMARK_MAIN();
