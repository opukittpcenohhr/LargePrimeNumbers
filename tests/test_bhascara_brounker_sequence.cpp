#include <gtest/gtest.h>

#include "bhascara_brounker_sequence.h"
#include "common.h"

namespace LargePrimeNumbers {

namespace {

const bigint n = bigint("13");
const std::vector<BhascaraBrounker::Item> expected_items = {
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
  auto iterable = BhascaraBrounker::get_first_item(n);
  for (const auto& expected_item : expected_items) {
    EXPECT_EQ(*iterable, expected_item);
    ++iterable;
  }
}

}  // namespace LargePrimeNumbers
