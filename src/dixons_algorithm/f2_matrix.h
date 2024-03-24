#pragma once

#include <boost/dynamic_bitset.hpp>
#include <iostream>

namespace LargePrimeNumbers {

class F2Matrix {
public:
  F2Matrix() = default;

  F2Matrix(size_t row_count, size_t column_count)
      : a_(row_count, boost::dynamic_bitset<>(column_count)) {
    assert(row_count > 0);
    assert(column_count > 0);
  }

  boost::dynamic_bitset<>& operator[](size_t index) {
    return a_[index];
  }

  const boost::dynamic_bitset<>& operator[](size_t index) const {
    return a_[index];
  }

  friend std::ostream& operator<<(std::ostream& os, const F2Matrix& matrix) {
    for (size_t i = 0; i < matrix.row_count(); ++i) {
      for (size_t j = 0; j < matrix.column_count(); ++j) {
        os << (matrix[i])[j];
      }
      os << std::endl;
    }
    return os;
  }

  size_t row_count() const {
    return a_.size();
  }

  size_t column_count() const {
    return a_[0].size();
  }

private:
  std::vector<boost::dynamic_bitset<>> a_;
};

void perform_gaussian_elimination(F2Matrix& matrix, size_t columns_to_perform);

}  // namespace LargePrimeNumbers
