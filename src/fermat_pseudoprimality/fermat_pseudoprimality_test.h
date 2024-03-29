#pragma once

#include <span>

#include "common.h"

namespace LargePrimeNumbers {

// Preconditions:
// n is co-prime to start_value
bool is_fermat_pseudoprime_relative_to_base(const bigint& n, int base);

bool is_fermat_pseudoprime(const bigint& n, std::span<const int> bases);

bool is_prime_fermat_test(const bigint& n, std::span<const int> bases);

}  // namespace LargePrimeNumbers
