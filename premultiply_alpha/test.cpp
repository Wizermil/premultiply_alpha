#include "test.hpp"

#include <cstring>

static constexpr std::uint8_t const DATA[64] {
    0xff, 0x01, 0xf1, 0x66,
    0x80, 0x80, 0x80, 0x22,
    0x88, 0x88, 0x88, 0x00,
    0xff, 0x66, 0x05, 0xff,

    0xff, 0x01, 0xf1, 0x66,
    0x00, 0x00, 0x00, 0xff,
    0x88, 0x88, 0x88, 0x00,
    0xff, 0x66, 0x05, 0xff,

    0xff, 0x01, 0xf1, 0x66,
    0x80, 0x80, 0x80, 0x22,
    0x88, 0x88, 0x88, 0x00,
    0xff, 0x66, 0x05, 0xff,

    0xff, 0x01, 0xf1, 0x66,
    0x00, 0x00, 0x00, 0xff,
    0x88, 0x88, 0x88, 0x00,
    0xff, 0x66, 0x05, 0xff
};
static constexpr std::uint8_t const RESULT[64] {
    0x66, 0x00, 0x60, 0x66,
    0x11, 0x11, 0x11, 0x22,
    0x00, 0x00, 0x00, 0x00,
    0xff, 0x66, 0x05, 0xff,

    0x66, 0x00, 0x60, 0x66,
    0x00, 0x00, 0x00, 0xff,
    0x00, 0x00, 0x00, 0x00,
    0xff, 0x66, 0x05, 0xff,

    0x66, 0x00, 0x60, 0x66,
    0x11, 0x11, 0x11, 0x22,
    0x00, 0x00, 0x00, 0x00,
    0xff, 0x66, 0x05, 0xff,

    0x66, 0x00, 0x60, 0x66,
    0x00, 0x00, 0x00, 0xff,
    0x00, 0x00, 0x00, 0x00,
    0xff, 0x66, 0x05, 0xff
};

static bool check(void (*func)(std::uint32_t*, std::size_t), std::uint32_t* data, std::size_t pixel, std::uint32_t const* result) noexcept {
    func(data, pixel);
    for (std::uint32_t *first = data, *last = data + pixel; first != last; ++first, ++result) {
        if (*first != *result)
            return false;
    }
    return true;
}

static std::uint32_t* setup(std::uint32_t const* data, std::size_t pixel) noexcept {
    auto sample = new std::uint32_t[pixel];
    std::memcpy(sample, data, pixel * sizeof(std::uint32_t));
    return sample;
}

namespace pma {

    bool check(void (*func)(std::uint32_t*, std::size_t)) noexcept {
        bool result = true;

        std::uint32_t* data_1 = setup(reinterpret_cast<std::uint32_t const*>(DATA), 1);
        result &= ::check(func, data_1, 1, reinterpret_cast<std::uint32_t const*>(RESULT));
        delete[] data_1;

        std::uint32_t* data_4 = setup(reinterpret_cast<std::uint32_t const*>(DATA), 4);
        result &= ::check(func, data_4, 4, reinterpret_cast<std::uint32_t const*>(RESULT));
        delete[] data_4;

        std::uint32_t* data_6 = setup(reinterpret_cast<std::uint32_t const*>(DATA), 6);
        result &= ::check(func, data_6, 6, reinterpret_cast<std::uint32_t const*>(RESULT));
        delete[] data_6;

        std::uint32_t* data_8 = setup(reinterpret_cast<std::uint32_t const*>(DATA), 8);
        result &= ::check(func, data_8, 8, reinterpret_cast<std::uint32_t const*>(RESULT));
        delete[] data_8;

        std::uint32_t* data_16 = setup(reinterpret_cast<std::uint32_t const*>(DATA), 16);
        result &= ::check(func, data_16, 16, reinterpret_cast<std::uint32_t const*>(RESULT));
        delete[] data_16;

        return result;
    }
}
