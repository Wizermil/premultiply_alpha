#include <cassert>
#include <iostream>
#include <benchmark/benchmark.h>

#include "benchmark.hpp"
#include "test.hpp"
#include "premultiply_alpha.hpp"

namespace pma {
    BENCHMARK(v1_plain);
#if !defined(NSIMD)
#    if defined(__i386__) || defined(__x86_64__)
    BENCHMARK(v1_simd_x86);
#    endif
#endif

    BENCHMARK(v2_plain);

#if !defined(NSIMD)
#    if defined(__i386__) || defined(__x86_64__)
    BENCHMARK(v3_simd_x86);
    BENCHMARK(v4_simd_x86);
#    endif
#endif
}

int main(int argc, char** argv) {
    ::benchmark::Initialize(&argc, argv);
    if (::benchmark::ReportUnrecognizedArguments(argc, argv))
        return 1;

    CHECK(v1::premultiply_alpha_plain);

#if !defined(NSIMD)
#    if defined(__i386__) || defined(__x86_64__)
    CHECK(v1::premultiply_alpha_simd_x86);
#    endif
#endif

    CHECK(v2::premultiply_alpha_plain);

#if !defined(NSIMD)
#    if defined(__i386__) || defined(__x86_64__)
    CHECK(v3::premultiply_alpha_simd_x86);

    CHECK(v4::premultiply_alpha_simd_x86);
#    endif
#endif

    ::benchmark::RunSpecifiedBenchmarks();
}
