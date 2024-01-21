#include <gtest/gtest.h>

#include "find_factor_quadratic_sieve.h"
#include "pollard_rho_find_factor.h"
#include "pollard_rho_one_find_factor.h"
#include "testing_utility.h"
#include "trial_find_factor.h"

using namespace LargePrimeNumbers;

namespace {
const bigint kBigNumberThreshold = boost::multiprecision::pow(bigint(10), 30);
}

TEST(TrialFindFactorTest, test) {
  const static std::set<bigint> exclusions = {};

  test_find_factor(find_factor_trial, "find_factor_trial", exclusions,
                   std::nullopt, 10);
}

TEST(PollardRhoFindFactorTest, test) {
  auto kTestParams = PollardRhoParams{1000000, {2, 3, 5}};
  const std::set<bigint> kExclusions = {};

  auto test_find_factor_pollard_rho = [&kTestParams](const bigint &n) {
    return find_factor_pollard_rho(n, kTestParams);
  };
  test_find_factor(test_find_factor_pollard_rho, "find_factor_pollard_rho",
                   kExclusions, std::nullopt, kBigNumberThreshold);
}

TEST(PollardRhoOneFindFactorTest, test) {
  auto kTestParams = PollardRhoOneParams{10000, {2, 3, 5}};
  const std::set<bigint> kExclusions = {
      464052305161,
      bigint("9999999940000000073359"),
  };

  auto test_find_factor_pollard_rho_one = [&kTestParams](const bigint &n) {
    return find_factor_pollard_rho_one(n, kTestParams);
  };
  test_find_factor(test_find_factor_pollard_rho_one,
                   "find_factor_pollard_rho_one", kExclusions, std::nullopt,
                   kBigNumberThreshold);
}

TEST(QuadraticSieveFactorTest, test) {
  constexpr auto kTestParams = QuadraticSieveParams{2000, 50000000, 2.0};
  const std::set<bigint> kExclusions = {};

  auto test_find_factor_quadratic_sieve = [&kTestParams](const bigint &n) {
    return find_factor_quadratic_sieve(n, kTestParams);
  };

  test_find_factor(test_find_factor_quadratic_sieve,
                   "find_factor_quadratic_sieve", kExclusions,
                   kBigNumberThreshold, std::nullopt);
}
