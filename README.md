# LargePrimeNumbers

This repository contains implementations of various algorithms for primality testing and factorization

## Implemented algorithms:

1. Trial Factorization
2. Trial Primality Test
3. Pollard Rho
4. Pollard Rho-1
5. Fermat Pseudoprimality Test
6. Miller-Rabin Pseudoprimality Test
7. Dixon's Algorithm
8. Quadratic Sieve
9. CFRAC

## Setup Guide with CMake:

Follow these steps to set up the project using CMake:

**Clone the Repository:**
   ```sh
   git clone https://github.com/your-username/LargePrimeNumbers.git
   cd LargePrimeNumbers
   ```

**Create a Build Directory::**
   ```sh
   mkdir build
   cd build
   ```

**Run CMake:**
   ```sh
   cmake ..
   ```

**Build the Project:**
   ```sh
   cmake --build .
   ```

## CMake Targets Description

### tests
- **Description:** This target includes all tests. To run only speciefic test, you can use ctest.

### example
- **Description:** Sample of using library for factorizing arbitrary integer. 

### benchmark_cfrac
- **Description:** Run benchmarks for Continued Fraction Factorization (CFRAC) algorithm.

### benchmark_quadratic_sieve
- **Description:** Run benchmarks for Quadratic Sieve algorithm.

### plot_stats_by_bases_count
- **Description:** Compare the number of detected "probable primes" by the Fermat and Miller-Rabin tests with respect to the number of bases used.


