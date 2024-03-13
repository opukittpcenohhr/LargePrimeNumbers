#include <iostream>

#include "common.h"
#include "find_factor_quadratic_sieve.h"
#include "legendre_symbol.h"

int main() {
  using namespace boost::multiprecision;
  using namespace std;

  constexpr auto params =
      LargePrimeNumbers::QuadraticSieveParams{2000, 50000000, 2.0};

  // >>> 175656509371887105761 * 338555568168236555657
  // 59469489332848408438249254427481121839977

  auto factor = LargePrimeNumbers::find_factor_quadratic_sieve(
      LargePrimeNumbers::bigint("59469489332848408438249254427481121839977"),
      params);

  if (factor.has_value()) {
    cout << "found factor: " << factor.value() << endl;
  } else {
    cout << "found no factor" << endl;
  }
}
