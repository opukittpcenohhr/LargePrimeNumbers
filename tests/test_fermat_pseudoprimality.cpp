#include <gtest/gtest.h>

#include "fermat_pseudoprimarity_test.h"
#include "testing_utility.h"

TEST(FermatPseudoPrimalityTest, test) {
  using namespace Project;
  const static std::set<bigint> CARMICHAEL_NUMBERS = {561, 29341, 63973,
                                                      512461};

  test_primality_test(is_fermat_pseudoprime, "is_fermat_pseudoprime",
                      CARMICHAEL_NUMBERS);
}