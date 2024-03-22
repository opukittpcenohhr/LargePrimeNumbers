#include <iostream>

#include "common.h"
#include "find_factor_quadratic_sieve.h"
#include "legendre_symbol.h"

int main() {
  using namespace boost::multiprecision;
  using namespace std;

  constexpr auto params =
      LargePrimeNumbers::QuadraticSieveParams{10000, 500000000, 2.0};

  // >>> 969670948966462549277183 * 420728663328480145626943
  // 407968362227118674723680452077848647063019941569

  auto factor = LargePrimeNumbers::find_factor_quadratic_sieve(
      LargePrimeNumbers::bigint(
          "407968362227118674723680452077848647063019941569"),
      params);

  if (factor.has_value()) {
    cout << "found factor: " << factor.value() << endl;
  } else {
    cout << "found no factor" << endl;
  }
}
