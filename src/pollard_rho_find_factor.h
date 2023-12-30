#include <boost/multiprecision/cpp_int.hpp>
#include <optional>

#include "common.h"
#include "logging.h"
#include "utility.h"

namespace Project {

template <typename BasesType, size_t start_values_count>
struct PollardRhoParams {
  const size_t max_iterations;
  const std::array<BasesType, start_values_count> start_values;
};

template <PollardRhoParams params>
std::optional<bigint> find_factor_pollard_rho(bigint n) {
  INFO() << "finding factors of " << n << " using pollard rho";

  if (n % 2 == 0) {
    return 2;
  }

  auto f = [&n](bigint x) {
    return addmod<bigint>(mulmod(x, x, n), 1, n);
  };

  for (bigint start_value : params.start_values) {
    DEBUG() << "using start value " << start_value;
    bigint first_pointer = start_value;
    auto second_pointer = first_pointer;
    for (size_t i = 0; i < params.max_iterations; i++) {
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
