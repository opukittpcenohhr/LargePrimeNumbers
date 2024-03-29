#pragma once

#include <optional>

#include "common.h"

namespace LargePrimeNumbers {

// Precondition: n >= 1
bool is_prime_trial(const bigint& x);

// Precondition: n >= 1
std::optional<bigint> find_factor_trial(const bigint& n);

}  // namespace LargePrimeNumbers
