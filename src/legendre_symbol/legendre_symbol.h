#pragma once

#include <boost/multiprecision/cpp_int.hpp>
#include <optional>

#include "common.h"

namespace LargePrimeNumbers {

// Preconditions:
// p is prime
// p is even
int find_legendre_symbol(const bigint& n, const bigint& p);

}  // namespace LargePrimeNumbers
