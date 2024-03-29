#include "bhascara_brounker_sequence.h"

#include "common.h"
#include "utility.h"

namespace LargePrimeNumbers {

const BhascaraBrounker::Item& BhascaraBrounker::Iterable::operator*() const {
  return current_;
}

const BhascaraBrounker::Item* BhascaraBrounker::Iterable::operator->() const {
  return &current_;
}

BhascaraBrounker::Iterable& BhascaraBrounker::Iterable::operator++() {
  bigint a_new_next = (sqrt_n_ + next_.b) / next_.c;
  bigint b_new_next = a_new_next * next_.c - next_.b;
  bigint c_new_next = current_.c + a_new_next * (next_.b - b_new_next);
  auto p_new_next =
      addmod<bigint>(mulmod<bigint>(a_new_next, next_.p, n_), current_.p, n_);
  current_ = next_;
  next_ = {
      .a = a_new_next,
      .b = b_new_next,
      .c = c_new_next,
      .p = p_new_next,
  };
  return *this;
}

BhascaraBrounker::Iterable BhascaraBrounker::get_first_item(const bigint& n) {
  return BhascaraBrounker::get_first_item(n, boost::multiprecision::sqrt(n));
}

BhascaraBrounker::Iterable BhascaraBrounker::get_first_item(
    const bigint& n, const bigint& sqrt_n) {
  return BhascaraBrounker::Iterable(
      {
          // 0-th item
          .a = 0,
          .b = 0,
          .c = 1,
          .p = 1,
      },
      {
          // 1-st item
          .a = sqrt_n,
          .b = sqrt_n,
          .c = n - sqrt_n * sqrt_n,
          .p = sqrt_n,
      },
      n, sqrt_n);
}

}  // namespace LargePrimeNumbers
