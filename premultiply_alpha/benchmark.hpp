#pragma once

#include <benchmark/benchmark.h>

namespace pma {
    void v1_plain(benchmark::State& state) noexcept;
    void v2_plain(benchmark::State& state) noexcept;

#if !defined(NSIMD)
#    if defined(__i386__) || defined(__x86_64__)
    void v1_simd_x86(benchmark::State& state) noexcept;
    void v3_simd_x86(benchmark::State& state) noexcept;
    void v4_simd_x86(benchmark::State& state) noexcept;
    void v5_simd_x86(benchmark::State& state) noexcept;
#    endif
#endif
}
