#include "f2_matrix.h"

namespace LargePrimeNumbers {

F2Matrix::F2Matrix(size_t row_count, size_t column_count)
    : a_(row_count, boost::dynamic_bitset<>(column_count)) {
  assert(row_count > 0);
  assert(column_count > 0);
}

boost::dynamic_bitset<>& F2Matrix::operator[](size_t index) {
  return a_[index];
}

const boost::dynamic_bitset<>& F2Matrix::operator[](size_t index) const {
  return a_[index];
}

std::ostream& operator<<(std::ostream& os, const F2Matrix& matrix) {
  for (size_t i = 0; i < matrix.row_count(); ++i) {
    for (size_t j = 0; j < matrix.column_count(); ++j) {
      os << (matrix[i])[j];
    }
    os << std::endl;
  }
  return os;
}

size_t F2Matrix::row_count() const {
  return a_.size();
}

size_t F2Matrix::column_count() const {
  return a_[0].size();
}

void reduce_to_row_echelon_form(size_t columns_to_perform, F2Matrix& matrix) {
  for (size_t col = 0, row = 0;
       col < columns_to_perform && row < matrix.row_count(); ++col) {
    size_t pivot = row;
    while (pivot < matrix.row_count() && !matrix[pivot][col]) {
      ++pivot;
    }
    if (pivot == matrix.row_count()) {
      continue;
    }
    if (pivot != row) {
      std::swap(matrix[row], matrix[pivot]);
    }
    assert(matrix[row][col] == 1);
    for (size_t row_under = row + 1; row_under < matrix.row_count();
         ++row_under) {
      if (matrix[row_under][col]) {
        matrix[row_under] ^= matrix[row];
      }
    }
    ++row;
  }
}

}  // namespace LargePrimeNumbers
