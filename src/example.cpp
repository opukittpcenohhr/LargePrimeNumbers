#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>

#include "fermat_pseudoprimarity_test.h"

int main() {
  using namespace boost::multiprecision;
  using namespace Project;
  using namespace std;

  cpp_int res = 561;
  cout << res << endl;
  cout << is_fermat_pseudoprime(res) << endl;

  return 0;
}