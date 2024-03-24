#include "strong_pseudoprimality_test.h"

#include "common.h"
#include "utility.h"

namespace LargePrimeNumbers {

std::pair<size_t, bigint> find_highest_power(bigint n, const bigint& k) {
  assert(k != 1);
  assert(n != 0);
  size_t res = 0;
  while (n % k == 0) {
    res++;
    n /= k;
  }
  return {res, n};
}

bool is_strong_pseudoprime_relative_to_base(const bigint& n, int base) {
  size_t a;
  bigint t;
  std::tie(a, t) = find_highest_power(n - 1, 2);
  auto current_pow = powmod<bigint>(base, t, n);
  if (current_pow == 1 || current_pow == n - 1) {
    return true;
  }
  for (size_t i = 0; i + 1 < a; i++) {
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
