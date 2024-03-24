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

template <typename T>
concept PrimalityTestWithBasesCount = requires(
    T func, std::span<const int> bases, const LargePrimeNumbers::bigint& arg) {
  { func(arg, bases) } -> std::same_as<bool>;
};

template <PrimalityTestWithBasesCount PrimalityTestFunc>
void plot_detected_pseudoprimes_vs_bases_count_for_pseudoprimality_test(
    PrimalityTestFunc primality_test, const std::string& test_name,
    const std::vector<int>& bases, const std::vector<int>& log_ranges_begin,
    const int range_len) {
  using namespace LargePrimeNumbers;

  for (auto log_range_begin : log_ranges_begin) {
    bigint range_begin =
        boost::multiprecision::pow(bigint(10), log_range_begin);
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
          << " pseudoprimality test, log_range_begin: " << log_range_begin
          << " bases_count: " << bases_count
          << " detected primes: " << detected_primes;
    }

    const std::string range_description =
        "[10^{" + std::to_string(log_range_begin) + "}," + "10^{" +
        std::to_string(log_range_begin) + "}+" + std::to_string(range_len) +
        "]";
    auto f = matplot::figure();
    f->size(1200, 800);
    matplot::plot(counts, found_primes);
    matplot::xlabel("Number of bases");
    matplot::ylabel("Number of pseudoprimes detected");
    std::string filename = "benchmark_charts/" + test_name +
                           "_pseudoprimality_" + range_description + ".png";
    matplot::title(
        "Number of pseudoprimes detected by " + test_name +
        " pseudoprimality test for "
        "different number of bases  "
        "for numbers in "
        "range " +
        range_description);
    matplot::save(filename);
  }
}

int main() {
  using namespace LargePrimeNumbers;

  namespace logging = boost::log;
  logging::core::get()->set_filter(
      logging::trivial::severity >= logging::trivial::info);

  // TODO(dumnov): make this cli arguments
  std::vector<int> bases = {2, 3, 5, 7, 9};
  std::vector<int> log_ranges_begin = {6, 10, 20};
  int range_len = 2000000;

  plot_detected_pseudoprimes_vs_bases_count_for_pseudoprimality_test(
      LargePrimeNumbers::is_strong_pseudoprime, "Miller-Rabin", bases,
      log_ranges_begin, range_len);

  plot_detected_pseudoprimes_vs_bases_count_for_pseudoprimality_test(
      LargePrimeNumbers::is_fermat_pseudoprime, "Fermat", bases,
      log_ranges_begin, range_len);
}
