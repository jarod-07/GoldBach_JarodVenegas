/**
 * @file Interfaz.cpp
 * @author Jarod Venegas Alpizar (JAROD.VENEGAS@ucr.ac.cr)
 * @brief Maneja todo lo que hace interaccion con el usuario
 * @version 1.0
 * @date 2021-07-27
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef INTERFAZ_
#define INTERFAZ_

#include <inttypes.h>
#include <string>
#include <vector>

#include "Struct.hpp"
#include "unistd.h"

class Interfaz {
 public:
  Interfaz();
  ~Interfaz();
  void input_numbers(std::vector<int64_t>& vector_of_numbers,
                     int64_t& counter_of_numbers, int64_t& size_of_prime);
  std::string toString_even(Data_of_number data, int threads);
  std::string toString_odd(Data_of_number data, int threads);
};
#endif
