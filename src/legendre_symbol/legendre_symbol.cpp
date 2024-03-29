#include "legendre_symbol.h"

#include <optional>

#include "common.h"
#include "utility.h"

namespace LargePrimeNumbers {

int find_legendre_symbol(const bigint& n, const bigint& p) {
  assert(p % 2 == 1);
  if (n % p == 0) {
    return 0;
  }
  auto pow = powmod<bigint>(n % p, (p - 1) / 2, p);
  assert(pow == 1 || pow == p - 1);
  return pow == 1 ? 1 : -1;
}

}  // namespace LargePrimeNumbers
