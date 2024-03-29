#include "find_highest_power_of.h"

#include <cassert>

#include "common.h"

namespace LargePrimeNumbers {

HighestPowerOfFactor find_highest_power_of(bigint n, const bigint& k) {
  assert(n > 0 && k > 1);
  size_t res = 0;
  while (n % k == 0) {
    res++;
    n /= k;
  }
  return {res, n};
}

}  // namespace LargePrimeNumbers
