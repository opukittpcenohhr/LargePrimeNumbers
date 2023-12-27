#include "pollard_rho_find_factor.h"

#include <boost/multiprecision/cpp_int.hpp>
#include <optional>

#include "common.h"
#include "logging.h"
#include "utility.h"

namespace Project {

std::optional<bigint> find_factor_pollard_rho(
    bigint n, size_t max_iterations, std::vector<bigint> start_values) {
  INFO() << "finding factors of " << n << " using pollard rho";

  if (n % 2 == 0) {
    return 2;
  }

  auto f = [&n](bigint x) {
    return addmod<bigint>(mulmod(x, x, n), 1, n);
  };

  for (bigint start_value : start_values) {
    DEBUG() << "using start value " << start_value;
    bigint first_pointer = start_value;
    auto second_pointer = first_pointer;
    for (size_t i = 0; i < max_iterations; i++) {
      first_pointer = f(first_pointer);
      second_pointer = f(f(second_pointer));
      auto difference = abs(first_pointer - second_pointer);
      auto current_gcd = gcd(difference, n);
      DEBUG() << "iteration: " << i << " first_pointer: " << first_pointer
              << " second_pointer: " << second_pointer
              << " difference: " << difference
              << " current_gcd: " << current_gcd;
      if (current_gcd != 1) {
        if (current_gcd == n) {
          return std::nullopt;
        }
        return current_gcd;
      }
    }
  }
  WARNING() << "pollard rho failed for all start values, probably you need to "
               "use different "
               "polynomial, n: "
            << n;
  return std::nullopt;
}

}  // namespace Project
