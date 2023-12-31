#pragma once

#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/trivial.hpp>
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

inline void set_log_level_for_tests() {
  namespace logging = boost::log;
  logging::core::get()->set_filter(logging::trivial::severity >=
                                   logging::trivial::info);
}

template <PrimalityTest PrimalityTestFunc>
void test_primality_test(
    PrimalityTestFunc primality_test, std::string primality_test_name,
    const std::set<bigint>& false_positives,
    std::optional<size_t> max_number_len_to_test = std::nullopt) {
  set_log_level_for_tests();
  for (auto [number, is_prime] : PRIMES_DATA) {
    if (max_number_len_to_test.has_value() &&
        number.size() > max_number_len_to_test.value()) {
      continue;
    }
    bool expected_result = is_prime;
    if (false_positives.contains(bigint(number))) {
      expected_result = true;
    }
    INFO() << "Testing " << primality_test_name << ", number: " << number;
    EXPECT_EQ(primality_test(bigint(number)), expected_result);
  }
}

template <FindFactor FindFactorFunc>
void test_find_factor(
    FindFactorFunc find_factor, std::string find_factor_test_name,
    const std::set<bigint>& exclusions,
    std::optional<size_t> min_number_len_to_test = std::nullopt,
    std::optional<size_t> max_number_len_to_test = std::nullopt) {
  set_log_level_for_tests();
  for (auto [number_str, is_prime] : PRIMES_DATA) {
    if (max_number_len_to_test.has_value() &&
        number_str.size() > max_number_len_to_test.value()) {
      continue;
    }
    if (min_number_len_to_test.has_value() &&
        number_str.size() < min_number_len_to_test.value()) {
      continue;
    }
    auto number = bigint(number_str);
    if (!is_prime && !exclusions.contains(number)) {
      INFO() << "Testing " << find_factor_test_name << ", number: " << number;
      auto some_factor = find_factor(number);
      EXPECT_EQ(some_factor.has_value(), true);
      EXPECT_NE(some_factor.value(), 1);
      EXPECT_NE(some_factor.value(), number);
      EXPECT_EQ(number % some_factor.value(), 0);
      INFO() << "Found factor: " << some_factor.value();
    }
  }
}

}  // namespace Project