#pragma once

#include <functional>
#include <optional>

#include "benchmark_data.h"
#include "check_potential_factor.h"
#include "common.h"
#include "execution_time.h"

namespace LargePrimeNumbers {

template <typename Params>
void run_factorization_function(
    std::function<std::optional<bigint>(const bigint&, const Params&)>
        factorization_function,
    const bigint& number, const Params& params) {
  auto factor = factorization_function(number, params);
  assert(check_potential_factor(number, factor));
  BOOST_LOG_TRIVIAL(info) << "number: " << number
                          << " factor: " << factor.value();
}

template <typename Params>
void run_factorization_benchmark(
    std::function<std::optional<bigint>(const bigint&, const Params&)>
        factorization_function,
    const std::map<int, Params>& params_by_length) {
  auto test_data = get_composite_numbers_by_length();
  for (const auto& [length, data] : test_data) {
    const auto& params = params_by_length.at(length);
    std::chrono::milliseconds total_time(0);
    for (const auto& number_str : data) {
      auto current_time = execution_time(
          run_factorization_function<Params>, factorization_function,
          bigint(number_str), params);
      total_time += current_time;
    }
    std::cout << "Average execution time for numbers of length " << length
              << " is " << total_time.count() / data.size() << " ms"
              << std::endl;
  }
}

}  // namespace LargePrimeNumbers
