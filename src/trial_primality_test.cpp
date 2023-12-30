#include "trial_primality_test.h"

#include <boost/multiprecision/cpp_int.hpp>

#include "common.h"

namespace Project {

bool is_prime_trial(bigint x) {
  for (bigint i = 2; i * i <= x; i++) {
    if (x % i == 0) {
      return false;
    }
  }
  return true;
}

}  // namespace Project
