#pragma once

#include "common.h"

namespace LargePrimeNumbers {

template <typename T>
concept PrimalityTest = requires(T func, const bigint& arg) {
  { func(arg) } -> std::same_as<bool>;
};

template <typename T>
concept FindFactor = requires(T func, const bigint& arg) {
  { func(arg) } -> std::same_as<std::optional<bigint>>;
};

}  // namespace LargePrimeNumbers
