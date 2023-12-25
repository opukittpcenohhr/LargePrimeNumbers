#include "naive_primary_test.h"

#include <boost/multiprecision/cpp_int.hpp>

namespace Project {

bool is_prime_naive(bigint x) {
  for (bigint i = 2; i * i <= x; i++) {
    if (x % i == 0) {
      return false;
    }
  }
  return true;
}

}  // namespace Project