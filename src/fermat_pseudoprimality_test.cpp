#include <boost/multiprecision/cpp_int.hpp>

#include "fermat_pseudoprimarity_test.h"
#include "logging.h"
#include "utility.h"

namespace Project {

bool is_fermat_pseudoprime(bigint n, std::vector<bigint> bases) {
  INFO() << "testing if " << n << " is fermat pseudoprime";
  for (const auto& base : bases) {
    DEBUG() << "trying base " << base;
    if (gcd(base, n) != 1) {
      // We know, that either base == n or n is not prime
      // although we are cant simply check this two cases (and probably return
      // false), since number is considered pseudoprime, only if it pseudoprime
      // for all relatively composite bases, and this is not the case
      continue;
    }
    auto predicate_value = powmod<bigint>(base, n - 1, n);
    DEBUG() << "predicate_value is: " << predicate_value;
    if (predicate_value != 1) {
      return false;
    }
  }

  return true;
}

}  // namespace Project