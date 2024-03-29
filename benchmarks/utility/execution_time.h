#pragma once
#include <chrono>

namespace LargePrimeNumbers {

template <typename F, typename... Args>
std::chrono::milliseconds execution_time(F func, Args&&... args) {
  auto t_begin = std::chrono::high_resolution_clock::now();
  func(std::forward<Args>(args)...);
  auto t_end = std::chrono::high_resolution_clock::now();
  return std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_begin);
}

}  // namespace LargePrimeNumbers
