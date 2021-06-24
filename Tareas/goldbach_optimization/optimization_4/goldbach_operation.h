/**
 * @file goldbach_pthread.h
 * @author Jarod Venegas Alpizar (JAROD.VENEGAS@ucr.ac.cr)
 * @brief Controla las operaciones para calcular la conjetura de Goldbach
 * @version 1.0
 * @date 2021-05-30
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef GOLDBACH_OPERATION
#define GOLDBACH_OPERATION

#include "struct.h"

int is_prime(int64_t number);
int even_odd(int64_t number);
Sums* strong_conjecture(int64_t* prime_vector, int64_t num_temp,
                        int64_t* counter, FILE* output);
Sums* weak_conjecture(int64_t* prime_vector, int64_t num_temp, int64_t* counter,
                      FILE* output);

#endif
