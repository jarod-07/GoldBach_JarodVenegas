#ifndef INTERFAZ_
#define INTERFAZ_
#include <inttypes.h>

#include <string>
#include <vector>

#include "Structs.hpp"
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