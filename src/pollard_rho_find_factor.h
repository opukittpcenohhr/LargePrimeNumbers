#include <boost/multiprecision/cpp_int.hpp>
#include <optional>

#include "common.h"

namespace Project {

std::optional<bigint> find_factor_pollard_rho(
    bigint n, size_t max_iterations = 1000000,
    std::vector<bigint> start_values = {2, 3, 5});

}  // namespace Project
