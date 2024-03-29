#pragma once

#include <boost/dynamic_bitset.hpp>
#include <iostream>

namespace LargePrimeNumbers {

class F2Matrix {
public:
  F2Matrix() = default;

  F2Matrix(size_t row_count, size_t column_count);

  boost::dynamic_bitset<>& operator[](size_t index);

  const boost::dynamic_bitset<>& operator[](size_t index) const;

  friend std::ostream& operator<<(std::ostream& os, const F2Matrix& matrix);

  size_t row_count() const;

  size_t column_count() const;

private:
  std::vector<boost::dynamic_bitset<>> a_;
};

void reduce_to_row_echelon_form(size_t columns_to_perform, F2Matrix& matrix);

}  // namespace LargePrimeNumbers
