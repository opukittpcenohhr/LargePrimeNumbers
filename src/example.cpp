#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>

#include "legendre_symbol.h"
#include "logging.h"
#include "quadratic_sieve.h"

int main() {
  using namespace boost::multiprecision;
  using namespace Project;
  using namespace std;

  constexpr auto params = QuadraticSieveParams{2000, 50000000, 2.0};

  // >>> 175656509371887105761 * 338555568168236555657
  // 59469489332848408438249254427481121839977

  auto factor = find_factor_quadratic_sieve<params>(
      bigint("59469489332848408438249254427481121839977"));

  if (factor.has_value()) {
    cout << "found factor: " << factor.value() << endl;
  } else {
    cout << "found no factor" << endl;
  }
}