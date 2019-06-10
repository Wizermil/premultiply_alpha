#pragma once

#include <cstdint>
#include <cstddef>
#include <iostream>

#define CHECK(x) if (!pma::check(&x)) { \
std::cout << "error test: " << __LINE__ << ": " << (#x) << '\n'; \
    return -1; \
}

namespace pma {
    bool check(void (*func)(std::uint32_t*, std::size_t)) noexcept;
}
