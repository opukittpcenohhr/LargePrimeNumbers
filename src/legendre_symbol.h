#pragma once

#include <boost/multiprecision/cpp_int.hpp>
#include <optional>

#include "common.h"

namespace Project {

int find_legendre_symbol(bigint n, int p);

}  // namespace Project