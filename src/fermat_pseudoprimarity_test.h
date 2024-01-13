#pragma once

#include <boost/multiprecision/cpp_int.hpp>

#include "common.h"
#include "logging.h"
#include "utility.h"

namespace LargePrimeNumbers {

template <typename BasesType, size_t bases_count>
struct FermatPseudoprimalityParams {
  const std::array<BasesType, bases_count> bases;
};

template <FermatPseudoprimalityParams params>
bool is_fermat_pseudoprime(bigint n) {
  INFO() << "testing if " << n << " is fermat pseudoprime";
  for (const auto& base : params.bases) {
    DEBUG() << "trying base " << base;
    if (gcd(base, n) != 1) {
      // We know, that either base == n or n is not prime
      // although we cant simply check this two cases (and probably return
      // false), since number is considered pseudoprime, only if it pseudoprime
      // for all relatively prime bases, and this is not the case
      continue;
    }
    auto predicate_value = powmod<bigint>(base, n - 1, n);
    DEBUG() << "predicate_value is: " << predicate_value;
    if (predicate_value != 1) {
      return false;
    }
  }

  return true;
}

}  // namespace LargePrimeNumbers