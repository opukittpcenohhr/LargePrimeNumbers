#include "find_congruence.h"

#include <map>
#include <optional>
#include <random>

#include "common.h"
#include "legendre_symbol.h"
#include "random.h"
#include "utility.h"

namespace LargePrimeNumbers {

namespace {

// Computes v_ind, where v is sequence defined by following rules:
// v_1 = v_1
// v_2 = v_2
// v_i = h * v_{i - 1} + n * v_{i - 2} mod p
bigint find_v(bigint ind, bigint p, bigint h, bigint n, bigint v1, bigint v2) {
  std::map<bigint, bigint> v;
  v[1] = v1;
  v[2] = v2;

  std::function<bigint(bigint)> get_v = [&](bigint i) {
    if (!v.contains(i)) {
      if (i % 2 == 0) {
        v[i] = mulmod<bigint>(get_v(i / 2), get_v(i / 2), p);
        auto tmp = mulmod<bigint>(2, powmod<bigint>(n, i / 2, p), p);
        v[i] = submod<bigint>(v[i], tmp, p);
      } else {
        v[i] = mulmod<bigint>(get_v(i / 2), get_v(i / 2 + 1), p);
        auto tmp = mulmod<bigint>(h, powmod<bigint>(n, i / 2, p), p);
        v[i] = submod<bigint>(v[i], tmp, p);
      }
    }
    return v[i];
  };

  return get_v(ind);
}
}  // namespace

bigint find_congruence(const bigint& n, const bigint& p) {
  auto rng = RandomBigint(239);

  bigint h = -1;
  while (h == -1) {
    auto candidate = rng.generate_uniform(0, p - 1);
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
      submod(mulmod(h, h, p), mulmod<bigint>(2, n_residue_modulo_p, p), p));

  auto x = mulmod<bigint>(v, (p + 1) / 2, p);
  return x;
}

std::vector<bigint> find_all_congruences(const bigint& n, const bigint& p) {
  if (p == 2) {
    return {(n % p).convert_to<int>()};
  } else {
    auto some_congruence = find_congruence(n, p);
    return {some_congruence, p - some_congruence};
  }
}

}  // namespace LargePrimeNumbers
