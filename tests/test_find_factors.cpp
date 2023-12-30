#include <gtest/gtest.h>

#include "pollard_rho_find_factor.h"
#include "pollard_rho_one_find_factor.h"
#include "testing_utility.h"
#include "trial_find_factor.h"

using namespace Project;

TEST(TrialFindFactorTest, test) {
  using namespace Project;
  const static std::set<bigint> exclusions = {};

  test_find_factor(find_factor_trial, "find_factor_trial", exclusions, 10);
}

TEST(PollardRhoFindFactorTest, test) {
  using namespace Project;
  const static std::set<bigint> exclusions = {};
  constexpr auto TEST_PARAMS = PollardRhoParams<int, 3>{1000000, {2, 3, 5}};

  test_find_factor(find_factor_pollard_rho<TEST_PARAMS>,
                   "find_factor_pollard_rho", exclusions);
}

TEST(PollardRhoOneFindFactorTest, test) {
  constexpr auto TEST_PARAMS = PollardRhoOneParams<int, 3>{10000, {2, 3, 5}};

  using namespace Project;
  const static std::set<bigint> exclusions = {
      464052305161,
      bigint("9999999940000000073359"),
  };

  test_find_factor(find_factor_pollard_rho_one<TEST_PARAMS>,
                   "find_factor_pollard_rho_one", exclusions);
}