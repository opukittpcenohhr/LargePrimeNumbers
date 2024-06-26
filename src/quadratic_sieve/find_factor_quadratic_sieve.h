#pragma once

#include <optional>

#include "common.h"

namespace LargePrimeNumbers {

struct QuadraticSieveParams {
  size_t factor_base_size;
  size_t M;
  double T;
};

std::optional<bigint> find_factor_quadratic_sieve(
    const bigint& n, const QuadraticSieveParams& params);

}  // namespace LargePrimeNumbers
