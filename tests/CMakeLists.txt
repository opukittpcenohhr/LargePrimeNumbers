enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(
  tests
  test_find_factors.cpp test_primality_tests.cpp
  test_gaussian_elemination_algorithm.cpp test_factor_base.cpp test_bhascara_brounker_sequence.cpp
  data.cpp)
target_link_libraries(tests prime_numbers_library GTest::gtest_main)
gtest_discover_tests(tests)