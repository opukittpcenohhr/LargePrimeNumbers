#pragma once

#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <optional>

#include "common.h"
#include "dixons_algorithm.h"
#include "find_congruence.h"
#include "find_factor_base.h"
#include "logging.h"

namespace Project {

struct QuadraticSieveParams {
  const size_t factor_base_size;
  const size_t M;
  const double T;
};

template <QuadraticSieveParams params>
std::optional<bigint> find_factor_quadratic_sieve(bigint n) {
  using namespace std;
  auto factor_base = find_factor_base(n, params.factor_base_size);
  INFO() << "factor base found, max factor base: " << factor_base.back();

  auto s = boost::multiprecision::sqrt(n) + 1;
  // We are considering a segment of [s, ... s + 2 * M)
  // so index i in array corresponds to r = i + s, and value to factor is f(r) =
  // r * r mod n
  // We use unique_ptr to allocate array on heap, not stack
  auto prime_factors_log_sum = std::vector<double>(2 * params.M);

  for (auto p : factor_base) {
    auto congruences = find_all_congruences(n, p);
    for (auto congruence : congruences) {
      // add log(p) to all r's inside interval, that are equal to
      // congruence modulo p
      bigint first_number_in_interval = (s / p) * p + congruence;
      if (first_number_in_interval < s) {
        first_number_in_interval = first_number_in_interval + p;
      }
      assert(first_number_in_interval >= s);
      auto first_index = (first_number_in_interval - s).convert_to<size_t>();
      for (size_t index = first_index; index < 2 * params.M; index += p) {
        prime_factors_log_sum[index] += log(p);
      }
    }
  }
  INFO() << "sieving done";

  auto n_log =
      boost::multiprecision::log(boost::multiprecision::cpp_dec_float_100(n))
          .convert_to<double>();
  // approximation of log(max(f(r)))
  double target = (n_log) / 2 + log(2 * params.M);
  double threshold = target - params.T * log(factor_base.back());
  DEBUG() << "target: " << target << " threshold: " << threshold;

  std::vector<bigint> candidates;

  for (size_t index = 0; index < 2 * params.M; index++) {
    if (prime_factors_log_sum[index] >= threshold) {
      candidates.push_back(index + s);
    }
  }
  INFO() << "found " << candidates.size() << " candidates";

  return find_factor_dixon<params.factor_base_size>(n, candidates, factor_base);
}

}  // namespace Project