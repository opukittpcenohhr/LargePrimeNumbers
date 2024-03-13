#pragma once

#include <cassert>
#include <optional>

namespace LargePrimeNumbers {

template <typename T>
T addmod(const T& a, const T& b, const T& mod) {
  return (a + b) % mod;
}

template <typename T>
T submod(const T& a, const T& b, const T& mod) {
  return ((a - b) % mod + mod) % mod;
}

template <typename T>
T mulmod(const T& a, const T& b, const T& mod) {
  return (a * b) % mod;
}

template <typename T>
T powmod(T a, T b, const T& mod) {
  assert(b >= 0);
  T res = 1;
  while (b > 0) {
    if (b % 2 == 1) {
      res = mulmod<T>(res, a, mod);
    }
    a = mulmod<T>(a, a, mod);
    b = b / 2;
  }
  return res;
}

template <typename T>
T gcd(const T& a, const T& b) {
  if (b == 0) {
    return a;
  } else {
    return gcd(b, a % b);
  }
}

template <typename T>
T abs(const T& a) {
  return a * (a > 0) - a * (a < 0);
}

template <typename T>
std::optional<T> check_potential_factor(const T& n, const T& factor) {
  assert(n >= 1);
  assert(factor >= 1);
  T g = gcd(n, factor);
  if (g != 1 && g != n) {
    return g;
  } else {
    return std::nullopt;
  }
}

}  // namespace LargePrimeNumbers
