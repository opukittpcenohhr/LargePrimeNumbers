#pragma once

#include "common.h"
#include "logging.h"
#include "primes_data.h"

namespace Project {

template <typename T>
concept PrimalityTest = requires(T func, const bigint& arg) {
  { func(arg) } -> std::same_as<bool>;
};

template <PrimalityTest PrimalityTestFunc>
void test_primality_test(PrimalityTestFunc primality_test,
                         std::string primality_test_name,
                         const std::set<bigint>& false_positives) {
  for (auto [number, is_prime] : PRIMES_DATA) {
    bool expected_result = is_prime;
    if (false_positives.contains(bigint(number))) {
      expected_result = true;
    }
    DEBUG() << "Testing " << primality_test_name << ", number: " << number;
    EXPECT_EQ(primality_test(bigint(number)), expected_result);
  }
}

}  // namespace Project