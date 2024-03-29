#pragma once

#include <optional>

#include "common.h"

namespace LargePrimeNumbers {

struct DixonParams {
  size_t factor_base_size;
  uint32_t random_seed = 31;
};

std::optional<bigint> dixon_find_factor(
    const bigint& n, const DixonParams& params);

}  // namespace LargePrimeNumbers
