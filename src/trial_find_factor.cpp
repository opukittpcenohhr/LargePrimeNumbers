#include "trial_find_factor.h"

#include <optional>

#include "common.h"

namespace LargePrimeNumbers {

bool is_prime_trial(const bigint& x) {
  return !find_factor_trial(x).has_value();
}

std::optional<bigint> find_factor_trial(const bigint& n) {
  if (n % 2 == 0 && n > 2) {
    return 2;
  }
  for (bigint i = 3; i * i <= n; i += 2) {
    if (n % i == 0) {
      return i;
    }
  }
  return std::nullopt;
}

}  // namespace LargePrimeNumbers
