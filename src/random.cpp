#include "random.h"

#include <boost/multiprecision/gmp.hpp>
#include <boost/multiprecision/random.hpp>
#include <random>

#include "common.h"

namespace LargePrimeNumbers {

RandomBigint::RandomBigint(uint32_t seed) : mt_(seed) {}

bigint RandomBigint::generate_uniform(const bigint& min, const bigint& max) {
  assert(min <= max);
  boost::uniform_int<bigint> gen(min, max);
  return gen(mt_);
}

}  // namespace LargePrimeNumbers
