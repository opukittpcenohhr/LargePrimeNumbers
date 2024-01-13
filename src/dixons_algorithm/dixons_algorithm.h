#pragma once
#include <boost/multiprecision/cpp_int.hpp>
#include <map>
#include <optional>
#include <random>

#include "common.h"
#include "f2_matrix.h"
#include "legendre_symbol.h"
#include "logging.h"
#include "utility.h"

namespace LargePrimeNumbers {

inline bigint get_polynomial_value(const bigint& r, const bigint& n) {
  return mulmod(r, r, n);
}

// factorizes g(r) = r * r mod n over factor base
inline bigint perform_polynomial_factorization_over_factor_base(
    const bigint& r, const bigint& n, std::vector<int>& factorization_powers,
    const std::vector<int>& factor_base) {
  std::fill(factorization_powers.begin(), factorization_powers.end(), 0);
  bigint g_r = get_polynomial_value(r, n);
  assert(g_r < n);
  for (size_t factor_index = 0; factor_index < factor_base.size();
       factor_index++) {
    while (g_r % factor_base[factor_index] == 0 && g_r > 1) {
      factorization_powers[factor_index]++;
      g_r = g_r / factor_base[factor_index];
    }
  }
  return g_r;
}

template <size_t factor_base_size>
std::optional<bigint> find_factor_dixon(bigint n,
                                        std::vector<bigint> r_candidates,
                                        std::vector<int> factor_base) {
  assert(factor_base.size() == factor_base_size);

  constexpr size_t FILL_FACTOR = 3;

  std::vector<int> factorization_powers(factor_base_size);
  std::vector<bigint> r;
  r.reserve(FILL_FACTOR * factor_base_size);

  size_t factorized_count = 0;
  F2Matrix<FILL_FACTOR * factor_base_size + 1,
           (1 + FILL_FACTOR) * factor_base_size + 1>
      matrix;

  for (size_t i = 0; i < r_candidates.size(); i++) {
    auto factorization_remainder =
        perform_polynomial_factorization_over_factor_base(
            r_candidates[i], n, factorization_powers, factor_base);
    if (factorization_remainder == 1) {
      if (r.size() == factor_base_size * FILL_FACTOR) {
        break;
      }
      for (size_t factor_index = 0; factor_index < factor_base_size;
           factor_index++) {
        matrix[factorized_count][factor_index] =
            (factorization_powers[factor_index] % 2);
      }
      matrix[factorized_count][factor_base_size + factorized_count] = 1;
      r.push_back(r_candidates[i]);
      factorized_count++;
    }
  }
  INFO() << "number of completely factorized r's : " << factorized_count;
  perform_gaussian_elimination(matrix, factor_base_size);
  for (size_t i = 0; i < factorized_count; i++) {
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
      for (size_t candidate_index = 0; candidate_index < factorized_count;
           candidate_index++) {
        if (matrix[i][factor_base_size + candidate_index]) {
          auto g_r = get_polynomial_value(r[candidate_index], n);
          x = x * g_r;
          y = y * r[candidate_index];
        }
      }
      assert(((x) % n) == ((y * y) % n));
      x = boost::multiprecision::sqrt(x);
      assert(((x * x) % n) == ((y * y) % n));
      if (auto factor = check_potential_factor<bigint>(n, x + y)) {
        return factor;
      }
    }
  }
  return std::nullopt;
}

}  // namespace LargePrimeNumbers