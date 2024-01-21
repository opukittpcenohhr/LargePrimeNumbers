#include "dixons_algorithm.h"

#include <map>
#include <optional>
#include <random>

#include "common.h"
#include "f2_matrix.h"
#include "legendre_symbol.h"
#include "utility.h"

namespace LargePrimeNumbers {

// factorizes g(r) = r * r mod n over factor base and saves result to
// factorization_powers
bigint perform_polynomial_factorization_over_factor_base(
    const bigint& r, const bigint& n, const std::vector<size_t>& factor_base,
    std::vector<size_t>& factorization_powers) {
  std::fill(factorization_powers.begin(), factorization_powers.end(), 0);
  bigint g_r = mulmod(r, r, n);
  for (size_t factor_index = 0; factor_index < factor_base.size();
       factor_index++) {
    while (g_r % factor_base[factor_index] == 0 && g_r > 1) {
      factorization_powers[factor_index]++;
      g_r = g_r / factor_base[factor_index];
    }
  }
  return g_r;
}

// factorize g(r) = r * r mod n over factor base and save factor powers in
// matrix for further gaussian elimination
std::pair<F2Matrix, std::vector<bigint>>
factorize_over_factor_base_and_fill_powers_matrix(
    const bigint& n, const std::vector<bigint>& candidates,
    const std::vector<size_t>& factor_base) {
  constexpr size_t kFillFactor = 3;

  auto max_factored_candidates = kFillFactor * factor_base.size();
  std::vector<bigint> factorized_candidates;
  factorized_candidates.reserve(max_factored_candidates);

  std::vector<size_t> factorization_powers(factor_base.size());

  size_t factorized_count = 0;
  F2Matrix matrix(kFillFactor * factor_base.size() + 1,
                  (1 + kFillFactor) * factor_base.size() + 1);

  auto fill_matrix_with_factorization_powers = [&factorization_powers, &matrix,
                                                &factor_base](size_t i) {
    for (size_t factor_index = 0; factor_index < factor_base.size();
         factor_index++) {
      matrix[i][factor_index] = (factorization_powers[factor_index] % 2);
    }
  };

  for (const auto& candidate : candidates) {
    auto factorization_remainder =
        perform_polynomial_factorization_over_factor_base(
            candidate, n, factor_base, factorization_powers);
    if (factorization_remainder == 1) {
      fill_matrix_with_factorization_powers(factorized_count);
      matrix[factorized_count][factor_base.size() + factorized_count] = true;
      factorized_candidates.push_back(candidate);
      factorized_count++;
    }
    if (factorized_candidates.size() == max_factored_candidates) {
      break;
    }
  }
  return {matrix, factorized_candidates};
}

// Checks if number given by i-th row of matrix can be used to find a factor
// of n
std::optional<bigint> check_factor_candidate(
    const bigint& n, const F2Matrix& matrix,
    const std::vector<bigint>& factorized_candidates, size_t factor_base_size,
    size_t i) {
  bool is_complete_square = true;
  for (size_t j = 0; j < factor_base_size; j++) {
    is_complete_square &= (matrix[i][j] == 0);
  }
  bool is_empty_row = true;
  for (size_t factor_index = 0; factor_index < factor_base_size;
       factor_index++) {
    is_empty_row &= (matrix[i][factor_base_size + factor_index] == 0);
  }
  if (is_complete_square && !is_empty_row) {
    bigint x = 1;
    bigint y = 1;
    for (size_t candidate_index = 0;
         candidate_index < factorized_candidates.size(); candidate_index++) {
      if (matrix[i][factor_base_size + candidate_index]) {
        auto g_r = mulmod<bigint>(factorized_candidates[candidate_index],
                                  factorized_candidates[candidate_index], n);
        x = x * g_r;
        y = y * factorized_candidates[candidate_index];
      }
    }
    assert(((x) % n) == ((y * y) % n));
    x = boost::multiprecision::sqrt(x);
    assert(((x * x) % n) == ((y * y) % n));
    if (auto factor = check_potential_factor<bigint>(n, x + y)) {
      return factor;
    }
  }
  return std::nullopt;
}

std::optional<bigint> find_factor_dixon(
    const bigint& n, const std::vector<bigint>& candidates,
    const std::vector<size_t>& factor_base) {
  F2Matrix matrix;
  std::vector<bigint> factorized_candidates;
  tie(matrix, factorized_candidates) =
      factorize_over_factor_base_and_fill_powers_matrix(n, candidates,
                                                        factor_base);
  BOOST_LOG_TRIVIAL(info) << "number of completely factorized candidates : "
                          << factorized_candidates.size();

  perform_gaussian_elimination(matrix, factor_base.size());
  for (size_t i = 0; i < factorized_candidates.size(); i++) {
    if (auto factor = check_factor_candidate(n, matrix, factorized_candidates,
                                             factor_base.size(), i)) {
      return factor.value();
    }
  }
  return std::nullopt;
}

}  // namespace LargePrimeNumbers
