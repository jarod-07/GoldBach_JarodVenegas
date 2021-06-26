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
#include "interfaz.h"

/**
 * @brief Controla la impresion de todas las sumas de cada numero
 * @param shared_data struct shared_data
 * @return void
 */
void print_goldbach(shared_data_t* shared_data) {
  for (int64_t i = 0; i < shared_data->number_counter; i++) {
    if (shared_data->sums_vector[i]->major_limit == 0) {
      fprintf(stdout, "NA");
    } else {
      if (shared_data->sums_vector[i]->minor_limit == 0) {
        if (shared_data->sums_vector[i]->number < 0) {
          shared_data->sums_vector[i]->number =
              shared_data->sums_vector[i]->number * -1;
          fprintf(stdout, "-%" PRIu64 ": NA\n",
                  shared_data->sums_vector[i]->number);
        } else {
          fprintf(stdout, "%" PRIu64 ": NA\n",
                  shared_data->sums_vector[i]->number);
        }
      } else {
        if (shared_data->sums_vector[i]->number % 2 == 0) {
          print_strong(shared_data->sums_vector[i]->number,
                       shared_data->sums_vector[i]->sums,
                       shared_data->sums_vector[i]);
        } else {
          print_weak(shared_data->sums_vector[i]->number,
                     shared_data->sums_vector[i]->sums,
                     shared_data->sums_vector[i]);
        }
      }
    }
  }
}

/**
 * @brief Controla el ingreso de datos, los almacena en una cola y asigna una
 * posicion a cada hilo
 * @param shared_data struct shared_data
 */
int input_number(shared_data_t* shared_data) {
  int64_t number = 0;
  int size = 10;

  shared_data->numbers_vec = (int64_t*)calloc(size, sizeof(int64_t));

  if (shared_data->numbers_vec) {
    while (fscanf(stdin, "%" SCNu64, &number) == 1) {
      if (shared_data->number_counter == size) {
        shared_data->numbers_vec = (int64_t*)realloc(
            shared_data->numbers_vec, (size * 2) * sizeof(int64_t));
        if (shared_data->numbers_vec == NULL) {
          fprintf(stdout, "Memory not reallocated\n");
          exit(0);
        } else {
          size = size * 2;

          shared_data->numbers_vec[shared_data->number_counter] = number;
        }
      } else {
        shared_data->numbers_vec[shared_data->number_counter] = number;
      }

      shared_data->number_counter++;
    }
    if (shared_data->number_of_threads >= shared_data->number_counter) {
      shared_data->number_of_threads = shared_data->number_counter;
    }
  } else {
    fprintf(stdout, "Could not allocate the memeory.");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

/**
 * @brief Imprime las sumas de la conjetura debil
 * @param num_temp entero de 64 bits
 * @param counter entero de 64 bits
 * @param sums Struct Sumas
 * @param output file
 * @return void
 */
void print_weak(int64_t num_temp, int64_t counter, Sums* sums) {
  int64_t first;
  int64_t second;
  int64_t third;
  int64_t number = 0;
  if (num_temp < 0) {
    number = num_temp * -1;
  }
  if (num_temp < 0) {
    fprintf(stdout,
            "-%" PRIu64
            ": "
            "%" PRIu64 " sums: ",
            number, counter);
    for (int i = 0; i < counter; i++) {
      if (i != counter - 1) {
        first = sums[i].first;
        second = sums[i].second;
        third = sums[i].third;
        fprintf(stdout,
                "%" PRIu64
                " + "
                "%" PRIu64
                " + "
                "%" PRIu64 ", ",
                first, second, third);
      } else {
        first = sums[i].first;
        second = sums[i].second;
        third = sums[i].third;
        fprintf(stdout,
                "%" PRIu64
                " + "
                "%" PRIu64
                " + "
                "%" PRIu64 "\n",
                first, second, third);
      }
    }
  } else {
    fprintf(stdout,
            "%" PRIu64
            ": "
            "%" PRIu64 " sums\n",
            num_temp, counter);
  }
}

/**
 * @brief Imprime las sumas de la conjetura debil
 * @param num_temp entero de 64 bits
 * @param counter entero de 64 bits
 * @param sums struct Sumas
 * @param output file
 * @return void
 */
void print_strong(int64_t num_temp, int64_t counter, Sums* sums) {
  int64_t first;
  int64_t second;
  int64_t number = 0;
  if (num_temp < 0) {
    number = num_temp * -1;
  }
  if (num_temp < 0) {
    fprintf(stdout,
            "-%" PRIu64
            ": "
            "%" PRIu64 " sums: ",
            number, counter);
    for (int i = 0; i < counter; i++) {
      if (i != counter - 1) {
        first = sums[i].first;
        second = sums[i].second;
        fprintf(stdout,
                "%" PRIu64
                " + "
                "%" PRIu64 ", ",
                first, second);
      } else {
        first = sums[i].first;
        second = sums[i].second;
        fprintf(stdout,
                "%" PRIu64
                " + "
                "%" PRIu64 "\n",
                first, second);
      }
    }
  } else {
    fprintf(stdout,
            "%" PRIu64
            ": "
            "%" PRIu64 " sums\n",
            num_temp, counter);
  }
}
