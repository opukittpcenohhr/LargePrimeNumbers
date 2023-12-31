#pragma once

#include <boost/multiprecision/cpp_int.hpp>
#include <optional>

#include "common.h"

namespace Project {

std::optional<bigint> find_factor_trial(bigint n);

}  // namespace Project
