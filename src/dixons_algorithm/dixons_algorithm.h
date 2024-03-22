#pragma once

#include <optional>
#include <span>

#include "common.h"
#include "f2_matrix.h"
#include "legendre_symbol.h"
#include "utility.h"

namespace LargePrimeNumbers {

class DixonsAlgorithm {
public:
  explicit DixonsAlgorithm(const bigint& n,
                           const std::vector<size_t>& factor_base,
                           int fill_factor = 3)
      : n_(n),
        factor_base_(factor_base),
        factorized_candidates_{},
        matrix_(fill_factor * factor_base.size() + 1,
                (1 + fill_factor) * factor_base.size() + 1),
        factorization_powers_cache_(factor_base_.size()) {}

  void process_candidates(std::span<const bigint> candidates);

  // Checks if g(r) = r * r mod n can be factorized over factor base, and if so,
  // saves factorization powers to matrix for further gaussian elimination
  void process_candidate(const bigint& candidate);

  std::optional<bigint> find_factor();

private:
  bigint perform_polynomial_factorization_over_factor_base(const bigint& r);

  void factorize_over_factor_base_and_fill_powers_matrix(const bigint& r);

  // Checks if number corresponding to i-th row of matrix can be used to find a
  // factor of n
  std::optional<bigint> check_factor_candidate(size_t i) const;

  bigint n_;
  std::vector<size_t> factor_base_;
  std::vector<bigint> factorized_candidates_;
  F2Matrix matrix_;

  std::vector<size_t> factorization_powers_cache_;
};

}  // namespace LargePrimeNumbers
