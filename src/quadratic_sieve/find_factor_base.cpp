#include "find_factor_base.h"

#include <boost/multiprecision/cpp_int.hpp>
#include <optional>

#include "common.h"
#include "legendre_symbol.h"
#include "utility.h"

namespace LargePrimeNumbers {

std::vector<size_t> find_factor_base(const bigint& n, size_t factors_count) {
  // 100 * factors_count should be enough, since there is around n / ln(n) prime
  // numbers less than n, and around half of them have legendre symbol equal to
  // 1 -- so in our case 100 is sufficient for factors_count <= 10^6 for sure

  std::vector<size_t> result;
  result.reserve(factors_count);
  result.push_back(2);

  auto max_number_to_check = 100 * factors_count;
  std::vector<bool> is_prime(max_number_to_check + 1, true);

  auto check_and_add_to_factor_base = [&](size_t p) {
    if (find_legendre_symbol(n, p) == 1) {
      result.push_back(p);
    }
  };

  for (size_t i = 3; i <= max_number_to_check && result.size() < factors_count;
       i += 2) {
    if (is_prime[i]) {
      check_and_add_to_factor_base(i);
      for (size_t j = 2 * i; j <= max_number_to_check; j += i) {
        is_prime[j] = false;
      }
    }
  }
  assert(result.size() == factors_count);
  return result;
}

}  // namespace LargePrimeNumbers
