#pragma once

#include <optional>

#include "common.h"

namespace LargePrimeNumbers {

std::optional<bigint> find_factor_dixon(const bigint& n,
                                        const std::vector<bigint>& r_candidates,
                                        const std::vector<size_t>& factor_base);

}  // namespace LargePrimeNumbers
