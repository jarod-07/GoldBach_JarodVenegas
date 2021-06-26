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

// Metodos privados
/**
 * @brief Determina donde empieza cada hilo
 * @param thread_id
 * @param number_of_threads
 * @param iterations cantidad de iteraciones
 * @param start empieza en 2
 * @return int64_t
 */
int64_t where_to_begin(int64_t thread_id, int64_t number_of_threads,
                       int64_t iterations, int64_t start) {
  int64_t normal = thread_id * ((iterations - start) / number_of_threads);
  int64_t remainder = 0;
  if (thread_id < ((iterations - start) % number_of_threads)) {
    remainder = thread_id;
  } else {
    remainder = (iterations - start) % number_of_threads;
  }
  int64_t begin = start + normal + remainder;
  return begin;
}

/**
 * @brief Determina donde termina cada hilo
 * @param thread_id
 * @param number_of_threads
 * @param iterations cantidad de iteraciones
 * @param start empieza en 2
 * @return int64_t
 */
int64_t where_to_end(int64_t thread_id, int64_t number_of_threads,
                     int64_t iterations, int64_t start) {
  int64_t thread_next = thread_id + 1;
  return where_to_begin(thread_next, number_of_threads, iterations, start);
}
// Fin de metodos privados
/**
 * @brief Determina si un numero es primo. Se obtuvo referencias del codigo en
 * internet.
 * @param number entero
 * @return devuelve un 1 si es primo y un 0 si no es primo
 * @link https://en.wikipedia.org/wiki/Primality_test @endlink
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
 * @param private_data struct private_data_t
 * @param position posicion dentro del vector de Sums
 * @return struct Sumas
 */
void strong_conjecture(private_data_t* private_data, int64_t position) {
  int64_t number_of_threads = private_data->shared_data->number_of_threads;
  int64_t num_temp = private_data->goldbach_number;
  int64_t thread_id = private_data->thread_id;
  int64_t counter = 0;
  int64_t number = 0;

  if (num_temp < 0) {
    number = num_temp * -1;
  } else {
    number = num_temp;
  }

  int64_t iterations = (number / 2) + 1;
  int64_t start = where_to_begin(thread_id, number_of_threads, iterations, 2);
  int64_t end = where_to_end(thread_id, number_of_threads, iterations, 2);

  queue_init(&private_data->shared_data->sums_vector[position]
                  .sums_of_thread[thread_id]);

  for (int64_t x = start; x < end; x++) {
    if ((is_prime(x) == 1)) {
      int64_t posible_number = number - x;
      if (is_prime(posible_number) == 1 && (x + posible_number) == number) {
        if (posible_number > 2 && posible_number >= x) {
          if (num_temp < 0) {
            queue_enqueue(&private_data->shared_data->sums_vector[position]
                               .sums_of_thread[thread_id],
                          (int64_t)x);
            queue_enqueue(&private_data->shared_data->sums_vector[position]
                               .sums_of_thread[thread_id],
                          (int64_t)posible_number);
          }
          counter = counter + 1;
        }
      }
    }
  }
  private_data->shared_data->sums_vector[position].counter_of_sums[thread_id] =
      counter;
}

/**
 * @brief Para todo numero impar utiliza la conjetura debil de goldbach
 * @param private_data struct private_data_t
 * @param position posicion dentro del vector de Sums
 * @return struct Sumas
 */
void weak_conjecture(private_data_t* private_data, int64_t position) {
  int64_t number_of_threads = private_data->shared_data->number_of_threads;
  int64_t num_temp = private_data->goldbach_number;
  int64_t thread_id = private_data->thread_id;
  int64_t counter = 0;
  int64_t number = 0;

  if (num_temp < 0) {
    number = num_temp * -1;
  } else {
    number = num_temp;
  }

  int64_t iterations = number / 2;
  int64_t start = where_to_begin(thread_id, number_of_threads, iterations, 2);
  int64_t end = where_to_end(thread_id, number_of_threads, iterations, 2);

  queue_init(&private_data->shared_data->sums_vector[position]
                  .sums_of_thread[thread_id]);

  for (int64_t x = start; x < end; x++) {
    if (is_prime(x) == 1) {
      for (int64_t y = x; y < number; y++) {
        if (is_prime(y) == 1) {
          int64_t posible_number = number - (x + y);
          if (x + y + posible_number == number &&
              is_prime(posible_number) == 1) {
            if (posible_number > 2 && posible_number >= y) {
              if (num_temp < 0) {
                queue_enqueue(&private_data->shared_data->sums_vector[position]
                                   .sums_of_thread[thread_id],
                              (int64_t)x);
                queue_enqueue(&private_data->shared_data->sums_vector[position]
                                   .sums_of_thread[thread_id],
                              (int64_t)y);
                queue_enqueue(&private_data->shared_data->sums_vector[position]
                                   .sums_of_thread[thread_id],
                              (int64_t)posible_number);
              }
              counter = counter + 1;
            }
          }
        }
      }
    }
  }
  private_data->shared_data->sums_vector[position].counter_of_sums[thread_id] =
      counter;
}
