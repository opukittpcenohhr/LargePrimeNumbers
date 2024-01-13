#pragma once

#include <boost/log/trivial.hpp>

namespace LargePrimeNumbers {

#define DEBUG() BOOST_LOG_TRIVIAL(debug)
#define INFO() BOOST_LOG_TRIVIAL(info)
#define WARNING() BOOST_LOG_TRIVIAL(warning)
#define ERROR() BOOST_LOG_TRIVIAL(error)

}  // namespace LargePrimeNumbers