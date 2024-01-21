#include <boost/multiprecision/gmp.hpp>
#include <boost/multiprecision/random.hpp>
#include <random>

#include "common.h"

namespace LargePrimeNumbers {

class RandomBigintGenerator {
 public:
  RandomBigintGenerator(int seed) : mt_(seed) {}

  // generate random number in [min, max]
  bigint generate_uniform_random(const bigint& min, const bigint& max) {
    assert(min <= max);
    boost::uniform_int<bigint> gen(min, max);
    return gen(mt_);
  }

 private:
  boost::mt19937 mt_;
};

}  // namespace LargePrimeNumbers
