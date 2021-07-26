/**
 * @file Goldbach_controller.hpp
 * @author Jarod Venegas Alpizar (JAROD.VENEGAS@ucr.ac.cr)
 * @brief Controla la conjetura del goldbach y la parte del MPI
 * @version 1.0
 * @date 2021-07-27
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef GOLDBACH_CONTROLLER_
#define GOLDBACH_CONTROLLER_

#include <math.h>

#include "Goldbach.hpp"

class Goldbach_controller {
 private:
  Goldbach goldbach;
  Interfaz interfaz;
  int number_of_threads;

 public:
  Goldbach_controller();
  ~Goldbach_controller();
  bool is_valid(int64_t number);
  void set_threads(int num_threads);
  void create_prime_vector(int64_t size);

  void create_prime_vector(std::vector<int64_t>& prime_vector, int64_t size);

  std::string goldbach_conjecture(std::vector<int64_t> goldbach_numbers,
                                  std::vector<int64_t> prime_vector,
                                  int64_t counter, int my_rank,
                                  int number_of_process);

  int64_t where_to_begin(int64_t rank, int64_t num, int64_t start,
                         int64_t process_count);

  int64_t where_to_end(int64_t rank, int64_t num, int64_t start,
                       int64_t process_count);
};
#endif
