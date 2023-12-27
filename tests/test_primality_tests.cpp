#include <gtest/gtest.h>

#include "fermat_pseudoprimarity_test.h"
#include "testing_utility.h"
#include "trial_primality_test.h"

using namespace Project;

TEST(TrialPrimalityTest, test) {
  using namespace Project;
  const static std::set<bigint> false_positives = {};

  test_primality_test(is_prime_trial, "is_prime_trial", false_positives, 10);
}

bool is_fermat_pseudoprime_with_default_params(bigint n) {
  return is_fermat_pseudoprime(n);
}

TEST(FermatPseudoPrimalityTest, test) {
  using namespace Project;
  const static std::set<bigint> CARMICHAEL_NUMBERS = {
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

  test_primality_test(is_fermat_pseudoprime_with_default_params,
                      "is_fermat_pseudoprime", CARMICHAEL_NUMBERS);
}