#pragma once

#include <boost/multiprecision/cpp_int.hpp>

#include "common.h"
#include "logging.h"
#include "utility.h"

namespace LargePrimeNumbers {

template <typename BasesType, size_t bases_count>
struct StrongPseudoprimalityParams {
  const std::array<BasesType, bases_count> bases;
};

std::pair<size_t, bigint> find_highest_power(bigint n, bigint k) {
  assert(k != 1);
  assert(n != 0);
  size_t res = 0;
  while (n % k == 0) {
    res++;
    n /= k;
  }
  return {res, n};
}

// Also known as Miller-Rabbin test
template <StrongPseudoprimalityParams params>
bool is_strong_pseudoprime(bigint n) {
  INFO() << "testing if " << n << " is strong pseudoprime";
  if (n == 2) {
    return true;
  }
  if (n % 2 == 0) {
    return false;
  }
  size_t a;
  bigint t;
  std::tie(a, t) = find_highest_power(n - 1, 2);
  for (const auto& base : params.bases) {
    if (gcd(n, base) != 1) {
      continue;
    }
    bool found_one_divisible = false;
    bigint current_pow = powmod<bigint>(base, t, n);
    if (current_pow == 1 || current_pow == n - 1) {
      found_one_divisible = true;
      break;
    }
    for (size_t i = 0; i + 1 < a; i++) {
      current_pow = mulmod(current_pow, current_pow, n);
      if (current_pow == n - 1) {
        found_one_divisible = true;
        break;
      }
    }
    if (!found_one_divisible) {
      return false;
    }
  }
  return true;
}

}  // namespace LargePrimeNumbers