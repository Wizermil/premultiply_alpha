#pragma once

#include <cstdint>
#include <cstddef>
#include <iostream>

#define CHECK(x) if (!pma::check(&x)) { \
    std::cout << "error algorithm\n"; \
    return -1; \
}

namespace pma {
    bool check(void (*func)(std::uint8_t*, std::size_t)) noexcept;
}
