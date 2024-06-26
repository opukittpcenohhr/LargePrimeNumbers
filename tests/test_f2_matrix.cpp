#include <gtest/gtest.h>

#include "f2_matrix.h"

namespace LargePrimeNumbers {

TEST(ReduceToRowEchelonForm, test) {
  auto matrix = F2Matrix(3, 3);
  matrix[0][0] = 0;
  matrix[0][1] = 0;
  matrix[0][2] = 1;

  matrix[1][0] = 1;
  matrix[1][1] = 0;
  matrix[1][2] = 1;

  matrix[2][0] = 1;
  matrix[2][1] = 1;
  matrix[2][2] = 0;

  reduce_to_row_echelon_form(2, matrix);
  EXPECT_EQ(matrix[0][0], 1);
  EXPECT_EQ(matrix[0][1], 0);
  EXPECT_EQ(matrix[0][0], 1);

  EXPECT_EQ(matrix[1][0], 0);
  EXPECT_EQ(matrix[1][1], 1);
  EXPECT_EQ(matrix[1][2], 1);

  EXPECT_EQ(matrix[2][0], 0);
  EXPECT_EQ(matrix[2][1], 0);
  EXPECT_EQ(matrix[2][2], 1);
}

}  // namespace LargePrimeNumbers
