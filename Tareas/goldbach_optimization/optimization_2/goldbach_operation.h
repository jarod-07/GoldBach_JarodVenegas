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
void strong_conjecture(private_data_t* private_data, int64_t position);
void weak_conjecture(private_data_t* private_data, int64_t position);

#endif
