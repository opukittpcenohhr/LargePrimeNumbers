#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/trivial.hpp>
#include <map>

#include "find_factor_quadratic_sieve.h"
#include "utility/becnhmark_factorization_with_params.h"

using namespace LargePrimeNumbers;

namespace {

const std::map<int, QuadraticSieveParams> quadratic_sieve_params_by_length = {
    {40, {2000, 200000000, 2.0}}, {42, {2500, 300000000, 2.0}},
    {44, {4000, 500000000, 2.0}}, {46, {4500, 500000000, 2.0}},
    {48, {8000, 500000000, 2.0}}, {50, {10000, 1000000000, 2.0}}};

}  // namespace

int main() {
  namespace logging = boost::log;
  logging::core::get()->set_filter(
      logging::trivial::severity >= logging::trivial::info);

  run_factorization_benchmark<QuadraticSieveParams>(
      find_factor_quadratic_sieve, quadratic_sieve_params_by_length);
  return 0;
}
