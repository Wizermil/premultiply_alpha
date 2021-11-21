#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#include <benchmark/benchmark.h>
#pragma clang diagnostic pop

#include "benchmark.hpp"
#include "test.hpp"
#include "premultiply_alpha.hpp"

namespace pma {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wglobal-constructors"

    BENCHMARK(v1_plain);
    BENCHMARK(v2_plain);

#if !defined(NSIMD)
    BENCHMARK(v1_simd);
    BENCHMARK(v3_simd);
    BENCHMARK(v4_simd);
    BENCHMARK(v5_simd);
    BENCHMARK(v6_simd);
#endif

#pragma clang diagnostic pop
}

int main(int argc, char** argv) {
    ::benchmark::Initialize(&argc, argv);
    if (::benchmark::ReportUnrecognizedArguments(argc, argv))
        return 1;

    CHECK(v1::premultiply_alpha_plain)
    CHECK(v2::premultiply_alpha_plain)

#if !defined(NSIMD)
    CHECK(v1::premultiply_alpha_simd)
    CHECK(v3::premultiply_alpha_simd)
    CHECK(v4::premultiply_alpha_simd)
    CHECK(v5::premultiply_alpha_simd)
    CHECK(v6::premultiply_alpha_simd)
#endif

    ::benchmark::RunSpecifiedBenchmarks();
}
