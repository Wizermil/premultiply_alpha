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

static bool check(void (*func)(std::uint8_t*, std::size_t), std::uint8_t* data, std::size_t pixels, std::uint8_t const* result) noexcept {
    func(data, pixels);
    return std::strncmp(reinterpret_cast<char const*>(data), reinterpret_cast<char const*>(result), pixels) == 0;
}

static std::uint8_t* setup(std::uint8_t const* data, std::size_t len) noexcept {
    auto sample = new std::uint8_t[len];
    std::memcpy(sample, data, len);
    return sample;
}

namespace pma {

    bool check(void (*func)(std::uint8_t*, std::size_t)) noexcept {
        bool result = true;

        std::uint8_t* data_1 = setup(DATA, 4);
        result &= ::check(func, data_1, 4, RESULT);
        delete[] data_1;

        std::uint8_t* data_16 = setup(DATA, 16);
        result &= ::check(func, data_16, 16, RESULT);
        delete[] data_16;

        std::uint8_t* data_20 = setup(DATA, 20);
        result &= ::check(func, data_20, 20, RESULT);
        delete[] data_20;

        std::uint8_t* data_32 = setup(DATA, 32);
        result &= ::check(func, data_32, 32, RESULT);
        delete[] data_32;

        return result;
    }
}
