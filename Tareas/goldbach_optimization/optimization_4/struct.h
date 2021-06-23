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
#ifndef STRUCT_
#define STRUCT_

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

/**
 * @brief Estructura utilizada para almacenar los datos compartidos entre la n
 * cantidad de hilos
 *
 */
typedef struct {
    FILE* input;
    FILE* output;
    Sums** sums_vector;
    int64_t number_counter;
    int64_t* numbers_vec;
    int64_t* prime_vector;
    int64_t thread_position;
    int64_t number_of_threads;
} shared_data_t;

/**
 * @brief Estructura utilizada para alamcenar los datos privados de los hilos
 *
 */
typedef struct {
    int64_t position;
    int64_t thread_id;
    int64_t goldbach_number;
    shared_data_t* shared_data;
} private_data_t;

#endif