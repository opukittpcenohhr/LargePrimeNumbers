#include "bhascara_brounker_sequence.h"

#include "common.h"
#include "utility.h"

namespace LargePrimeNumbers {

std::pair<BhascaraBrounkerSequenceItem, BhascaraBrounkerSequenceItem>
get_initial_brounker_sequence_items(const bigint& n, const bigint& sqrt_n) {
  return {
      {
          // 0-th item
          .a = 0,
          .b = 0,
          .c = 1,
          .p = 1,
      },
      {
          // 1-st item
          .a = sqrt_n,
          .b = sqrt_n,
          .c = n - sqrt_n * sqrt_n,
          .p = sqrt_n,
      }};
}

BhascaraBrounkerSequenceItem generate_next_brounker_sequence_item_mod_n(
    const BhascaraBrounkerSequenceItem& current_item,
    const BhascaraBrounkerSequenceItem& previous_item, const bigint& n,
    const bigint& sqrt_n) {
  auto a_next = (sqrt_n + current_item.b) / current_item.c;
  auto b_next = a_next * current_item.c - current_item.b;
  auto c_next = previous_item.c + a_next * (current_item.b - b_next);
  auto tmp = mulmod<bigint>(a_next, current_item.p, n);
  auto p_next = addmod<bigint>(tmp, previous_item.p, n);
  return {
      .a = a_next,
      .b = b_next,
      .c = c_next,
      .p = p_next,
  };
}

}  // namespace LargePrimeNumbers
