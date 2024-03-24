#pragma once

#include <optional>

#include "common.h"

namespace LargePrimeNumbers {

std::optional<bigint> find_factor_trial(const bigint& n);

}  // namespace LargePrimeNumbers
