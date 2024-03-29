#include <matplot/matplot.h>

#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/trivial.hpp>
#include <cmath>
#include <random>
#include <vector>

#include "concepts.h"
#include "fermat_pseudoprimality_test.h"
#include "strong_pseudoprimality_test.h"

namespace {

template <LargePrimeNumbers::PrimalityTestWithBasesCount PrimalityTestFunc>
void plot_detected_pseudoprimes_vs_bases_count_for_pseudoprimality_test(
    PrimalityTestFunc primality_test, const std::string& test_name,
    const std::vector<int>& bases, const std::vector<int>& ranges_begin_log,
    const int range_len) {
  using namespace LargePrimeNumbers;

  for (auto single_range_begin_log : ranges_begin_log) {
    bigint range_begin =
        boost::multiprecision::pow(bigint(10), single_range_begin_log);
    bigint range_end = range_begin + range_len;
    std::vector<size_t> counts;
    std::vector<size_t> found_primes;
    for (size_t bases_count = 1; bases_count <= bases.size(); bases_count++) {
      size_t detected_primes = 0;
      for (bigint n = range_begin; n <= range_end; n++) {
        if (primality_test(
                n, std::span<const int>(bases.data(), bases_count))) {
          detected_primes++;
        }
      }
      counts.push_back(bases_count);
      found_primes.push_back(detected_primes);
      BOOST_LOG_TRIVIAL(info)
          << "Benchmark " << test_name
          << " pseudoprimality test, single_range_begin_log: "
          << single_range_begin_log << " bases_count: " << bases_count
          << " detected primes: " << detected_primes;
    }

    const std::string range_description =
        "[10^{" + std::to_string(single_range_begin_log) + "}," + "10^{" +
        std::to_string(single_range_begin_log) + "}+" +
        std::to_string(range_len) + "]";
    auto f = matplot::figure();
    f->size(1200, 800);
    matplot::plot(counts, found_primes);
    matplot::xlabel("Number of bases");
    matplot::ylabel("Number of potential primes detected");
    std::string filename = "benchmark_charts/" + test_name + "_primality_" +
                           range_description + ".png";
    matplot::title(
        "Number of potential primes detected by " + test_name +
        " primality test for "
        "different number of bases  "
        "for numbers in "
        "range " +
        range_description);
    matplot::save(filename);
  }
}

}  // namespace

int main() {
  using namespace LargePrimeNumbers;

  namespace logging = boost::log;
  logging::core::get()->set_filter(
      logging::trivial::severity >= logging::trivial::info);

  // TODO(dumnov): make this cli arguments
  std::vector<int> bases = {2, 3, 5, 7, 9};
  std::vector<int> ranges_begin_log = {6, 10, 20};
  int range_len = 2000000;

  plot_detected_pseudoprimes_vs_bases_count_for_pseudoprimality_test(
      LargePrimeNumbers::is_strong_pseudoprime, "Miller-Rabin", bases,
      ranges_begin_log, range_len);

  plot_detected_pseudoprimes_vs_bases_count_for_pseudoprimality_test(
      LargePrimeNumbers::is_prime_fermat_test, "Fermat", bases,
      ranges_begin_log, range_len);
}
