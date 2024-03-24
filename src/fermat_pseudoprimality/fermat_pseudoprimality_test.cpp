#include "fermat_pseudoprimality_test.h"

#include <span>

#include "common.h"
#include "utility.h"

namespace LargePrimeNumbers {

bool is_fermat_pseudoprime_relative_to_base(const bigint& n, int base) {
  auto predicate_value = powmod<bigint>(base, n - 1, n);
  BOOST_LOG_TRIVIAL(debug) << "fermat pseudoprimality test, n: " << n
                           << " base: " << base
                           << " predicate_value: " << predicate_value;
  return predicate_value == 1;
}

bool is_fermat_pseudoprime(const bigint& n, std::span<const int> bases) {
  for (auto base : bases) {
    // We know, that either base == n or n is not prime
    // although we cant simply check this two cases (and probably return
    // false), since number is considered pseudoprime, only if it pseudoprime
    // for all relatively prime bases, and this is not the case
    if (gcd(n, base) != 1) {
      continue;
    }
    if (!is_fermat_pseudoprime_relative_to_base(n, base)) {
      return false;
    }
  }
  return true;
}

}  // namespace LargePrimeNumbers
