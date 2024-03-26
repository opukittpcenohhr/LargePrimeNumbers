#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/trivial.hpp>
#include <cmath>
#include <map>
#include <random>
#include <vector>

#include "concepts.h"
#include "find_factor_quadratic_sieve.h"

using namespace LargePrimeNumbers;

namespace {

const std::map<int, std::vector<std::string>> test_data_by_length = {
    {
        40,
        {
            "1341607143054843295547875435911311905603",
            "1059285451583551757136470012326168588211",
            "2091670908976974559557349218113349872537",
            "5483796096268107917873364568462891391489",
        },
    },
    {42,
     {
         "699004724346603726808873010695909898715301",
         "323625121576583872016625431084244826643719",
         "169990781102809563810476653384677149067593",
         "692208583265230868345078053241847923557531",
     }},
    {44,
     {
         "78557707277711944408813356963986078545605353",
         "49574663404422284323912558249674569048374199",
         "14072239672140078566948347701006855196527359",
         "89318364773291449689396095503502029711463867",
     }},
    {46,
     {
         "3949636775596748375228311760105549562554372279",
         "3013757924334904635755632689370794028758312287",
         "2166544711417488176144109263469319459138950817",
         "1227970244726132302414144733718246630334933457",
     }},
    {48,
     {
         "214108560153417661906862628449317907379325899017",
         "119012167475755260742853754537856452568006013057",
         "231585709976443166303654553891689652002612548451",
         "207664371462601836760816945444169966007517618661",
     }},
    {50,
     {
         "16001540072473582624298580657033478499527103960501",
         "45259614007442517325437121480339719298296284476841",
         "42050080283993441771863866335296608251393384745331",
         "39605391140139351309590713465425102375506112814753",
     }}};

const std::map<int, QuadraticSieveParams> quadratic_sieve_params_by_length = {
    {40, {2000, 200000000, 2.0}}, {42, {2500, 300000000, 2.0}},
    {44, {4000, 500000000, 2.0}}, {46, {4500, 500000000, 2.0}},
    {48, {8000, 500000000, 2.0}}, {50, {10000, 1000000000, 2.0}}};

void run_quadratic_sieve(
    const bigint& number, const QuadraticSieveParams& params) {
  auto factor = LargePrimeNumbers::find_factor_quadratic_sieve(number, params);
  assert(factor.has_value());
  assert(factor.value() > 1 && factor.value() < number);
  assert(number % factor.value() == 0);
  BOOST_LOG_TRIVIAL(info) << "number: " << number
                          << " factor: " << factor.value();
}

template <typename F, typename... Args>
std::chrono::milliseconds execution_time(F func, Args&&... args) {
  auto t_begin = std::chrono::high_resolution_clock::now();
  func(std::forward<Args>(args)...);
  auto t_end = std::chrono::high_resolution_clock::now();
  return std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_begin);
}

void run_benchmarks() {
  for (const auto& [length, data] : test_data_by_length) {
    const auto& params = quadratic_sieve_params_by_length.at(length);
    std::chrono::milliseconds total_time(0);
    for (const auto& number_str : data) {
      auto current_time =
          execution_time(run_quadratic_sieve, bigint(number_str), params);
      total_time += current_time;
    }
    std::cout << "Average execution time for numbers of length " << length
              << " is " << total_time.count() / data.size() << " ms"
              << std::endl;
  }
}
}  // namespace

int main() {
  namespace logging = boost::log;
  logging::core::get()->set_filter(
      logging::trivial::severity >= logging::trivial::info);

  run_benchmarks();
  return 0;
}
