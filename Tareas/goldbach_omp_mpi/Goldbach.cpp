/**
 * @file Goldbach.cpp
 * @author Jarod Venegas Alpizar (JAROD.VENEGAS@ucr.ac.cr)
 * @brief Aplica las respectivas conjeturas de golbach y maneja la parte de
 * OpenMp
 * @version 1.0
 * @date 2021-07-27
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "Goldbach.hpp"

/**
 * @brief Construye un nuevo objeto Goldbach
 *
 */
Goldbach::Goldbach() {}

/**
 * @brief Destruye un objeto Goldbach
 *
 */
Goldbach::~Goldbach() {}

/**
 * @brief Determina si un numero es primo. Se obtuvo referencias del codigo en
 * internet.
 * @param number entero
 * @return devuelve un 1 si es primo y un 0 si no es primo
 * @link https://en.wikipedia.org/wiki/Primality_test @endlink
 */
bool Goldbach::is_prime(int64_t number) {
  if (number == 2 || number == 3 || number == 5 || number == 7) {
    return true;
  }
  if (number % 2 == 0 || number % 3 == 0 || number % 5 == 0 ||
      number % 7 == 0) {
    return false;
  } else {
    for (int64_t i = 11; i * i <= number; i += 6) {
      if (number % i == 0 || number % (i + 2) == 0) {
        return false;
      }
    }
    return true;
  }
}
/**
 * @brief Determina si un numero es par o impar
 * @param number entero de 64 bits
 * @return devuelve un 1 si es par y un 0 si es impar
 */
bool Goldbach::even_odd(int64_t number) {
  if (number < 0) {
    number = number * -1;
  }
  if (number % 2 == 0) {
    return true;
  }
  return false;
}

/**
 * @brief Calcula las sumas impares de goldbach. Se utiliza OpenMp para repartir
 * el trabajo entre los hilos.
 * 
 * @param data 
 * @param prime_vector 
 * @param number_of_threads 
 */
void Goldbach::strong_conjecture(Data_of_number& data,
                                 std::vector<int64_t> prime_vector,
                                 int number_of_threads) {
  int64_t number = data.number;
  int64_t number_temp = 0;
  if (number < 0) {
    number_temp = number * -1;
  } else {
    number_temp = number;
  }

#pragma omp parallel num_threads(number_of_threads)
  {
    int64_t size = 40;
    int64_t counter = 0;
    int64_t posible_number = 0;

    data.sums_by_threads[omp_get_thread_num()].sums =
        (Sums*)calloc(size, sizeof(Sums));

#pragma omp for schedule(static)
    for (int64_t x = 2; x <= number_temp / 2; x++) {
      if (prime_vector[x] == 1) {
        posible_number = number_temp - x;
        if (x + posible_number == number_temp &&
            prime_vector[posible_number] == 1) {
          if (posible_number > 2 && posible_number >= x) {
            if (number < 0) {
              if (counter == size) {
                size = size * 2;
                data.sums_by_threads[omp_get_thread_num()].sums =
                    (Sums*)realloc(
                        data.sums_by_threads[omp_get_thread_num()].sums,
                        size * sizeof(Sums));
              }
              data.sums_by_threads[omp_get_thread_num()].sums[counter].first =
                  x;
              data.sums_by_threads[omp_get_thread_num()].sums[counter].second =
                  posible_number;
            }
            counter++;
          }
        }
      }
    }
    data.sums_by_threads[omp_get_thread_num()].number_of_sums = counter;
  }
}

/**
 * @brief Calcula las sumas impares de goldbach. Se utiliza OpenMp para repartir
 * el trabajo entre los hilos.
 * 
 * @param data 
 * @param prime_vector 
 * @param number_of_threads 
 */
void Goldbach::weak_conjecture(Data_of_number& data,
                               std::vector<int64_t> prime_vector,
                               int number_of_threads) {
  int64_t number = data.number;
  int64_t number_temp = 0;
  if (number < 0) {
    number_temp = number * -1;
  } else {
    number_temp = number;
  }

#pragma omp parallel num_threads(number_of_threads)
  {
    int64_t size = 40;
    int64_t counter = 0;
    int64_t posible_number = 0;

    data.sums_by_threads[omp_get_thread_num()].sums =
        (Sums*)calloc(size, sizeof(Sums));
#pragma omp for schedule(static)
    for (int64_t x = 2; x <= number_temp / 2; x++) {
      if (prime_vector[x] == 1) {
        for (int64_t y = x; y <= number_temp / 2; y += 2) {
          if (prime_vector[y] == 1) {
            posible_number = number_temp - (x + y);

            if (x + y + posible_number == number_temp &&
                prime_vector[posible_number] == 1) {
              if (posible_number > 2 && posible_number >= y) {
                if (number < 0) {
                  if (counter == size) {
                    size = size * 2;
                    data.sums_by_threads[omp_get_thread_num()].sums =
                        (Sums*)realloc(
                            data.sums_by_threads[omp_get_thread_num()].sums,
                            size * sizeof(Sums));
                  }
                  data.sums_by_threads[omp_get_thread_num()]
                      .sums[counter]
                      .first = x;
                  data.sums_by_threads[omp_get_thread_num()]
                      .sums[counter]
                      .second = y;
                  data.sums_by_threads[omp_get_thread_num()]
                      .sums[counter]
                      .third = posible_number;
                }
                counter++;
              }
            }
          }
        }
      }
    }
    data.sums_by_threads[omp_get_thread_num()].number_of_sums = counter;
  }
}
