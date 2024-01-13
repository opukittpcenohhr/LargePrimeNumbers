#include "legendre_symbol.h"

#include <boost/multiprecision/cpp_int.hpp>
#include <optional>

#include "common.h"
#include "utility.h"

namespace LargePrimeNumbers {

int find_legendre_symbol(bigint n, int p) {
  if (n % p == 0) {
    return 0;
  }
  auto pow = powmod<long long>((n % p).convert_to<int>(), (p - 1) / 2, p);
  assert(pow == 1 || pow == p - 1);
  if (pow == 1) {
    return 1;
  } else {
    return -1;
  }
}

}  // namespace LargePrimeNumbers