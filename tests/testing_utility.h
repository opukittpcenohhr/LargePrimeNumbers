#pragma once

#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/trivial.hpp>
#include <optional>

#include "common.h"
#include "concepts.h"
#include "data.h"

namespace LargePrimeNumbers {

inline void set_log_level_for_tests() {
  namespace logging = boost::log;
  logging::core::get()->set_filter(
      logging::trivial::severity >= logging::trivial::info);
}

template <PrimalityTest PrimalityTestFunc>
void test_primality_test(
    PrimalityTestFunc primality_test, const std::string& primality_test_name,
    const std::set<bigint>& false_positives,
    std::optional<bigint> max_number_to_test = std::nullopt) {
  set_log_level_for_tests();
  auto data = get_prime_numbers_data();
  for (const auto& [number, is_prime] : data) {
    if (max_number_to_test.has_value() && number > max_number_to_test) {
      continue;
    }
    bool expected_result = is_prime;
    if (false_positives.contains(number)) {
      expected_result = true;
    }
    BOOST_LOG_TRIVIAL(info)
        << "Testing " << primality_test_name << ", number: " << number;
    EXPECT_EQ(primality_test(number), expected_result);
  }
}

template <FindFactor FindFactorFunc>
void test_find_factor(
    FindFactorFunc find_factor, const std::string& find_factor_test_name,
    const std::set<bigint>& exclusions,
    std::optional<bigint> min_number_to_test = std::nullopt,
    std::optional<bigint> max_number_to_test = std::nullopt) {
  set_log_level_for_tests();
  auto data = get_prime_numbers_data();
  for (const auto& test_case : data) {
    bigint number = test_case.first;
    bool is_prime = test_case.second;
    if (max_number_to_test.has_value() && number > max_number_to_test) {
      continue;
    }
    if (min_number_to_test.has_value() && number < min_number_to_test) {
      continue;
    }
    if (!is_prime && !exclusions.contains(number)) {
      BOOST_LOG_TRIVIAL(info)
          << "Testing " << find_factor_test_name << ", number: " << number;
      auto some_factor = find_factor(number);
      EXPECT_EQ(some_factor.has_value(), true);
      EXPECT_NE(some_factor.value(), 1);
      EXPECT_NE(some_factor.value(), number);
      EXPECT_EQ(number % some_factor.value(), 0);
      BOOST_LOG_TRIVIAL(info) << "Found factor: " << some_factor.value();
    }
  }
}

}  // namespace LargePrimeNumbers
