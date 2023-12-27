cmake_minimum_required(VERSION 3.20)
project(LargePrimeNumbers)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror")

find_package(
  Boost
  COMPONENTS log
  REQUIRED)

# Creating library
include_directories(src)
add_library(
  prime_numbers_library
  src/trial_primality_test.cpp src/fermat_pseudoprimality_test.cpp
  src/trial_find_factor.cpp src/pollard_rho_find_factor.cpp
  src/pollard_rho_one_find_factor.cpp)
target_link_libraries(prime_numbers_library Boost::boost Boost::log
                      ${CONAN_LIBS})

# Creating example
add_executable(example src/example.cpp)
target_link_libraries(example prime_numbers_library)

# Testing
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(tests tests/test_find_factors.cpp tests/test_primality_tests.cpp)
target_link_libraries(tests prime_numbers_library GTest::gtest_main)
gtest_discover_tests(tests)
