#include "dixon_find_factor.h"

#include <optional>

#include "common.h"
#include "factor_using_candidate_combination.h"
#include "find_factor_base.h"
#include "random.h"

namespace LargePrimeNumbers {

std::optional<bigint> dixon_find_factor(
    const bigint& n, const DixonParams& params) {
  auto factor_base = find_factor_base(n, params.factor_base_size);
  assert(!factor_base.empty());
  BOOST_LOG_TRIVIAL(info) << "factor base found, max factor base: "
                          << factor_base.back()
                          << " factor base size: " << factor_base.size();
  FactorUsingCandidateCombination factor_using_combination(
      n, std::move(factor_base));
  RandomBigint random(params.random_seed);
  while (!factor_using_combination.processed_enough_candidates()) {
    factor_using_combination.process_candidate(
        random.generate_uniform(1, n - 1));
  }
  return factor_using_combination.find_factor();
}

}  // namespace LargePrimeNumbers
