add_executable(plot_stats_by_bases_count plot_stats_by_bases_count.cpp)
target_link_libraries(plot_stats_by_bases_count prime_numbers_library Matplot++::matplot)

add_executable(benchmark_quadratic_sieve benchmark_quadratic_sieve.cpp utility/becnmark_data.cpp)
target_link_libraries(benchmark_quadratic_sieve prime_numbers_library)

add_executable(benchmark_cfrac benchmark_cfrac.cpp utility/becnmark_data.cpp)
target_link_libraries(benchmark_cfrac prime_numbers_library)
