#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/trivial.hpp>
#include <map>

#include "find_factor_cfrac.h"
#include "utility/becnhmark_factorization_with_params.h"

using namespace LargePrimeNumbers;

namespace {

const std::map<int, CfracParams> cfrac_params_by_length = {
    {32, {300}},  //
    {36, {400}},
    {40, {500}},
    {42, {600}},
};

}  // namespace

int main() {
  namespace logging = boost::log;
  logging::core::get()->set_filter(
      logging::trivial::severity >= logging::trivial::info);

  run_factorization_benchmark<CfracParams>(
      find_factor_cfrac, cfrac_params_by_length);
  return 0;
}
