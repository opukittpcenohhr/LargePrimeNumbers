#pragma once

#include "common.h"

namespace LargePrimeNumbers {

struct HighestPowerOfFactor {
  size_t degree;
  bigint remainder;
};

// Precondition: n > 0, k > 1
HighestPowerOfFactor find_highest_power_of(bigint n, const bigint& k);

}  // namespace LargePrimeNumbers
