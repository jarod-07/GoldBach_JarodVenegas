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

void goldbach(private_data_t* private_data, int64_t number);
void complete_structure(shared_data_t* shared_data);
void* run_threads(void* data);
int create_threads(shared_data_t* shared_data);

#endif
