#include "dixons_algorithm.h"

#include <map>
#include <optional>
#include <random>

#include "common.h"
#include "f2_matrix.h"
#include "legendre_symbol.h"
#include "utility.h"

namespace LargePrimeNumbers {

bigint DixonsAlgorithm::perform_polynomial_factorization_over_factor_base(
    const bigint& r) {
  std::fill(
      factorization_powers_cache_.begin(), factorization_powers_cache_.end(),
      0);
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

bool DixonsAlgorithm::factorize_over_factor_base_and_fill_powers_matrix(
    const bigint& r) {
  auto factorization_remainder =
      perform_polynomial_factorization_over_factor_base(r);
  if (factorization_remainder == 1) {
    size_t i = factorized_candidates_.size();
    for (size_t factor_index = 0; factor_index < factor_base_.size();
         factor_index++) {
      matrix_[i][factor_index] =
          (factorization_powers_cache_[factor_index] % 2);
    }
    matrix_[i][factor_base_.size() + i] = true;
    factorized_candidates_.push_back(r);
    return true;
  }
  return false;
}

std::optional<bigint> DixonsAlgorithm::check_factor_candidate(size_t i) const {
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
    if (auto factor = check_potential_factor<bigint>(n_, x + y)) {
      return factor;
    }
  }
  return std::nullopt;
}

void DixonsAlgorithm::process_candidates(std::span<const bigint> candidates) {
  for (const auto& candidate : candidates) {
    process_candidate(candidate);
  }
}

bool DixonsAlgorithm::process_candidate(const bigint& candidate) {
  if (factored_enough_candidates()) {
    return false;
  }
  return factorize_over_factor_base_and_fill_powers_matrix(candidate);
}

bool DixonsAlgorithm::factored_enough_candidates() const {
  return factorized_candidates_.size() >=
         number_of_factored_candidates_required_;
}

std::optional<bigint> DixonsAlgorithm::find_factor() {
  BOOST_LOG_TRIVIAL(info) << "number of completely factorized candidates : "
                          << factorized_candidates_.size();
  perform_gaussian_elimination(matrix_, factor_base_.size());
  for (size_t i = 0; i < factorized_candidates_.size(); i++) {
    if (auto factor = check_factor_candidate(i)) {
      return factor.value();
    }
  }
  return std::nullopt;
}

}  // namespace LargePrimeNumbers
