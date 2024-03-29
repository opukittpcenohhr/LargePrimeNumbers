#include "find_factor_quadratic_sieve.h"

#include <boost/multiprecision/cpp_dec_float.hpp>
#include <optional>

#include "common.h"
#include "dixons_algorithm.h"
#include "find_congruence.h"
#include "find_factor_base.h"

namespace LargePrimeNumbers {

std::vector<bigint> perform_sieving(
    const bigint& n, const std::vector<size_t>& factor_base,
    const QuadraticSieveParams& params) {
  auto s = boost::multiprecision::sqrt(n) + 1;
  // We are considering a segment of [s, ... s + 2 * M)
  // so index i in array corresponds to r = i + s, and value to factor is f(r) =
  // r * r mod n
  auto prime_factors_log_sum = std::vector<float>(2 * params.M);

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

  auto n_log =
      boost::multiprecision::log(boost::multiprecision::cpp_dec_float_100(n))
          .convert_to<double>();
  // approximation of log(max(f(r)))
  double target = (n_log) / 2 + log(2 * params.M);
  double threshold = target - params.T * log(factor_base.back());
  BOOST_LOG_TRIVIAL(debug) << "target: " << target
                           << " threshold: " << threshold;

  std::vector<bigint> candidates;

  for (size_t index = 0; index < 2 * params.M; index++) {
    if (prime_factors_log_sum[index] >= threshold) {
      candidates.emplace_back(index + s);
    }
  }
  return candidates;
}

std::optional<bigint> find_factor_quadratic_sieve(
    const bigint& n, const QuadraticSieveParams& params) {
  auto factor_base = find_factor_base(n, params.factor_base_size);
  BOOST_LOG_TRIVIAL(info) << "factor base found, max factor base: "
                          << factor_base.back();
  auto candidates = perform_sieving(n, factor_base, params);
  BOOST_LOG_TRIVIAL(info) << "found " << candidates.size() << " candidates";
  DixonsAlgorithm dixons_algorithm(n, factor_base);
  dixons_algorithm.process_candidates(candidates);
  return dixons_algorithm.find_factor();
}

}  // namespace LargePrimeNumbers
