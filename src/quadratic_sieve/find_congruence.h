#pragma once
#include <boost/multiprecision/cpp_int.hpp>
#include <map>
#include <optional>
#include <random>

#include "common.h"

namespace Project {

// find x, such as x^2 = n (mod p)
int find_congruence(bigint n, int p);

std::vector<int> find_all_congruences(bigint n, int p);

}  // namespace Project