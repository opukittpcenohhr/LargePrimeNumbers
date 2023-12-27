#pragma once

#include <boost/multiprecision/cpp_int.hpp>
#include <optional>

#include "common.h"

namespace Project {

std::optional<bigint> find_factor_pollard_rho_one(
    bigint n, size_t max_iterations = 100000,
    std::vector<bigint> bases = {2, 3, 5, 7, 11});

}  // namespace Project
