/**
 * @file Goldbach.hpp
 * @author Jarod Venegas Alpizar (JAROD.VENEGAS@ucr.ac.cr)
 * @brief Aplica las respectivas conjeturas de golbach y maneja la parte de
 * OpenMp
 * @version 1.0
 * @date 2021-07-27
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef GOLDBACH_
#define GOLDBACH_

#include <iostream>

#include "Interfaz.hpp"
#include "omp.h"
#include "Struct.hpp"
#include "unistd.h"

class Goldbach {
 public:
  Goldbach();
  ~Goldbach();
  void strong_conjecture(Data_of_number& data,
                         std::vector<int64_t> prime_vector,
                         int number_of_threads);
  void weak_conjecture(Data_of_number& data, std::vector<int64_t> prime_vector,
                       int number_of_threads);
  bool is_prime(int64_t number);
  bool even_odd(int64_t number);
};
#endif
