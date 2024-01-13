#pragma once

#include <array>
#include <cstddef>
#include <iostream>

#include "logging.h"

namespace LargePrimeNumbers {

template <size_t N, size_t M>
class F2Matrix {
 public:
  F2Matrix() : a(N) {}

  std::bitset<M>& operator[](size_t i) {
    return a[i];
  }

  const std::bitset<M>& operator[](size_t i) const {
    return a[i];
  }

  bool& operator()(size_t i, size_t j) {
    return a[i][j];
  }

  const bool& operator()(size_t i, size_t j) const {
    return a[i][j];
  }

  friend std::ostream& operator<<(std::ostream& os, const F2Matrix& matrix) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        os << matrix[i][j];
      }
      os << std::endl;
    }
    return os;
  }

 private:
  std::vector<std::bitset<M>> a;
};

template <size_t N, size_t M>
void perform_gaussian_elimination(F2Matrix<N, M>& matrix,
                                  size_t columns_to_perform) {
  for (size_t i = 0; i < columns_to_perform; ++i) {
    size_t pivot = i;
    while (pivot < N && !matrix[pivot][i]) {
      ++pivot;
    }
    if (pivot < N) {
      if (pivot != i) {
        std::swap(matrix[i], matrix[pivot]);
      }
      assert(matrix[i][i] == 1);
      for (size_t row_under = i + 1; row_under < N; ++row_under) {
        if (matrix[row_under][i]) {
          matrix[row_under] ^= matrix[i];
        }
      }
    }
  }
}

}  // namespace LargePrimeNumbers