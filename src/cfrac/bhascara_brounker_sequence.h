#pragma once

#include "common.h"
#include "utility.h"

namespace LargePrimeNumbers {

struct BhascaraBrounkerSequenceItem {
  bigint a;
  bigint b;
  bigint c;
  bigint p;

  bool operator==(const BhascaraBrounkerSequenceItem& other) const = default;
};

std::pair<BhascaraBrounkerSequenceItem, BhascaraBrounkerSequenceItem>
get_initial_brounker_sequence_items(const bigint& n, const bigint& sqrt_n);

// We pass sqrt_n as a parameter to avoid recalculating it
BhascaraBrounkerSequenceItem generate_next_brounker_sequence_item_mod_n(
    const BhascaraBrounkerSequenceItem& current_item,
    const BhascaraBrounkerSequenceItem& previous_item, const bigint& n,
    const bigint& sqrt_n);

}  // namespace LargePrimeNumbers
