/**
 * @file goldbach_pthread.h
 * @author Jarod Venegas Alpizar (JAROD.VENEGAS@ucr.ac.cr)
 * @brief Controla los hilos del programa de la conjetura Goldbach_Pthreads
 * @version 1.0
 * @date 2021-05-30
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef GOLDBACH_PTHREAD
#define GOLDBACH_PTHREAD

#include <assert.h>

#include "goldbach_operation.h"

/**
 * @brief Estructura utilizada para almacenar los datos compartidos entre la n
 * cantidad de hilos
 *
 */
typedef struct {
  Sums** sums_vector;
  int64_t number_counter;
  int64_t* numbers_vec;
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

void goldbach(private_data_t* private_data, int64_t number);
void* run_threads(void* data);
int create_threads(shared_data_t* shared_data);

#endif
