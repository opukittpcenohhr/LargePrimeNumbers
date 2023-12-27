#include <boost/multiprecision/cpp_int.hpp>
#include <optional>

#include "common.h"
#include "logging.h"
#include "utility.h"

namespace Project {

std::optional<bigint> find_factor_pollard_rho_one(bigint n,
                                                  size_t max_iterations,
                                                  std::vector<bigint> bases) {
  INFO() << "finding factors of " << n << " using pollard rho one";

  if (n % 2 == 0) {
    return 2;
  }

  for (bigint base : bases) {
    DEBUG() << "trying base:  " << base;
    auto current_pow = base;
    for (bigint i = 1; i < max_iterations; i++) {
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

}  // namespace Project
