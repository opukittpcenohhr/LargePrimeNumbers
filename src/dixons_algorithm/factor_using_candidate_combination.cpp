#include "factor_using_candidate_combination.h"

#include <map>
#include <optional>
#include <random>

#include "common.h"
#include "f2_matrix.h"
#include "legendre_symbol.h"
#include "utility.h"

namespace LargePrimeNumbers {

bool FactorUsingCandidateCombination::process_candidate(
    const bigint& candidate) {
  if (processed_enough_candidates()) {
    return false;
  }
  reset_factorization_powers_cache();
  auto factorization_remainder =
      perform_polynomial_factorization_over_factor_base(candidate);
  if (factorization_remainder == 1) {
    fill_powers_matrix(candidate);
  }
  return factorization_remainder == 1;
}

void FactorUsingCandidateCombination::process_candidates(
    std::span<const bigint> candidates) {
  for (const auto& candidate : candidates) {
    process_candidate(candidate);
    if (processed_enough_candidates()) {
      break;
    }
  }
}

bool FactorUsingCandidateCombination::processed_enough_candidates() const {
  return factorized_candidates_.size() >=
         number_of_factored_candidates_required_;
}

bigint FactorUsingCandidateCombination::
    perform_polynomial_factorization_over_factor_base(const bigint& r) {
  bigint g_r = mulmod(r, r, n_);
  for (size_t factor_index = 0; factor_index < factor_base_.size();
       factor_index++) {
    while (g_r % factor_base_[factor_index] == 0 && g_r > 1) {
      factorization_powers_cache_[factor_index]++;
      g_r = g_r / factor_base_[factor_index];
    }
  }
  return g_r;
}

void FactorUsingCandidateCombination::fill_powers_matrix(const bigint& r) {
  size_t i = factorized_candidates_.size();
  for (size_t factor_index = 0; factor_index < factor_base_.size();
       factor_index++) {
    matrix_[i][factor_index] = (factorization_powers_cache_[factor_index] % 2);
  }
  matrix_[i][factor_base_.size() + i] = true;
  factorized_candidates_.push_back(r);
}

std::optional<bigint> FactorUsingCandidateCombination::get_factor_if_possible(
    size_t i) const {
  bool is_complete_square = true;
  for (size_t j = 0; j < factor_base_.size(); j++) {
    is_complete_square &= (matrix_[i][j] == 0);
  }
  bool is_empty_row = true;
  for (size_t factor_index = 0; factor_index < factor_base_.size();
       factor_index++) {
    is_empty_row &= (matrix_[i][factor_base_.size() + factor_index] == 0);
  }
  if (is_complete_square && !is_empty_row) {
    bigint x = 1;
    bigint y = 1;
    for (size_t candidate_index = 0;
         candidate_index < factorized_candidates_.size(); candidate_index++) {
      if (matrix_[i][factor_base_.size() + candidate_index]) {
        auto g_r = mulmod<bigint>(
            factorized_candidates_[candidate_index],
            factorized_candidates_[candidate_index], n_);
        x = x * g_r;
        y = y * factorized_candidates_[candidate_index];
      }
    }
    assert(((x) % n_) == ((y * y) % n_));
    x = boost::multiprecision::sqrt(x);
    assert(((x * x) % n_) == ((y * y) % n_));
    if (auto factor = factor_with_gcd<bigint>(n_, x + y)) {
      return factor;
    }
  }
  return std::nullopt;
}

std::optional<bigint> FactorUsingCandidateCombination::find_factor() {
  BOOST_LOG_TRIVIAL(info) << "number of completely factorized candidates : "
                          << factorized_candidates_.size();
  reduce_to_row_echelon_form(factor_base_.size(), matrix_);
  for (size_t i = 0; i < factorized_candidates_.size(); i++) {
    if (auto factor = get_factor_if_possible(i)) {
      return factor.value();
    }
  }
  return std::nullopt;
}

void FactorUsingCandidateCombination::reset_factorization_powers_cache() {
  std::fill(
      factorization_powers_cache_.begin(), factorization_powers_cache_.end(),
      0);
}

}  // namespace LargePrimeNumbers
