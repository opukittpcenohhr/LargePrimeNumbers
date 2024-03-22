#include "find_factor_cfrac.h"

#include <optional>

#include "bhascara_brounker_sequence.h"
#include "common.h"
#include "dixons_algorithm.h"
#include "find_factor_base.h"
#include "utility.h"

namespace LargePrimeNumbers {

std::optional<bigint> find_factor_cfrac(
    const bigint& n, const CfracParams& params) {
  bigint sqrt_n = boost::multiprecision::sqrt(n);
  // If n is a perfect square, Bhascara-Brounker sequence is not defined
  if (sqrt_n * sqrt_n == n) {
    return sqrt_n;
  }
  auto factor_base = find_factor_base(n, params.factor_base_size);
  BOOST_LOG_TRIVIAL(info) << "factor base found, max factor base: "
                          << factor_base.back()
                          << " factor base size: " << factor_base.size();

  DixonsAlgorithm dixons_algorithm(n, factor_base);

  BhascaraBrounkerSequenceItem current_item, previous_item;
  std::tie(previous_item, current_item) =
      get_initial_brounker_sequence_items(n, sqrt_n);

  size_t total_candidates = 0;
  size_t factored_candidates = 0;
  while (!dixons_algorithm.factored_enough_candidates()) {
    auto new_item = generate_next_brounker_sequence_item_mod_n(
        current_item, previous_item, n, sqrt_n);
    total_candidates++;
    if (dixons_algorithm.process_candidate(new_item.p)) {
      factored_candidates++;
      if (factored_candidates % 100 == 0) {
        BOOST_LOG_TRIVIAL(debug)
            << "found factored candidate, total candidates: "
            << total_candidates
            << ", factored candidates: " << factored_candidates;
      }
    }
    previous_item = current_item;
    current_item = new_item;
  }
  BOOST_LOG_TRIVIAL(info) << "total candidates: " << total_candidates
                          << ", factored candidates: " << factored_candidates
                          << ", ratio: "
                          << (double)factored_candidates /
                                 (double)total_candidates;
  return dixons_algorithm.find_factor();
}

}  // namespace LargePrimeNumbers
