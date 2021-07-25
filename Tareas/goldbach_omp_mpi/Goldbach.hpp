#ifndef GOLDBACH_
#define GOLDBACH_

#include "Intefaz.hpp"
#include "Structs.hpp"
#include "math.h"
#include "omp.h"
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
