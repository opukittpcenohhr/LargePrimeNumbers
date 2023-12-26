#include <boost/multiprecision/cpp_int.hpp>

#include "fermat_pseudoprimarity_test.h"
#include "utility.h"

namespace Project {

bool is_fermat_pseudoprime(bigint n) {
  static const std::array<bigint, 6> BASES_TO_TEST = {2, 3, 5, 7, 9, 11};

  for (const auto& base : BASES_TO_TEST) {
    if (gcd(base, n) != 1) {
      // We know, that either base == n or n is not prime
      // although we are cant simply check this two cases (and probably return
      // false), since number is considered pseudoprime, only if it pseudoprime
      // for all relatively composite bases, and this is not the case
      continue;
    }
    if (powmod<bigint>(base, n - 1, n) != 1) {
      return false;
    }
  }

  return true;
}

}  // namespace Project