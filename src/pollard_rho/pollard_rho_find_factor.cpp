#include "pollard_rho_find_factor.h"

#include "common.h"
#include "utility.h"

namespace LargePrimeNumbers {

PollardRhoResult pollard_rho(
    const bigint& n, std::optional<size_t> max_iterations, int start_value) {
  BOOST_LOG_TRIVIAL(info) << "finding factors of " << n << " using pollard rho";

  auto next_value = [&n](bigint x) {
    return addmod<bigint>(mulmod(x, x, n), 1, n);
  };

  BOOST_LOG_TRIVIAL(debug) << "using start value " << start_value;
  bigint first_pointer(start_value);
  bigint second_pointer(first_pointer);
  size_t iterations_passed = 0;
  while (!max_iterations.has_value() ||
         iterations_passed < max_iterations.value()) {
    iterations_passed++;
    first_pointer = next_value(first_pointer);
    second_pointer = next_value(next_value(second_pointer));
    auto difference = abs(first_pointer - second_pointer);
    auto current_gcd = gcd(difference, n);
    BOOST_LOG_TRIVIAL(debug)
        << "iterations_passed: " << iterations_passed
        << " first_pointer: " << first_pointer
        << " second_pointer: " << second_pointer
        << " difference: " << difference << " current_gcd: " << current_gcd;
    if (current_gcd != 1) {
      if (current_gcd == n) {
        return {iterations_passed, std::nullopt};
      }
      return {iterations_passed, current_gcd};
    }
  }
  BOOST_LOG_TRIVIAL(warning)
      << "pollard rho failed, n: " << n << " start_value:  " << start_value;
  return {iterations_passed, std::nullopt};
}

std::optional<bigint> find_factor_pollard_rho(
    const bigint& n, const PollardRhoParams& params) {
  for (auto start_value : params.start_values) {
    if (auto factor = factor_with_gcd<bigint>(n, start_value)) {
      return factor.value();
    }
  }
  for (auto start_value : params.start_values) {
    auto result = pollard_rho(n, params.max_iterations, start_value);
    if (result.factor.has_value()) {
      return result.factor.value();
    }
  }
  return std::nullopt;
}

}  // namespace LargePrimeNumbers
