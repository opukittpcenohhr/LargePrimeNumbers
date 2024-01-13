#include <gtest/gtest.h>

#include "pollard_rho_find_factor.h"
#include "pollard_rho_one_find_factor.h"
#include "quadratic_sieve.h"
#include "testing_utility.h"
#include "trial_find_factor.h"

using namespace LargePrimeNumbers;

TEST(TrialFindFactorTest, test) {
  const static std::set<bigint> exclusions = {};

  test_find_factor(find_factor_trial, "find_factor_trial", exclusions,
                   std::nullopt, 10);
}

TEST(PollardRhoFindFactorTest, test) {
  const static std::set<bigint> exclusions = {};
  constexpr auto TEST_PARAMS = PollardRhoParams<int, 3>{1000000, {2, 3, 5}};

  test_find_factor(find_factor_pollard_rho<TEST_PARAMS>,
                   "find_factor_pollard_rho", exclusions, std::nullopt, 30);
}

TEST(PollardRhoOneFindFactorTest, test) {
  constexpr auto TEST_PARAMS = PollardRhoOneParams<int, 3>{10000, {2, 3, 5}};

  const static std::set<bigint> exclusions = {
      464052305161,
      bigint("9999999940000000073359"),
  };

  test_find_factor(find_factor_pollard_rho_one<TEST_PARAMS>,
                   "find_factor_pollard_rho_one", exclusions, std::nullopt, 30);
}

TEST(QuadraticSieveFactorTest, test) {
  constexpr auto LARGE_TESTS_PARAMS = QuadraticSieveParams{2000, 50000000, 2.0};
  const static std::set<bigint> LARGE_TEST_EXCLUSIONS = {};

  test_find_factor(find_factor_quadratic_sieve<LARGE_TESTS_PARAMS>,
                   "find_factor_quadratic_sieve", LARGE_TEST_EXCLUSIONS, 30,
                   std::nullopt);
}