/**
 * @file goldbach_operation.c
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

#include <inttypes.h>
#include <math.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * @brief Estructura utilizada para almacenar las sumas y luego imprimirlas
 *
 */
typedef struct {
    int64_t first;
    int64_t second;
    int64_t third;
    int64_t number;
    int64_t sums;
    int major_limit;
    int minor_limit;
} Sums;

int is_prime(int64_t number);
int even_odd(int64_t number);
Sums* strong_conjecture(int64_t num_temp, int64_t* counter);
Sums* weak_conjecture(int64_t num_temp, int64_t* counter);

#endif
