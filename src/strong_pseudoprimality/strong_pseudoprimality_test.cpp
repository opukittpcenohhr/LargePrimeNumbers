#include "strong_pseudoprimality_test.h"

#include "common.h"
#include "find_highest_power_of.h"
#include "utility.h"

namespace LargePrimeNumbers {

bool is_strong_pseudoprime_relative_to_base(const bigint& n, int base) {
  auto highest_power = find_highest_power_of(n - 1, 2);
  auto current_pow = powmod<bigint>(base, highest_power.remainder, n);
  if (current_pow == 1 || current_pow == n - 1) {
    return true;
  }
  for (size_t i = 0; i + 1 < highest_power.degree; i++) {
    current_pow = mulmod(current_pow, current_pow, n);
    if (current_pow == n - 1) {
      return true;
    }
  }
  return false;
}

bool is_strong_pseudoprime(const bigint& n, std::span<const int> bases) {
  if (n == 2) {
    return true;
  }
  if (n % 2 == 0) {
    return false;
  }
  for (auto base : bases) {
    if (gcd(n, base) != 1) {
      continue;
    }
    if (!is_strong_pseudoprime_relative_to_base(n, base)) {
      return false;
    }
  }
  return true;
}

}  // namespace LargePrimeNumbers
