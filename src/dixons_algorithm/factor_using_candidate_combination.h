#pragma once

#include <optional>
#include <ranges>
#include <span>

#include "common.h"
#include "f2_matrix.h"
#include "legendre_symbol.h"
#include "utility.h"

namespace LargePrimeNumbers {

// Try to find factor using some linear combination of g(r) = n * n mod n, where
// g(r) can be factored over factor base
class FactorUsingCandidateCombination {
public:
  FactorUsingCandidateCombination(
      const bigint& n, std::span<const size_t> factor_base, int fill_factor = 1)
      : n_(n),
        factor_base_(factor_base.begin(), factor_base.end()),
        number_of_factored_candidates_required_(
            factor_base.size() * fill_factor + 3),
        matrix_(
            number_of_factored_candidates_required_ + 1,
            number_of_factored_candidates_required_ + factor_base_.size()),
        factorization_powers_cache_(factor_base_.size()) {}

  // Checks if g(candidate) = candidate * candidate mod n can be factorized over
  // factor base, and if so, saves factorization powers to matrix for further
  // gaussian elimination
  bool process_candidate(const bigint& candidate);

  void process_candidates(std::span<const bigint> candidates);

  std::optional<bigint> find_factor();

  bool processed_enough_candidates() const;

private:
  bigint perform_polynomial_factorization_over_factor_base(const bigint& r);

  void fill_powers_matrix(const bigint& r);

  void reset_factorization_powers_cache();

  bool is_row_corresponds_to_complete_square(size_t i) const;

  bool is_row_corresponds_to_empty_subset(size_t i) const;

  // Checks if number corresponding to i-th row of matrix can be used to find a
  // factor of n
  std::optional<bigint> get_factor_if_possible(size_t i) const;

  bigint n_;
  std::vector<size_t> factor_base_;
  size_t number_of_factored_candidates_required_;
  std::vector<bigint> factorized_candidates_;
  F2Matrix matrix_;

  std::vector<size_t> factorization_powers_cache_;
};

}  // namespace LargePrimeNumbers
