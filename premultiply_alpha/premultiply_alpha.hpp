#pragma once

#include <stdint.h>
#include <assert.h>
#include <stddef.h>

#if !defined(NSIMD)
#    if defined(__ARM_NEON)
#        include <arm_neon.h>
#    elif defined(__i386__) || defined(__x86_64__)
#        include <immintrin.h>
#    endif
#endif

template <typename Iterator, typename OutputIterator, typename Func>
inline constexpr OutputIterator transform(Iterator first, Iterator last, OutputIterator result, Func&& func) noexcept {
    for (; first != last; ++first, ++result) {
        *result = func(*first);
    }
    return result;
}

// v1

namespace v1 {
    inline void premultiply_alpha_plain(uint32_t* data, size_t pixel) noexcept {
        uint8_t* bytes = reinterpret_cast<uint8_t*>(data);
        for (size_t i = 0, max = pixel << 2; i < max; i+=4) {
            bytes[i] = static_cast<uint8_t>(static_cast<uint16_t>(bytes[i] * bytes[i+3]) / static_cast<uint16_t>(255));
            bytes[i+1] = static_cast<uint8_t>(static_cast<uint16_t>(bytes[i+1] * bytes[i+3]) / static_cast<uint16_t>(255));
            bytes[i+2] = static_cast<uint8_t>(static_cast<uint16_t>(bytes[i+2] * bytes[i+3]) / static_cast<uint16_t>(255));
        }
    }

    inline void premultiply_alpha_simd(uint32_t* data, size_t pixel) noexcept {
#if !defined(NSIMD)
#    if defined(__i386__) || defined(__x86_64__)
        assert((reinterpret_cast<uintptr_t>(data) & 15) == 0);

        size_t const max_simd_pixel = pixel * sizeof(uint32_t) / sizeof(__m128i);

        __m128i const alpha_mask = _mm_set1_epi32(static_cast<int>(0xFF000000));
        __m128i const alpha_mask_one_comp = _mm_set1_epi32(static_cast<int>(0x00FFFFFF));
        __m128i const odd_mask = _mm_set1_epi16(static_cast<short>(0xFF00));
        __m128i const div_255 = _mm_set1_epi16(static_cast<short>(0x8081));

        __m128i color, alpha, color_even, color_odd;
        for (__m128i *ptr = reinterpret_cast<__m128i*>(data), *end = ptr + max_simd_pixel; ptr != end; ++ptr) {
            color = _mm_load_si128(ptr);

            alpha = _mm_and_si128(color, alpha_mask);
            alpha = _mm_or_si128(alpha, _mm_srli_epi32(alpha, 16));

            color_even = _mm_slli_epi16(color, 8);
            color_odd = _mm_and_si128(color, odd_mask);

            color_odd = _mm_mulhi_epu16(color_odd, alpha);
            color_even = _mm_mulhi_epu16(color_even, alpha);

            color_odd = _mm_srli_epi16(_mm_mulhi_epu16(color_odd, div_255), 7);
            color_even = _mm_srli_epi16(_mm_mulhi_epu16(color_even, div_255), 7);

            color = _mm_or_si128(color_even, _mm_slli_epi16(color_odd, 8));
            color = _mm_or_si128(_mm_and_si128(alpha, alpha_mask), _mm_and_si128(color, alpha_mask_one_comp));

            _mm_store_si128(ptr, color);
        }

        size_t const processed_pixel = max_simd_pixel * sizeof(__m128i) / sizeof(uint32_t);
        size_t const remaining_pixel = pixel - processed_pixel;
        premultiply_alpha_plain(data + processed_pixel, remaining_pixel);
#    elif defined(__ARM_NEON)
        // TODO
        premultiply_alpha_plain(data, pixel);
#    endif
#else
        premultiply_alpha_plain(data, pixel);
#endif
    }
}

// v2

namespace v2 {
    inline void premultiply_alpha_plain(uint32_t* data, size_t pixel) noexcept {
        ::transform(data, data + pixel, data, [](uint32_t p) noexcept {
            auto const a =  (p >> 24) & 0xFFU;
            auto const r = (((p >> 0) & 0xFFU) * a) / 255U;
            auto const g = (((p >> 8) & 0xFFU) * a) / 255U;
            auto const b = (((p >> 16) & 0xFFU) * a) / 255U;

            return (a << 24) | (b << 16) | (g << 8) | (r << 0);
        });
    }
}

// v3

namespace v3 {
    inline void premultiply_alpha_plain(uint32_t* data, size_t pixel) noexcept {
        ::transform(data, data + pixel, data, [](uint32_t p) noexcept {
            auto const a =  (p >> 24) & 0xFFU;
            auto const r = (((p >> 0) & 0xFFU) * a) / 255U;
            auto const g = (((p >> 8) & 0xFFU) * a) / 255U;
            auto const b = (((p >> 16) & 0xFFU) * a) / 255U;

            return (a << 24) | (b << 16) | (g << 8) | (r << 0);
        });
    }

    inline void premultiply_alpha_simd(uint32_t* data, size_t pixel) noexcept {
#if !defined(NSIMD)
#    if defined(__i386__) || defined(__x86_64__)
        assert((reinterpret_cast<uintptr_t>(data) & 15) == 0);

        size_t const max_simd_pixel = pixel * sizeof(uint32_t) / sizeof(__m128i);

        __m128i const mask_alphha_color_odd_255 = _mm_set1_epi32(static_cast<int>(0xff000000));
        __m128i const div_255 = _mm_set1_epi16(static_cast<short>(0x8081));

        __m128i const mask_shuffle_alpha = _mm_set_epi32(0x0f800f80, 0x0b800b80, 0x07800780, 0x03800380);
        __m128i const mask_shuffle_color_odd = _mm_set_epi32(static_cast<int>(0x80800d80), static_cast<int>(0x80800980), static_cast<int>(0x80800580), static_cast<int>(0x80800180));

        __m128i color, alpha, color_even, color_odd;
        for (__m128i *ptr = reinterpret_cast<__m128i*>(data), *end = ptr + max_simd_pixel; ptr != end; ++ptr) {
            color = _mm_load_si128(ptr);

            alpha = _mm_shuffle_epi8(color, mask_shuffle_alpha);

            color_even = _mm_slli_epi16(color, 8);
            color_odd = _mm_shuffle_epi8(color, mask_shuffle_color_odd);
            color_odd = _mm_or_si128(color_odd, mask_alphha_color_odd_255);
//            color_odd = _mm_blendv_epi8(color, _mm_set_epi32(0xff000000, 0xff000000, 0xff000000, 0xff000000), _mm_set_epi32(0x80800080, 0x80800080, 0x80800080, 0x80800080));

            color_odd = _mm_mulhi_epu16(color_odd, alpha);
            color_even = _mm_mulhi_epu16(color_even, alpha);

            color_odd = _mm_srli_epi16(_mm_mulhi_epu16(color_odd, div_255), 7);
            color_even = _mm_srli_epi16(_mm_mulhi_epu16(color_even, div_255), 7);

            color = _mm_or_si128(color_even, _mm_slli_epi16(color_odd, 8));

            _mm_store_si128(ptr, color);
        }

        size_t const processed_pixel = max_simd_pixel * sizeof(__m128i) / sizeof(uint32_t);
        size_t const remaining_pixel = pixel - processed_pixel;
        premultiply_alpha_plain(data + processed_pixel, remaining_pixel);
#    elif defined(__ARM_NEON)
        // TODO
        premultiply_alpha_plain(data, pixel);
#    endif

#else
        premultiply_alpha_plain(data, pixel);
#endif
    }
}

// v4

namespace v4 {
    inline void premultiply_alpha_plain(uint32_t* data, size_t pixel) noexcept {
        ::transform(data, data + pixel, data, [](uint32_t p) noexcept {
            auto const a =  (p >> 24) & 0xFFU;
            auto const r = (((p >> 0) & 0xFFU) * a) / 255U;
            auto const g = (((p >> 8) & 0xFFU) * a) / 255U;
            auto const b = (((p >> 16) & 0xFFU) * a) / 255U;

            return (a << 24) | (b << 16) | (g << 8) | (r << 0);
        });
    }

    inline void premultiply_alpha_simd(uint32_t* data, size_t pixel) noexcept {
#if !defined(NSIMD)
#    if defined(__i386__) || defined(__x86_64__)
        assert((reinterpret_cast<uintptr_t>(data) & 15) == 0);

        size_t const max_simd_pixel = pixel * sizeof(uint32_t) / (sizeof(__m128i) * 2);

        for (__m128i *ptr = reinterpret_cast<__m128i*>(data), *end = ptr + (max_simd_pixel * 2); ptr != end; ptr += 2) {
            // load data and split channels:
            __m128i abgr = _mm_load_si128(ptr);
            __m128i ABGR = _mm_load_si128(ptr+1);
            __m128i __ab = _mm_srli_epi32(abgr,16);
            __m128i GR__ = _mm_slli_epi32(ABGR,16);
            __m128i ABab = _mm_blend_epi16(ABGR, __ab, 0x55);
            __m128i GRgr = _mm_blend_epi16(GR__, abgr, 0x55);
            __m128i A_a_ = _mm_and_si128(ABab, _mm_set1_epi16(static_cast<short>(0xFF00)));
            __m128i G_g_ = _mm_and_si128(GRgr, _mm_set1_epi16(static_cast<short>(0xFF00)));
            __m128i R_r_ = _mm_slli_epi16(GRgr, 8);
            __m128i B_b_ = _mm_slli_epi16(ABab, 8);

            // actual alpha-scaling:
            __m128i inv = _mm_set1_epi16(static_cast<short>(0x8081)); // = ceil((1<<(16+7))/255.0)
            G_g_ = _mm_mulhi_epu16(_mm_mulhi_epu16(G_g_, A_a_), inv);
            // shift 7 to the right and 8 to the left, or shift 1 to the left and mask:
            G_g_ = _mm_and_si128(_mm_add_epi16(G_g_, G_g_), _mm_set1_epi16(static_cast<short>(0xFF00)));
            __m128i _R_r = _mm_mulhi_epu16(_mm_mulhi_epu16(R_r_, A_a_), inv);
            _R_r = _mm_srli_epi16(_R_r,7);
            __m128i _B_b = _mm_mulhi_epu16(_mm_mulhi_epu16(B_b_, A_a_), inv);
            _B_b = _mm_srli_epi16(_B_b,7);

            // re-assemble channels:
            GRgr = _mm_or_si128(_R_r, G_g_);
            ABab = _mm_or_si128(A_a_, _B_b);

            __m128i __GR = _mm_srli_epi32(GRgr, 16);
            __m128i ab__ = _mm_slli_epi32(ABab, 16);

            ABGR = _mm_blend_epi16(ABab, __GR, 0x55);
            abgr = _mm_blend_epi16(ab__, GRgr, 0x55);

            // store result
            _mm_store_si128(ptr, abgr);
            _mm_store_si128(ptr+1, ABGR);
        }

        size_t const processed_pixel = max_simd_pixel * sizeof(__m128i) * 2 / sizeof(uint32_t);
        size_t const remaining_pixel = pixel - processed_pixel;
        premultiply_alpha_plain(data + processed_pixel, remaining_pixel);
#    elif defined(__ARM_NEON)
        // TODO
        premultiply_alpha_plain(data, pixel);
#    endif
#else
        premultiply_alpha_plain(data, pixel);
#endif
    }
}

// v5

namespace v5 {
    inline void premultiply_alpha_plain(uint32_t* data, size_t pixel) noexcept {
        ::transform(data, data + pixel, data, [](uint32_t p) noexcept {
            auto const a =  (p >> 24) & 0xFFU;
            auto const r = (((p >> 0) & 0xFFU) * a) / 255U;
            auto const g = (((p >> 8) & 0xFFU) * a) / 255U;
            auto const b = (((p >> 16) & 0xFFU) * a) / 255U;

            return (a << 24) | (b << 16) | (g << 8) | (r << 0);
        });
    }

    inline void premultiply_alpha_simd(uint32_t* data, size_t pixel) noexcept {
#if !defined(NSIMD)
#if    defined(__AVX__) && (defined(__i386__) || defined(__x86_64__))
        assert((reinterpret_cast<uintptr_t>(data) & 31) == 0);

        size_t const max_simd_pixel = pixel * sizeof(uint32_t) / sizeof(__m256i);

        __m256i const mask_alphha_color_odd_255 = _mm256_set1_epi32(static_cast<int>(0xff000000));
        __m256i const div_255 = _mm256_set1_epi16(static_cast<short>(0x8081));

        __m256i const mask_shuffle_alpha = _mm256_set_epi32(0x0f800f80, 0x0b800b80, 0x07800780, 0x03800380, 0x0f800f80, 0x0b800b80, 0x07800780, 0x03800380);
        __m256i const mask_shuffle_color_odd = _mm256_set_epi32(static_cast<int>(0x80800d80), static_cast<int>(0x80800980), static_cast<int>(0x80800580), static_cast<int>(0x80800180), static_cast<int>(0x80800d80), static_cast<int>(0x80800980), static_cast<int>(0x80800580), static_cast<int>(0x80800180));

        __m256i color, alpha, color_even, color_odd;
        for (__m256i *ptr = reinterpret_cast<__m256i*>(data), *end = ptr + max_simd_pixel; ptr != end; ++ptr) {
            color = _mm256_load_si256(ptr);

            alpha = _mm256_shuffle_epi8(color, mask_shuffle_alpha);

            color_even = _mm256_slli_epi16(color, 8);
            color_odd = _mm256_shuffle_epi8(color, mask_shuffle_color_odd);
            color_odd = _mm256_or_si256(color_odd, mask_alphha_color_odd_255);

            color_odd = _mm256_mulhi_epu16(color_odd, alpha);
            color_even = _mm256_mulhi_epu16(color_even, alpha);

            color_odd = _mm256_srli_epi16(_mm256_mulhi_epu16(color_odd, div_255), 7);
            color_even = _mm256_srli_epi16(_mm256_mulhi_epu16(color_even, div_255), 7);

            color = _mm256_or_si256(color_even, _mm256_slli_epi16(color_odd, 8));

            _mm256_store_si256(ptr, color);
        }

        size_t const processed_pixel = max_simd_pixel * sizeof(__m256i) / sizeof(uint32_t);
        size_t const remaining_pixel = pixel - processed_pixel;
        premultiply_alpha_plain(data + processed_pixel, remaining_pixel);
#    elif defined(__ARM_NEON)
        // TODO
        premultiply_alpha_plain(data, pixel);
#    endif
#else
        premultiply_alpha_plain(data, pixel);
#endif
    }
}

// v6

namespace v6 {
    inline void premultiply_alpha_plain(uint32_t* data, size_t pixel) noexcept {
        ::transform(data, data + pixel, data, [](uint32_t p) noexcept {
            auto const a =  (p >> 24) & 0xFFU;
            auto const r = (((p >> 0) & 0xFFU) * a) / 255U;
            auto const g = (((p >> 8) & 0xFFU) * a) / 255U;
            auto const b = (((p >> 16) & 0xFFU) * a) / 255U;

            return (a << 24) | (b << 16) | (g << 8) | (r << 0);
        });
    }

    inline void premultiply_alpha_simd(uint32_t* data, size_t pixel) noexcept {
#if !defined(NSIMD)
#    if defined(__i386__) || defined(__x86_64__)
        using u8x16 = __attribute__((ext_vector_type(16))) uint8_t;
        using u16x8 = __attribute__((ext_vector_type(8))) uint16_t;

        size_t const max_simd_pixel = pixel * sizeof(uint32_t) / sizeof(u8x16);

        ::transform(reinterpret_cast<u8x16*>(data), reinterpret_cast<u8x16*>(data) + max_simd_pixel, reinterpret_cast<u8x16*>(data), [](u8x16 p) noexcept {
            u16x8 const alpha {p[3], p[3], p[7], p[7], p[11], p[11], p[15], p[15]};
            u16x8 color_even {(reinterpret_cast<u16x8>(p) >> 8) | u16x8{0x0000, 0x00FF, 0x0000, 0x00FF, 0x0000, 0x00FF, 0x0000, 0x00FF}};
            u16x8 color_odd {reinterpret_cast<u16x8>(p) & u16x8{0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF}};

            color_even = color_even * alpha;
            color_odd = color_odd * alpha;

            color_even /= 255U;
            color_odd /= 255U;

            return reinterpret_cast<u8x16>((color_even << 8) | color_odd);
        });

        size_t const processed_pixel = max_simd_pixel * sizeof(u8x16) / sizeof(uint32_t);
        size_t const remaining_pixel = pixel - processed_pixel;
        premultiply_alpha_plain(data + processed_pixel, remaining_pixel);
#    elif defined(__ARM_NEON)
        // TODO
        premultiply_alpha_plain(data, pixel);
#    endif
#else
        premultiply_alpha_plain(data, pixel);
#endif
    }

}
