#include "trial_primality_test.h"

#include "common.h"
#include "trial_find_factor.h"

namespace LargePrimeNumbers {

bool is_prime_trial(const bigint& x) {
  return !find_factor_trial(x).has_value();
}

}  // namespace LargePrimeNumbers
