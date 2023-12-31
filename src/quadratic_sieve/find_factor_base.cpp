#include "find_factor_base.h"

#include <boost/multiprecision/cpp_int.hpp>
#include <optional>

#include "common.h"
#include "legendre_symbol.h"
#include "logging.h"
#include "utility.h"

namespace Project {

std::vector<int> find_factor_base(bigint n, size_t factors_count) {
  // 100 * factors_count should be enough, since there is around n / ln(n) prime
  // numbers less than n, and around half of them have legendre symbol equal to
  // 1 -- so in our case 100 is sufficient for factors_count <= 10^6 for sure

  std::vector<int> result;
  result.reserve(factors_count);

  auto max_number_to_check = 100 * factors_count;
  std::vector<bool> is_prime(max_number_to_check + 1, true);
  for (int i = 2; i <= static_cast<int>(max_number_to_check); i++) {
    if (is_prime[i]) {
      if (find_legendre_symbol(n, i) == 1) {
        result.push_back(i);
        if (result.size() == factors_count) {
          break;
        }
      }
      for (size_t j = 2 * i; j <= max_number_to_check; j += i) {
        is_prime[j] = false;
      }
    }
  }
  assert(result.size() == factors_count);
  return result;
}

}  // namespace Project