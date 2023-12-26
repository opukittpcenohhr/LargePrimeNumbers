#pragma once

namespace Project {

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
  T res = 1;
  while (b > 0) {
    if (b % 2 == 1) {
      res = mulmod(res, a, mod);
    }
    a = mulmod(a, a, mod);
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

}  // namespace Project