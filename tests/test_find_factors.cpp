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

std::optional<bigint> find_factor_pollard_rho_with_default_params(bigint n) {
  return find_factor_pollard_rho(n);
}

TEST(PollardRhoFindFactorTest, test) {
  using namespace Project;
  const static std::set<bigint> exclusions = {};

  test_find_factor(find_factor_pollard_rho_with_default_params,
                   "find_factor_pollard_rho", exclusions);
}

std::optional<bigint> find_factor_pollard_rho_one_with_default_params(
    bigint n) {
  return find_factor_pollard_rho_one(n);
}

TEST(PollardRhoOneFindFactorTest, test) {
  using namespace Project;
  const static std::set<bigint> exclusions = {
      464052305161,
      bigint("9999999940000000073359"),
  };

  test_find_factor(find_factor_pollard_rho_one_with_default_params,
                   "find_factor_pollard_rho_one", exclusions);
}