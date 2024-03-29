#pragma once

#include <optional>

#include "common.h"

namespace LargePrimeNumbers {

bool is_prime_trial(const bigint& x);

std::optional<bigint> find_factor_trial(const bigint& n);

}  // namespace LargePrimeNumbers
