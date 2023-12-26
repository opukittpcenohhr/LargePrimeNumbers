#include <gtest/gtest.h>

#include "testing_utility.h"
#include "trial_find_factor.h"

TEST(TrialFindFactorTest, test) {
  using namespace Project;

  test_find_factor(find_factor_trial, "find_factor_trial");
}