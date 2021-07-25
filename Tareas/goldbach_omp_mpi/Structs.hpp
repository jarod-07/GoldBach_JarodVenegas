// Copyright 2021 Luis Alberto Bolanos
#ifndef STRUCTS
#define STRUCTS

#include "stdint.h"
/**
 * @brief
 *
 */
typedef struct {
  int64_t first;
  int64_t second;
  int64_t third;
} Sums;

/**
 * @brief 
 * 
 */
typedef struct {
  int64_t number_of_sums;
  Sums* sums;
} Thread_sums;

/**
 * @brief 
 * 
 */
typedef struct {
  int64_t number;
  Thread_sums* sums_by_threads;
} Data_of_number;

#endif
