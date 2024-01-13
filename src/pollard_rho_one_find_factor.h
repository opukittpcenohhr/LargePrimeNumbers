#pragma once

#include <boost/multiprecision/cpp_int.hpp>
#include <optional>

#include "common.h"
#include "logging.h"
#include "utility.h"

namespace LargePrimeNumbers {

template <typename BasesType, size_t bases_count>
struct PollardRhoOneParams {
  const size_t max_iterations;
  const std::array<BasesType, bases_count> bases;
};

template <PollardRhoOneParams params>
std::optional<bigint> find_factor_pollard_rho_one(bigint n) {
  INFO() << "finding factors of " << n << " using pollard rho one";

  if (n % 2 == 0) {
    return 2;
  }

  for (bigint base : params.bases) {
    DEBUG() << "trying base:  " << base;
    auto current_pow = base;
    for (bigint i = 1; i < params.max_iterations; i++) {
      current_pow = powmod(current_pow, i, n);
      auto current_gcd = gcd(current_pow - 1, n);
      DEBUG() << "iteration: " << i << " current_pow: " << current_pow
              << " current_gcd: " << current_gcd;
      if (current_pow == 1) {
        break;
      }
      if (current_gcd == n) {
        break;
      }
      if (current_gcd > 1) {
        return current_gcd;
      }
    }
  }
  WARNING()
      << "pollard rho one failed for all start values, probably you need to "
         "use different "
         "start value, n: "
      << n;
  return std::nullopt;
}

}  // namespace LargePrimeNumbers
