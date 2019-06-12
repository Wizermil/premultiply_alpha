#include "benchmark.hpp"

#include "cat.hpp"
#include "premultiply_alpha.hpp"

static constexpr std::size_t const max_pixel = cat::width * cat::height;

static std::uint32_t* setup() noexcept {
    std::uint32_t* data = new std::uint32_t[max_pixel];
    std::memcpy(data, cat::image, max_pixel * sizeof(std::uint32_t));
    return data;
}

namespace pma {

    void v1_plain(benchmark::State& state) noexcept {
        auto data = setup();
        state.SetLabel("v1::plain");
        for (auto _ : state) {
            v1::premultiply_alpha_plain(data, max_pixel);
        }
        state.counters["itr"] = benchmark::Counter(state.iterations(), benchmark::Counter::kIsRate);
        delete[] data;
    }

    void v2_plain(benchmark::State& state) noexcept {
        auto data = setup();
        state.SetLabel("v2::plain - Dot and Beached (discord #include)");
        for (auto _ : state) {
            v2::premultiply_alpha_plain(data, max_pixel);
        }
        state.counters["itr"] = benchmark::Counter(state.iterations(), benchmark::Counter::kIsRate);
        delete[] data;
    }

    void v6_simd(benchmark::State& state) noexcept {
        auto data = setup();
        state.SetLabel("v6::vector ext");
        for (auto _ : state) {
            v6::premultiply_alpha_simd(data, max_pixel);
        }
        state.counters["itr"] = benchmark::Counter(state.iterations(), benchmark::Counter::kIsRate);
        delete[] data;
    }

#if !defined(NSIMD)
#    if defined(__i386__) || defined(__x86_64__)
    void v1_simd_x86(benchmark::State& state) noexcept {
        auto data = setup();
        state.SetLabel("v1::simd_x86");
        for (auto _ : state) {
            v1::premultiply_alpha_simd_x86(data, max_pixel);
        }
        state.counters["itr"] = benchmark::Counter(state.iterations(), benchmark::Counter::kIsRate);
        delete[] data;
    }

    void v3_simd_x86(benchmark::State& state) noexcept {
        auto data = setup();
        state.SetLabel("v3::simd_x86 - Peter Cordes (stackoverflow)");
        for (auto _ : state) {
            v3::premultiply_alpha_simd_x86(data, max_pixel);
        }
        state.counters["itr"] = benchmark::Counter(state.iterations(), benchmark::Counter::kIsRate);
        delete[] data;
    }

    void v4_simd_x86(benchmark::State& state) noexcept {
        auto data = setup();
        state.SetLabel("v4::simd_x86 - chtz (stackoverflow)");
        for (auto _ : state) {
            v4::premultiply_alpha_simd_x86(data, max_pixel);
        }
        state.counters["itr"] = benchmark::Counter(state.iterations(), benchmark::Counter::kIsRate);
        delete[] data;
    }

    void v5_simd_x86(benchmark::State& state) noexcept {
        auto data = setup();
        state.SetLabel("v5::simd_x86 - AVX2");
        for (auto _ : state) {
            v5::premultiply_alpha_simd_x86(data, max_pixel);
        }
        state.counters["itr"] = benchmark::Counter(state.iterations(), benchmark::Counter::kIsRate);
        delete[] data;
    }
#    endif
#endif
}
