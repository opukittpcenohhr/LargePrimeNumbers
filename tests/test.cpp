#include <gtest/gtest.h>

#include "naive_primary_test.h"

TEST(NaiveTest, test) {
  EXPECT_EQ(Project::is_prime_naive(3), true);
  EXPECT_EQ(Project::is_prime_naive(4), false);
}