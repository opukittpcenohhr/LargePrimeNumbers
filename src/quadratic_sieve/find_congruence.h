#pragma once

#include "common.h"

namespace LargePrimeNumbers {

// find x, such as x^2 = n (mod p)
bigint find_congruence(const bigint& n, const bigint& p);

std::vector<bigint> find_all_congruences(const bigint& n, const bigint& p);

}  // namespace LargePrimeNumbers
