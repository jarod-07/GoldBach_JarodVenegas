/**
 * @file goldbach_pthread.c
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

#include <semaphore.h>

#include "goldbach_operation.h"
#include "queue.h"

/**
 * @brief Estructura utilizada para tener informacion compartida por los hilos
 *
 */
typedef struct {
    Sums** sums_vector;
    int64_t number_counter;
    queue_t numbers_queue;
    sem_t sem_get_position;
    int64_t thread_position;
    int64_t number_of_threads;
} shared_data_t;

/**
 * @brief Estructura utilizada para tener informacion privada de cada hilo
 *
 */
typedef struct {
    int64_t position;
    int64_t goldbach_number;
    shared_data_t* shared_data;
} private_data_t;

void goldbach(private_data_t* private_data);
void* run_threads(void* data);
int create_threads(shared_data_t* shared_data);

#endif
