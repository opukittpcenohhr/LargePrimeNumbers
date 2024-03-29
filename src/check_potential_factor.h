#pragma once

#include <optional>

#include "common.h"

namespace LargePrimeNumbers {

inline bool check_potential_factor(
    const bigint& n, const std::optional<bigint>& potential_factor) {
  return potential_factor.has_value() && potential_factor.value() > 1 &&
         potential_factor.value() < n && n % potential_factor.value() == 0;
}

}  // namespace LargePrimeNumbers
