#include <gtest/gtest.h>

#include "f2_matrix.h"
#include "find_congruence.h"
#include "find_factor_base.h"
#include "legendre_symbol.h"
#include "utility.h"

namespace LargePrimeNumbers {

namespace {
const bigint kQuadraticSieveN = bigint("4999486012441");
const std::vector<size_t> kExpectedFactorBases = {2,  3,  5,  7,  17,
                                                  19, 31, 43, 47, 59};
}  // namespace

TEST(LegendreSymbolTest, test) {
  EXPECT_EQ(find_legendre_symbol(35, 53), -1);
  EXPECT_EQ(find_legendre_symbol(68, 233), -1);
  EXPECT_EQ(find_legendre_symbol(126, 509), 1);
  EXPECT_EQ(find_legendre_symbol(672, 1297), 1);
  EXPECT_EQ(find_legendre_symbol(1235, 3499), -1);
  EXPECT_EQ(find_legendre_symbol(267980, 14647621), -1);
  EXPECT_EQ(find_legendre_symbol(63829163, 409482089), 1);
}

TEST(FindFactorBaseTest, test) {
  EXPECT_EQ(find_factor_base(kQuadraticSieveN, size(kExpectedFactorBases)),
            kExpectedFactorBases);
}

TEST(FindCongruenceTest, test) {
  auto test = [](const bigint &n, const bigint &p) {
    auto congruences = find_all_congruences(n, p);
    for (auto congruence : congruences) {
      EXPECT_EQ(n % p, mulmod(congruence, congruence, p));
    }
  };

  for (auto p : kExpectedFactorBases) {
    test(kQuadraticSieveN, p);
  }
  test(bigint("59469489332848408438249254427481121839977"), 48679);
}

}  // namespace LargePrimeNumbers
