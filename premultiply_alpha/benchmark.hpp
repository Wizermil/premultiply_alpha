#pragma once

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#include <benchmark/benchmark.h>
#pragma clang diagnostic pop

namespace pma {
    void v1_plain(benchmark::State& state) noexcept;
    void v2_plain(benchmark::State& state) noexcept;

    void v1_simd(benchmark::State& state) noexcept;
    void v3_simd(benchmark::State& state) noexcept;
    void v4_simd(benchmark::State& state) noexcept;
    void v5_simd(benchmark::State& state) noexcept;
    void v6_simd(benchmark::State& state) noexcept;
}
