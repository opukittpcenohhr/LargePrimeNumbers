#pragma once

#include <optional>

#include "common.h"

namespace LargePrimeNumbers {

struct CfracParams {
  size_t factor_base_size;
};

std::optional<bigint> find_factor_cfrac(
    const bigint& n, const CfracParams& params);

}  // namespace LargePrimeNumbers
