#pragma once

#include "common.h"
#include "utility.h"

namespace LargePrimeNumbers {

struct BhascaraBrounker {
  struct Item {
    bigint a;
    bigint b;
    bigint c;
    bigint p;

    bool operator==(const Item& other) const = default;
  };

  class Iterable {
  public:
    Iterable(
        const Item& current, const Item& next, const bigint& n,
        const bigint& sqrt_n)
        : current_(current), next_(next), n_(n), sqrt_n_(sqrt_n) {}

    const Item& operator*() const;
    const Item* operator->() const;
    Iterable& operator++();

  private:
    Item current_;
    Item next_;
    bigint n_;
    bigint sqrt_n_;
  };

  static Iterable get_first_item(const bigint& n);

  static Iterable get_first_item(const bigint& n, const bigint& sqrt_n);
};

}  // namespace LargePrimeNumbers
