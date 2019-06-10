#include "test.hpp"

#include <cstring>

static constexpr std::uint8_t const DATA[32] {
    0xff, 0x01, 0xf1, 0x66,
    0x00, 0x00, 0x00, 0xff,
    0x88, 0x88, 0x88, 0x00,
    0xff, 0x66, 0x05, 0xff,

    0xff, 0x01, 0xf1, 0x66,
    0x00, 0x00, 0x00, 0xff,
    0x88, 0x88, 0x88, 0x00,
    0xff, 0x66, 0x05, 0xff
};
static constexpr std::uint8_t const RESULT[32] {
    0x66, 0x00, 0x60, 0x66,
    0x00, 0x00, 0x00, 0xff,
    0x00, 0x00, 0x00, 0x00,
    0xff, 0x66, 0x05, 0xff,

    0x66, 0x00, 0x60, 0x66,
    0x00, 0x00, 0x00, 0xff,
    0x00, 0x00, 0x00, 0x00,
    0xff, 0x66, 0x05, 0xff
};

static bool check(void (*func)(std::uint32_t*, std::size_t), std::uint32_t* data, std::size_t pixel, std::uint8_t const* result) noexcept {
    func(data, pixel);
    return std::strncmp(reinterpret_cast<char const*>(data), reinterpret_cast<char const*>(result), pixel * sizeof(std::uint32_t)) == 0;
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
        result &= ::check(func, data_1, 1, RESULT);
        delete[] data_1;

        std::uint32_t* data_4 = setup(reinterpret_cast<std::uint32_t const*>(DATA), 4);
        result &= ::check(func, data_4, 4, RESULT);
        delete[] data_4;

        std::uint32_t* data_6 = setup(reinterpret_cast<std::uint32_t const*>(DATA), 6);
        result &= ::check(func, data_6, 6, RESULT);
        delete[] data_6;

        std::uint32_t* data_8 = setup(reinterpret_cast<std::uint32_t const*>(DATA), 8);
        result &= ::check(func, data_8, 8, RESULT);
        delete[] data_8;

        return result;
    }
}
