#pragma once

#include <optional>

#include "common.h"

namespace LargePrimeNumbers {

struct PollardRhoOneParams {
  std::optional<size_t> max_iterations;
  std::vector<int> bases;
};

struct PollardRhoOneResult {
  size_t iteration_count;
  std::optional<bigint> factor;
};

// Preconditions:
// n is known composite
// n is co-prime to start_value
PollardRhoOneResult pollard_rho_one(
    const bigint& n, std::optional<size_t> max_iterations, int base);

// Preconditions:
// n is known composite
std::optional<bigint> find_factor_pollard_rho_one(
    const bigint& n, const PollardRhoOneParams& params);

}  // namespace LargePrimeNumbers
