#include <gtest/gtest.h>

#include "bhascara_brounker_sequence.h"
#include "common.h"

namespace LargePrimeNumbers {

namespace {

const bigint n = bigint("13");
const bigint sqrt_n = bigint("3");
const std::vector<BhascaraBrounkerSequenceItem> expected_items = {
    {
        // 0
        .a = 0,
        .b = 0,
        .c = 1,
        .p = 1,
    },
    {
        // 1
        .a = 3,
        .b = 3,
        .c = 4,
        .p = 3,
    },
    {
        // 2
        .a = 1,
        .b = 1,
        .c = 3,
        .p = 4,
    },
    {
        // 3
        .a = 1,
        .b = 2,
        .c = 3,
        .p = 7,
    },
    {
        // 4
        .a = 1,
        .b = 1,
        .c = 4,
        .p = 11,
    },
    {
        // 5
        .a = 1,
        .b = 3,
        .c = 1,
        .p = 5,
    },
    {
        // 6
        .a = 6,
        .b = 3,
        .c = 4,
        .p = 2,
    },
    {
        // 7
        .a = 1,
        .b = 1,
        .c = 3,
        .p = 7,
    }};

}  // namespace

TEST(BhascaraBrounkerSequence, test) {
  std::vector<BhascaraBrounkerSequenceItem> sequence;
  BhascaraBrounkerSequenceItem f, s;
  std::tie(f, s) = get_initial_brounker_sequence_items(n, sqrt_n);
  sequence.push_back(f);
  sequence.push_back(s);
  for (size_t i = 0; i < expected_items.size(); i++) {
    if (i >= sequence.size()) {
      sequence.push_back(generate_next_brounker_sequence_item_mod_n(
          sequence[i - 1], sequence[i - 2], n, sqrt_n));
    }
    EXPECT_EQ(sequence[i], expected_items[i]);
  }
}

}  // namespace LargePrimeNumbers
