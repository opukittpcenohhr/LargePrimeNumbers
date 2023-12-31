#pragma once

#include <boost/multiprecision/cpp_int.hpp>
#include <optional>

#include "common.h"

namespace Project {

std::vector<int> find_factor_base(bigint n, size_t factors_count);

}  // namespace Project