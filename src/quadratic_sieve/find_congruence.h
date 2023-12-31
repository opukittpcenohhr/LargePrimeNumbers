#pragma once
#include <boost/multiprecision/cpp_int.hpp>
#include <map>
#include <optional>
#include <random>

#include "common.h"
#include "legendre_symbol.h"
#include "logging.h"
#include "utility.h"

namespace Project {

// both v1 and v2 are stored in ints, since all operations are modulo p
inline int find_v(int ind, int p, int h, int n, int v1, int v2) {
  typedef long long ll;

  std::map<int, int> v;
  v[1] = v1;
  v[2] = v2;

  std::function<int(int)> get_v = [&](int i) {
    if (!v.contains(i)) {
      if (i % 2 == 0) {
        v[i] = mulmod<ll>(get_v(i / 2), get_v(i / 2), p);
        auto tmp = mulmod<ll>(2, powmod<ll>(n, i / 2, p), p);
        v[i] = submod<ll>(v[i], tmp, p);
      } else {
        v[i] = mulmod<ll>(get_v(i / 2), get_v(i / 2 + 1), p);
        auto tmp = mulmod<ll>(h, powmod<ll>(n, i / 2, p), p);
        v[i] = submod<ll>(v[i], tmp, p);
      }
    }
    return v[i];
  };

  return get_v(ind);
}

inline int find_congruence(bigint n, int p) {
  // find x, such as x^2 = n (mod p)
  typedef long long ll;
  std::mt19937 rng(239);

  int h = -1;
  while (h == -1) {
    long long candidate = ((rng() % p) + p) % p;
    bigint legendre_symbol_enumerator = bigint(candidate * candidate) - 4 * n;
    legendre_symbol_enumerator = ((legendre_symbol_enumerator % p) + p) % p;
    if (find_legendre_symbol(legendre_symbol_enumerator, p) == -1) {
      h = candidate;
    }
  }
  assert(h != -1);

  int n_residue_modulo_p = (n % p).convert_to<int>();

  auto v = find_v(
      (p + 1) / 2, p, h, n_residue_modulo_p, h,
      submod<ll>(mulmod<ll>(h, h, p), mulmod<ll>(2, n_residue_modulo_p, p), p));

  auto x = mulmod<ll>(v, (p + 1) / 2, p);
  assert(mulmod<ll>(x, x, p) == n_residue_modulo_p);
  return x;
}

inline std::vector<int> find_all_congruences(bigint n, int p) {
  if (p == 2) {
    return {(n % p).convert_to<int>()};
  } else {
    auto some_congruence = find_congruence(n, p);
    return {some_congruence, p - some_congruence};
  }
}

}  // namespace Project