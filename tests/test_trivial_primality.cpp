#include <gtest/gtest.h>

#include "testing_utility.h"
#include "trial_primality_test.h"

TEST(TrialPrimalityTest, test) {
  using namespace Project;
  const static std::set<bigint> false_positives = {};

  test_primality_test(is_prime_trial, "is_prime_trial", false_positives);
}