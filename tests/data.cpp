#include "data.h"

#include <map>
#include <string>

namespace {
const std::map<std::string, bool> kPrimeNumbersData = {
    {"2", true},
    {"3", true},
    {"5", true},
    {"6", false},
    {"7", true},
    {"8", false},
    {"9", false},
    {"10", false},
    {"11", true},
    {"12", false},
    {"13", true},
    {"14", false},
    {"15", false},
    {"16", false},
    {"17", true},
    {"18", false},
    {"19", true},
    {"20", false},
    {"433", true},
    {"561", false},
    {"829", true},
    {"29341", false},
    {"63973", false},
    {"512461", false},
    {"9274252991", true},
    {"464052305161", false},
    {"4257452468389", true},
    {"2428095424619", true},
    {"53982894593057", true},
    {"1436697831295441", false},
    {"60977817398996785", false},
    {"7156857700403137441", false},
    {"1791562810662585767521", false},
    {"9999999989000000003021", false},  // 99999999943 * 99999999947
    {"9999999940000000073359", false},  // 99999999829 * 99999999571
    {"8999999614669999502009", false},  // 99999995593 * 90000000113
    {"59469489332848408438249254427481121839977",
     false},  // 175656509371887105761 * 338555568168236555657,
    {"12585343323244807147760102649942745852986103",
     false}  // 4443534478423724553557 * 2832282135843641284379
};
}

namespace LargePrimeNumbers {

std::map<bigint, bool> get_prime_numbers_data() {
  std::map<bigint, bool> result;
  for (auto [number_str, is_prime] : kPrimeNumbersData) {
    result[bigint(number_str)] = is_prime;
  }
  return result;
}

}  // namespace LargePrimeNumbers
