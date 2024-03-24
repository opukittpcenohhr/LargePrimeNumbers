#include "pollard_rho_one_find_factor.h"

#include "common.h"
#include "utility.h"

namespace LargePrimeNumbers {

PollardRhoOneResult pollard_rho_one(const bigint& n,
                                    std::optional<size_t> max_iterations,
                                    int base) {
  BOOST_LOG_TRIVIAL(info) << "finding factors of " << n
                          << " using pollard rho one, base: " << base;
  bigint current_pow(base);
  size_t iterations_passed = 0;
  while (!max_iterations.has_value() ||
         iterations_passed < max_iterations.value()) {
    current_pow = powmod<bigint>(current_pow, iterations_passed + 1, n);
    auto current_gcd = gcd(current_pow - 1, n);
    BOOST_LOG_TRIVIAL(debug) << "iteration: " << iterations_passed
                             << " current_pow: " << current_pow;
    if (current_pow == 1) {
      break;
    }
    if (current_gcd == n) {
      break;
    }
    if (current_gcd > 1) {
      return {iterations_passed, current_gcd};
    }
    ++iterations_passed;
  }
  BOOST_LOG_TRIVIAL(warning)
      << "pollard rho one failed, n: " << n << " base: " << base;
  return {iterations_passed, std::nullopt};
}

std::optional<bigint> find_factor_pollard_rho_one(
    const bigint& n, const PollardRhoOneParams& params) {
  for (auto base : params.bases) {
    if (auto factor = check_potential_factor<bigint>(n, base)) {
      return factor.value();
    }
  }
  for (auto base : params.bases) {
    auto result = pollard_rho_one(n, params.max_iterations, base);
    if (result.factor.has_value()) {
      return result.factor.value();
    }
  }
  return std::nullopt;
}

}  // namespace LargePrimeNumbers
