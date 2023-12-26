#pragma once

#include <optional>

#include "common.h"
#include "logging.h"
#include "primes_data.h"

namespace Project {

template <typename T>
concept PrimalityTest = requires(T func, const bigint& arg) {
  { func(arg) } -> std::same_as<bool>;
};

template <typename T>
concept FindFactor = requires(T func, const bigint& arg) {
  { func(arg) } -> std::same_as<std::optional<bigint>>;
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

template <FindFactor FindFactorFunc>
void test_find_factor(FindFactorFunc find_factor,
                      std::string find_factor_test_name) {
  for (auto [number_str, is_prime] : PRIMES_DATA) {
    if (!is_prime) {
      DEBUG() << "Testing " << find_factor_test_name
              << ", number: " << number_str;
      auto number = bigint(number_str);
      auto some_factor = find_factor(number);
      EXPECT_EQ(some_factor.has_value(), true);
      EXPECT_NE(some_factor.value(), 0);
      EXPECT_NE(some_factor.value(), number);
      EXPECT_EQ(number % some_factor.value(), 0);
    }
  }
}

}  // namespace Project