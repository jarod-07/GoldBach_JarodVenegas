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
 * @param shared_data struct shared_data_t
 * @param position posicion dentro del vector de Sums
 * @return void
 */
void major_limit_def(shared_data_t* shared_data, int64_t position) {
  int64_t size = shared_data->number_of_threads;
  shared_data->sums_vector[position].counter_of_sums =
      (int64_t*)calloc(size, sizeof(int64_t));
  shared_data->sums_vector[position].sums_of_thread =
      (queue_t*)calloc(size, sizeof(queue_t));
  shared_data->sums_vector[position].sums = 0;
  shared_data->sums_vector[position].number = 0;
  shared_data->sums_vector[position].major_limit = 0;
  shared_data->sums_vector[position].minor_limit = 1;
}

/**
 * @brief metodo necesario para asignar los valores adecuados dentro de la
 * estructura Sums en caso de que el numero sea un valor entre [-5 , 5]
 * @param shared_data struct shared_data_t
 * @param number 
 * @param position posicion dentro del vector de Sums
 * @return void
 */
void minor_limit_def(shared_data_t* shared_data, int64_t number,
                     int64_t position) {
  int64_t size = shared_data->number_of_threads;
  shared_data->sums_vector[position].counter_of_sums =
      (int64_t*)calloc(size, sizeof(int64_t));
  shared_data->sums_vector[position].sums_of_thread =
      (queue_t*)calloc(size, sizeof(queue_t));
  shared_data->sums_vector[position].sums = 0;
  shared_data->sums_vector[position].number = number;
  shared_data->sums_vector[position].major_limit = 1;
  shared_data->sums_vector[position].minor_limit = 0;
}

/**
 * @brief metodo necesario para asignar los valores adecuados dentro de la
 * estructura Sums en caso de que el numero sea par (sin importar si es negativo
 * o positivo)
 * @param shared_data struct shared_data_t
 * @param number 
 * @param position posicion dentro del vector de Sums
 * @return void
 */
void strong_conjecture_def(shared_data_t* shared_data, int64_t number,
                           int64_t position) {
  int64_t size = shared_data->number_of_threads;
  shared_data->sums_vector[position].counter_of_sums =
      (int64_t*)calloc(size, sizeof(int64_t));
  shared_data->sums_vector[position].sums_of_thread =
      (queue_t*)calloc(size, sizeof(queue_t));
  shared_data->sums_vector[position].sums = 0;
  shared_data->sums_vector[position].number = number;
  shared_data->sums_vector[position].major_limit = 1;
  shared_data->sums_vector[position].minor_limit = 1;
}

/**
 * @brief metodo necesario para asignar los valores adecuados dentro de la
 * estructura Sums en caso de que el numero sea impar (sin importar si es
 * negativo o positivo)
 * @param shared_data struct shared_data_t
 * @param number 
 * @param position posicion dentro del vector de Sums
 * @return void
 */
void weak_conjecture_def(shared_data_t* shared_data, int64_t number,
                         int64_t position) {
  int64_t size = shared_data->number_of_threads;
  shared_data->sums_vector[position].counter_of_sums =
      (int64_t*)calloc(size, sizeof(int64_t));
  shared_data->sums_vector[position].sums_of_thread =
      (queue_t*)calloc(size, sizeof(queue_t));
  shared_data->sums_vector[position].sums = 0;
  shared_data->sums_vector[position].number = number;
  shared_data->sums_vector[position].major_limit = 1;
  shared_data->sums_vector[position].minor_limit = 1;
}

// fin de metodos privados

/**
 * @brief Controla la entrada de datos y aplica la conjetura de goldbach
 * @param private_data struct que contiene los datos privados del hilo
 * @param position posicion dentro del vector de Sums
 * @return void
 */
void goldbach(private_data_t* private_data, int64_t position) {
  if (private_data->goldbach_number > ((int64_t)pow(2, 63) - 1) ||
      private_data->goldbach_number < -((int64_t)pow(2, 63) - 1)) {
    // no hace nada
  } else {
    if ((private_data->goldbach_number <= 5 &&
         private_data->goldbach_number >= -5)) {
      // no hace nada
    } else {
      if (even_odd(private_data->goldbach_number) == 1) {
        strong_conjecture(private_data, position);
      } else {
        weak_conjecture(private_data, position);
      }
    }
  }
}

/**
 * @brief Funcion para controlar los hilos. Cada hilo agarra el mismo numero
 * @param data void que recibe un private_data
 * @return void
 */
void* run_threads(void* data) {
  private_data_t* private_data = (private_data_t*)data;
  shared_data_t* shared_data = private_data->shared_data;
  for (int i = 0; i < shared_data->number_counter; i++) {
    private_data->goldbach_number = shared_data->numbers_vec[i];
    goldbach(private_data, i);
  }

  return 0;
}

/**
 * @brief Para llenar el vector de las estrcututas de Sums con los datos
 * correspondientes
 * @param shared_data struct shared_data_t
 * @return void
 */
void complete_structure(shared_data_t* shared_data) {
  int64_t limit = shared_data->number_counter;
  for (int64_t i = 0; i < limit; i++) {
    if (shared_data->numbers_vec[i] > ((int64_t)pow(2, 63) - 1) ||
        shared_data->numbers_vec[i] < -((int64_t)pow(2, 63) - 1)) {
      major_limit_def(shared_data, i);
    } else {
      if ((shared_data->numbers_vec[i] <= 5 &&
           shared_data->numbers_vec[i] >= -5)) {
        minor_limit_def(shared_data, shared_data->numbers_vec[i], i);
      } else {
        if (even_odd(shared_data->numbers_vec[i]) == 1) {
          strong_conjecture_def(shared_data, shared_data->numbers_vec[i], i);
        } else {
          weak_conjecture_def(shared_data, shared_data->numbers_vec[i], i);
        }
      }
    }
  }
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
