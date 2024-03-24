#pragma once

#include <span>

#include "common.h"

namespace LargePrimeNumbers {

std::pair<size_t, bigint> find_highest_power(bigint n, const bigint& k);

// Preconditions:
// n is even
// n is co-prime to base
bool is_strong_pseudoprime_relative_to_base(const bigint& n, int base);

// Also known as Miller-Rabbin test
bool is_strong_pseudoprime(const bigint& n, std::span<const int> bases);

}  // namespace LargePrimeNumbers
