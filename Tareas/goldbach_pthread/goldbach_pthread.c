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
#include "goldbach_pthread.h"

// inicio de metodos privados
/**
 * @brief metodo necesario para asignar los valores adecuados dentro de la
 * estructura Sums en caso de que el numero sea mas grande o más pequeño del
 * limite
 * @param private_data struct que contiene los datos privados del hilo
 * @return void
 */
void major_limit_def(private_data_t* private_data) {
  Sums* invalid_cases = (Sums*)calloc(1, sizeof(Sums));
  private_data->shared_data->sums_vector[private_data->position] =
      invalid_cases;
  private_data->shared_data->sums_vector[private_data->position]->major_limit =
      0;
  private_data->shared_data->sums_vector[private_data->position]->minor_limit =
      1;
}

/**
 * @brief metodo necesario para asignar los valores adecuados dentro de la
 * estructura Sums en caso de que el numero sea un valor entre [-5 , 5]
 * @param private_data struct que contiene los datos privados del hilo
 * @param number int de 64 bits
 * @return void
 */
void minor_limit_def(private_data_t* private_data, int64_t number) {
  Sums* invalid_cases = (Sums*)calloc(1, sizeof(Sums));
  private_data->shared_data->sums_vector[private_data->position] =
      invalid_cases;
  private_data->shared_data->sums_vector[private_data->position]->number =
      number;
  private_data->shared_data->sums_vector[private_data->position]->major_limit =
      1;
  private_data->shared_data->sums_vector[private_data->position]->minor_limit =
      0;
}

/**
 * @brief metodo necesario para asignar los valores adecuados dentro de la
 * estructura Sums en caso de que el numero sea par (sin importar si es negativo
 * o positivo)
 * @param private_data struct que contiene los datos privados del hilo
 * @param number int de 64 bits
 * @return void
 */
void strong_conjecture_def(private_data_t* private_data, int64_t number) {
  int64_t sums_counter = 0;
  Sums* even_sums = strong_conjecture(number, &sums_counter);

  even_sums->sums = sums_counter;
  private_data->shared_data->sums_vector[private_data->position] = even_sums;
  private_data->shared_data->sums_vector[private_data->position]->number =
      number;
  private_data->shared_data->sums_vector[private_data->position]->major_limit =
      1;
  private_data->shared_data->sums_vector[private_data->position]->minor_limit =
      1;
}

/**
 * @brief metodo necesario para asignar los valores adecuados dentro de la
 * estructura Sums en caso de que el numero sea impar (sin importar si es
 * negativo o positivo)
 * @param private_data struct que contiene los datos privados del hilo
 * @param number int de 64 bits
 * @return void
 */
void weak_conjecture_def(private_data_t* private_data, int64_t number) {
  int64_t sums_counter = 0;
  Sums* odd_sums = weak_conjecture(number, &sums_counter);
  odd_sums->sums = sums_counter;
  private_data->shared_data->sums_vector[private_data->position] = odd_sums;
  private_data->shared_data->sums_vector[private_data->position]->number =
      number;
  private_data->shared_data->sums_vector[private_data->position]->major_limit =
      1;
  private_data->shared_data->sums_vector[private_data->position]->minor_limit =
      1;
}
/**
 * @brief Calcula donde debe iniciar cada hilo
 * @param thread_id
 * @param number_of_threads
 * @param iterations
 * @param start siempre empiezan en 2
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

int64_t where_to_end(int64_t thread_id, int64_t number_of_threads,
                     int64_t iterations, int64_t start) {
  int64_t thread_next = thread_id + 1;
  return where_to_begin(thread_next, number_of_threads, iterations, start);
}
// fin de metodos privados

/**
 * @brief Controla la entrada de datos y aplica la conjetura de goldbach
 * @param private_data struct que contiene los datos privados del hilo
 * @param number int de 64 bits
 * @return void
 */
void goldbach(private_data_t* private_data, int64_t number) {
  if (number > ((int64_t)pow(2, 63) - 1) ||
      number < -((int64_t)pow(2, 63) - 1)) {
    major_limit_def(private_data);
  } else {
    if ((number <= 5 && number >= -5)) {
      minor_limit_def(private_data, number);
    } else {
      if (even_odd(number) == 1) {
        strong_conjecture_def(private_data, number);
      } else {
        weak_conjecture_def(private_data, number);
      }
    }
  }
}

/**
 * @brief Funcion para controlar los hilos: reparte el trabajo equitativemente
 * entre los hilos
 * @param data void que recibe un private_data
 * @return void
 */
void* run_threads(void* data) {
  private_data_t* private_data = (private_data_t*)data;
  shared_data_t* shared_data = private_data->shared_data;

  int64_t new_thread_id = private_data->thread_id;
  int64_t new_number_of_threads = private_data->shared_data->number_of_threads;
  int64_t new_iterations = shared_data->number_counter;
  int64_t new_start =
      where_to_begin(new_thread_id, new_number_of_threads, new_iterations, 0);

  int64_t new_end =
      where_to_end(new_thread_id, new_number_of_threads, new_iterations, 0);

  for (int64_t y = new_start; y < new_end; y++) {
    int64_t number = shared_data->numbers_vec[y];
    private_data->position = y;
    goldbach(private_data, number);
  }

  return 0;
}

/**
 * @brief Crea los hilos y envia cada hilo a ejecutar el codigo correspondiente
 * @param shared_data struct shared_data de todos los hilos
 * @return int error
 */
int create_threads(shared_data_t* shared_data) {
  assert(shared_data);
  int error = EXIT_SUCCESS;
  pthread_t* threads =
      (pthread_t*)calloc(shared_data->number_of_threads, sizeof(pthread_t));
  private_data_t* private_data = (private_data_t*)calloc(
      shared_data->number_of_threads, sizeof(private_data_t));
  if (threads && private_data) {
    for (int64_t index = 0; index < shared_data->number_of_threads; ++index) {
      private_data[index].thread_id = index;
      private_data[index].shared_data = shared_data;
      if (pthread_create(&threads[index], /*attr*/ NULL, run_threads,
                         &private_data[index]) == EXIT_SUCCESS) {
      } else {
        fprintf(stderr, "error: could not create thread %zu\n", index);
        error = 21;
        break;
      }
    }
    for (int64_t index = 0; index < shared_data->number_of_threads; ++index) {
      pthread_join(threads[index], /*value_ptr*/ NULL);
    }
    free(threads);
    free(private_data);
  } else {
    fprintf(stderr, "error: could not allocate memory for %zu threads\n",
            shared_data->number_of_threads);
    error = 22;
  }
  return error;
}
