#include <gtest/gtest.h>

#include "fermat_pseudoprimality_test.h"
#include "strong_pseudoprimality_test.h"
#include "testing_utility.h"
#include "trial_primality_test.h"

namespace LargePrimeNumbers {

TEST(TrialPrimalityTest, test) {
  const std::set<bigint> kFalsePositives = {};
  const bigint kMaxNumberToTest = boost::multiprecision::pow(bigint(10), 10);

  test_primality_test(is_prime_trial, "is_prime_trial", kFalsePositives,
                      kMaxNumberToTest);
}

TEST(FermatPseudoprimalityTest, test) {
  const static std::set<bigint> kCarmichaelNumbers = {
      561,
      29341,
      63973,
      512461,
      bigint("464052305161"),
      bigint("1436697831295441"),
      bigint("60977817398996785"),
      bigint("7156857700403137441"),
      bigint("1791562810662585767521"),
  };
  const std::array<int, 6> kTestBases = {2, 3, 5, 7, 9, 11};

  auto test_is_fermat_pseudoprime = [&kTestBases](const bigint &n) {
    return is_fermat_pseudoprime(n, kTestBases);
  };

  test_primality_test(test_is_fermat_pseudoprime, "is_fermat_pseudoprime",
                      kCarmichaelNumbers);
}

TEST(StrongPseudoprimalityTest, test) {
  const std::set<bigint> kFalsePositives = {};
  const std::array<int, 6> kTestBases = {2, 3, 5, 7, 9, 11};

  auto test_is_strong_pseudoprime = [&kTestBases](const bigint &n) {
    return is_strong_pseudoprime(n, kTestBases);
  };

  test_primality_test(test_is_strong_pseudoprime, "is_strong_pseudoprime",
                      kFalsePositives);
}

}  // namespace LargePrimeNumbers
