cmake_minimum_required(VERSION 3.20)
project(LargePrimeNumbers)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=undefined")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

find_package(
  Boost
  COMPONENTS log
  REQUIRED)

find_package(Matplot++ REQUIRED)

include_directories(
  src
  src/quadratic_sieve
  src/dixons_algorithm
  src/pollard_rho
  src/cfrac
  src/fermat_pseudoprimality
  src/strong_pseudoprimality
  src/legendre_symbol)

add_library(
  prime_numbers_library
  src/random.cpp
  src/trial_primality_test.cpp
  src/trial_find_factor.cpp
  src/quadratic_sieve/find_congruence.cpp
  src/quadratic_sieve/find_factor_base.cpp
  src/pollard_rho/pollard_rho_find_factor.cpp
  src/pollard_rho/pollard_rho_one_find_factor.cpp
  src/fermat_pseudoprimality/fermat_pseudoprimality_test.cpp
  src/strong_pseudoprimality/strong_pseudoprimality_test.cpp
  src/legendre_symbol/legendre_symbol.cpp
  src/quadratic_sieve/find_factor_quadratic_sieve.cpp
  src/dixons_algorithm/f2_matrix.cpp
  src/dixons_algorithm/dixons_algorithm.cpp
  src/cfrac/bhascara_brounker_sequence.cpp
  src/cfrac/find_factor_cfrac.cpp)

target_link_libraries(prime_numbers_library Boost::boost Boost::log
                      ${CONAN_LIBS})

add_subdirectory("benchmarks")
add_subdirectory("example")
add_subdirectory("tests")
