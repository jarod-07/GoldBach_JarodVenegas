/**
 * @file Struct.hpp
 * @author Jarod Venegas Alpizar (JAROD.VENEGAS@ucr.ac.cr)
 * @brief Contiene los struct necesarios para el programa
 * @version 1.0
 * @date 2021-07-27
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef STRUCT_
#define STRUCT_

#include "stdint.h"
/**
 * @brief Contiene una suma de un numero
 *
 */
typedef struct {
  int64_t first;
  int64_t second;
  int64_t third;
} Sums;

/**
 * @brief Informacion de cada hilo sobre la cantidad de sumas hechas
 *
 */
typedef struct {
  int64_t number_of_sums;
  Sums* sums;
} Thread_sums;

/**
 * @brief Informacion de todos los hilos sobre el numero
 *
 */
typedef struct {
  int64_t number;
  Thread_sums* sums_by_threads;
} Data_of_number;

#endif
