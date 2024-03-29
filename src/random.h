#include <boost/multiprecision/gmp.hpp>
#include <boost/multiprecision/random.hpp>
#include <random>

#include "common.h"

namespace LargePrimeNumbers {

class RandomBigint {
public:
  explicit RandomBigint(uint32_t seed);

  // generate random number in [min, max]
  bigint generate_uniform(const bigint& min, const bigint& max);

private:
  boost::mt19937 mt_;
};

}  // namespace LargePrimeNumbers
