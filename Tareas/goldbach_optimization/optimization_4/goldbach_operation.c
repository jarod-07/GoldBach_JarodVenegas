/**
 * @file goldbach_pthread.c
 * @author Jarod Venegas Alpizar (JAROD.VENEGAS@ucr.ac.cr)
 * @brief Controla las operaciones para calcular la conjetura de Goldbach
 * @version 1.0
 * @date 2021-05-30
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "goldbach_operation.h"

/**
 * @brief Determina si un numero es primo
 * @param number entero de 64 bits
 * @return devuelve un 1 si es primo y un 0 si no es primo
 */
int is_prime(int64_t number) {
  if (number == 2 || number == 3 || number == 5 || number == 7) {
    return 1;
  }
  if (number % 2 == 0 || number % 3 == 0 || number % 5 == 0 ||
      number % 7 == 0) {
    return 0;
  } else {
    for (int64_t i = 11; i * i <= number; i += 6) {
      if (number % i == 0 || number % (i + 2) == 0) {
        return 0;  // no es primo
      }
    }
    return 1;  // si es primo
  }
}

/**
 * @brief Determina si un numero es par o impar
 * @param number entero de 64 bits
 * @return devuelve un 1 si es par y un 0 si es impar
 */
int even_odd(int64_t number) {
  if (number < 0) {
    number = number * -1;
  }
  if (number % 2 == 0) {
    return 1;  // el numero es par
  }
  return 0;  // el numero es impar
}

/**
 * @brief Para todo numero impar utiliza la conjetura fuerte de goldbach
 * @param num_temp entero de 64 bits
 * @param counter entero de 64 bits
 * @param output file
 * @return struct Sumas
 */
Sums* strong_conjecture(int64_t* prime_vector, int64_t num_temp,
                        int64_t* counter, FILE* output) {
  int64_t number = 0;

  if (num_temp < 0) {
    number = num_temp * -1;
  } else {
    number = num_temp;
  }
  int size = 10;

  Sums* sums = (Sums*)calloc(size, sizeof(Sums));
  int64_t pivot = 2;
  for (int64_t i = number - pivot; i > 2; i--) {
    if ((prime_vector[pivot] == 1) && (prime_vector[i] == 1) && pivot <= i) {
      if (num_temp < 0) {
        sums[*counter].first = (int64_t)pivot;
        sums[*counter].second = (int64_t)i;
      }
      *counter = *counter + 1;
      if (*counter == size && num_temp < 0) {
        size = size * 2;
        Sums* sums_temp = realloc(sums, (size * 2) * sizeof(Sums));
        if (sums_temp == NULL) {
          fprintf(output, "Memory not reallocated\n");
          exit(0);
        } else {
          sums = sums_temp;
        }
      }
    }
    pivot++;
  }
  return sums;
}

/**
 * @brief Para todo numero impar utiliza la conjetura debil de goldbach
 * @param num_temp entero de 64 bits
 * @param counter entero de 64 bits
 * @param output file
 * @return struct Sumas
 */
Sums* weak_conjecture(int64_t* prime_vector, int64_t num_temp, int64_t* counter,
                      FILE* output) {
  int64_t number = 0;

  if (num_temp < 0) {
    number = num_temp * -1;
  } else {
    number = num_temp;
  }

  int size = 10;

  Sums* sums = (Sums*)calloc(size, sizeof(Sums));

  for (int64_t x = 2; x < number / 2; x++) {
    if (prime_vector[x] == 1) {
      for (int64_t y = x; y < number / 2; y++) {
        if (prime_vector[y] == 1) {
          int64_t posible_number = number - (x + y);
          if (x + y + posible_number == number &&
              prime_vector[posible_number] == 1) {
            if (posible_number > 2 && posible_number >= y) {
              if (num_temp < 0) {
                sums[*counter].first = (int64_t)x;
                sums[*counter].second = (int64_t)y;
                sums[*counter].third = (int64_t)posible_number;
              }
              *counter = *counter + 1;
              if (*counter == size && num_temp < 0) {
                size = size * 2;
                Sums* sums_temp = realloc(sums, (size * 2) * sizeof(Sums));
                if (sums_temp == NULL) {
                  fprintf(output, "Memory not reallocated\n");
                  exit(0);
                } else {
                  sums = sums_temp;
                }
              }
            }
          }
        }
      }
    }
  }
  return sums;
}
