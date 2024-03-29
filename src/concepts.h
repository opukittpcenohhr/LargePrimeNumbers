#pragma once

#include <span>

#include "common.h"

namespace LargePrimeNumbers {

template <typename T>
concept PrimalityTest = requires(T&& func, const bigint& arg) {
  { func(arg) } -> std::same_as<bool>;
};

template <typename T>
concept FindFactor = requires(T&& func, const bigint& arg) {
  { func(arg) } -> std::same_as<std::optional<bigint>>;
};

template <typename T>
concept PrimalityTestWithBasesCount = requires(
    T&& func, std::span<const int> bases,
    const LargePrimeNumbers::bigint& arg) {
  { func(arg, bases) } -> std::same_as<bool>;
};

template <typename T>
concept SomeOptional = requires {
  typename std::decay_t<T>;
  requires std::is_same_v<
      std::decay_t<T>, std::optional<typename std::decay_t<T>::value_type>>;
};

}  // namespace LargePrimeNumbers
