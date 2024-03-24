#include <optional>

#include "common.h"

namespace LargePrimeNumbers {

struct PollardRhoParams {
  std::optional<size_t> max_iterations;
  std::vector<int> start_values;
};

struct PollardRhoResult {
  size_t iteration_count;
  std::optional<bigint> factor;
};

// Preconditions:
// n is known composite
// n is co-prime to start_value
PollardRhoResult pollard_rho(
    const bigint& n, std::optional<size_t> max_iterations, int start_value);
// Preconditions:
// n is known composite
std::optional<bigint> find_factor_pollard_rho(
    const bigint& n, const PollardRhoParams& params);

}  // namespace LargePrimeNumbers
