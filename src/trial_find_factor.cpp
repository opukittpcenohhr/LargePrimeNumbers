#include "trial_find_factor.h"

#include <boost/multiprecision/cpp_int.hpp>
#include <optional>

#include "common.h"

namespace Project {

std::optional<bigint> find_factor_trial(bigint n) {
  for (bigint i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      return i;
    }
  }
  return std::nullopt;
}

}  // namespace Project