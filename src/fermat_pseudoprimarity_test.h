#pragma once

#include <boost/multiprecision/cpp_int.hpp>

#include "common.h"

namespace Project {

bool is_fermat_pseudoprime(bigint x,
                           std::vector<bigint> bases = {2, 3, 5, 7, 9, 11});

}  // namespace Project