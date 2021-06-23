/**
 * @file interfaz.h
 * @author Jarod Venegas Alpizar (JAROD.VENEGAS@ucr.ac.cr)
 * @brief Interfaz del programa de la conjetura de Goldbach_Pthreads que se
 * encarga de los metodos de impresion y entrada de datos
 * @version 1.0
 * @date 2021-05-30
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef INTERFAZ
#define INTERFAZ

#include "goldbach_operation.h"
#include "goldbach_pthread.h"

void print_goldbach(shared_data_t* shared_data);
int input_number(shared_data_t* shared_data, int64_t* size);
void print_weak(int64_t num_temp, int64_t counter, Sums* sums, FILE* output);
void print_strong(int64_t num_temp, int64_t counter, Sums* sums, FILE* output);

#endif
