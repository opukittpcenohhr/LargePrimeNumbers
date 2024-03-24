#include "f2_matrix.h"

namespace LargePrimeNumbers {

void perform_gaussian_elimination(F2Matrix& matrix, size_t columns_to_perform) {
  for (size_t i = 0; i < columns_to_perform; ++i) {
    size_t pivot = i;
    while (pivot < matrix.row_count() && !matrix[pivot][i]) {
      ++pivot;
    }
    if (pivot == matrix.row_count()) {
      continue;
    }
    if (pivot != i) {
      std::swap(matrix[i], matrix[pivot]);
    }
    assert(matrix[i][i] == 1);
    for (size_t row_under = i + 1; row_under < matrix.row_count();
         ++row_under) {
      if (matrix[row_under][i]) {
        matrix[row_under] ^= matrix[i];
      }
    }
  }
}

}  // namespace LargePrimeNumbers
