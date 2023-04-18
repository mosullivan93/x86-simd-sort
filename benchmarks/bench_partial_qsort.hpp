#include "bench-qsort-common.h"

template <typename T>
static void avx512_partial_qsort(benchmark::State& state) {
    if (!cpu_has_avx512bw()) {
        state.SkipWithMessage("Requires AVX512 BW ISA");
    }
    if ((sizeof(T) == 2) && (!cpu_has_avx512_vbmi2())) {
        state.SkipWithMessage("Requires AVX512 VBMI2 ISA");
    }
    // Perform setup here
    int64_t K = state.range(0);
    size_t ARRSIZE = state.range(1);
    std::vector<T> arr;
    std::vector<T> arr_bkp;

    /* Initialize elements */
    arr = get_uniform_rand_array<T>(ARRSIZE);
    arr_bkp = arr;

    /* call avx512_partial_qsort */
    for (auto _ : state) {
        avx512_partial_qsort<T>(arr.data(), K, ARRSIZE);

        state.PauseTiming();
        arr = arr_bkp;
        state.ResumeTiming();
    }
}

template <typename T>
static void stdpartialsort(benchmark::State& state) {
    // Perform setup here
    int64_t K = state.range(0);
    size_t ARRSIZE = state.range(1);
    std::vector<T> arr;
    std::vector<T> arr_bkp;

    /* Initialize elements */
    arr = get_uniform_rand_array<T>(ARRSIZE);
    arr_bkp = arr;

    /* call std::partial_sort */
    for (auto _ : state) {
        std::partial_sort(arr.begin(), arr.begin() + K, arr.end());

        state.PauseTiming();
        arr = arr_bkp;
        state.ResumeTiming();
    }
}

// Register the function as a benchmark
BENCHMARK(avx512_partial_qsort<float>)->ArgsProduct({{5, 10, 100, 1000, 5000}, {10000, 100000, 250000}});
BENCHMARK(stdpartialsort<float>)->ArgsProduct({{5, 10, 100, 1000, 5000}, {10000, 100000, 250000}});
BENCHMARK(avx512_partial_qsort<uint32_t>)->ArgsProduct({{5, 10, 100, 1000, 5000}, {10000, 100000, 250000}});
BENCHMARK(stdpartialsort<uint32_t>)->ArgsProduct({{5, 10, 100, 1000, 5000}, {10000, 100000, 250000}});
BENCHMARK(avx512_partial_qsort<int32_t>)->ArgsProduct({{5, 10, 100, 1000, 5000}, {10000, 100000, 250000}});
BENCHMARK(stdpartialsort<int32_t>)->ArgsProduct({{5, 10, 100, 1000, 5000}, {10000, 100000, 250000}});

BENCHMARK(avx512_partial_qsort<double>)->ArgsProduct({{5, 10, 100, 1000, 5000}, {10000, 100000, 250000}});
BENCHMARK(stdpartialsort<double>)->ArgsProduct({{5, 10, 100, 1000, 5000}, {10000, 100000, 250000}});
BENCHMARK(avx512_partial_qsort<uint64_t>)->ArgsProduct({{5, 10, 100, 1000, 5000}, {10000, 100000, 250000}});
BENCHMARK(stdpartialsort<uint64_t>)->ArgsProduct({{5, 10, 100, 1000, 5000}, {10000, 100000, 250000}});
BENCHMARK(avx512_partial_qsort<int64_t>)->ArgsProduct({{5, 10, 100, 1000, 5000}, {10000, 100000, 250000}});
BENCHMARK(stdpartialsort<int64_t>)->ArgsProduct({{5, 10, 100, 1000, 5000}, {10000, 100000, 250000}});

//BENCHMARK(avx512_partial_qsort<float16>)->ArgsProduct({{5, 10, 100, 1000, 5000}, {10000, 100000, 250000}});
BENCHMARK(avx512_partial_qsort<uint16_t>)->ArgsProduct({{5, 10, 100, 1000, 5000}, {10000, 100000, 250000}});
BENCHMARK(stdpartialsort<uint16_t>)->ArgsProduct({{5, 10, 100, 1000, 5000}, {10000, 100000, 250000}});
BENCHMARK(avx512_partial_qsort<int16_t>)->ArgsProduct({{5, 10, 100, 1000, 5000}, {10000, 100000, 250000}});
BENCHMARK(stdpartialsort<int16_t>)->ArgsProduct({{5, 10, 100, 1000, 5000}, {10000, 100000, 250000}});
