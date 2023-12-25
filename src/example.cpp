#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>

#include "naive_primary_test.h"

int main() {
  using namespace boost::multiprecision;
  using namespace Project;
  using namespace std;

  cpp_int res = 1;
  for (cpp_int i = 1; i < 1000; i++) {
    if (is_prime_naive(i)) {
      cout << "prime: " << i << endl;
    }
  }

  return 0;
}