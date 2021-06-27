/**
 * @file interfaz.h
 * @author Jarod Venegas Alpizar (JAROD.VENEGAS@ucr.ac.cr)
 * @brief Interfaz del programa de la conjetura de Goldbach_Pthreads que se
 * encarga de los metodos de impresion y entrada de datos
 * @version 1.0
 * @date 2021-06-27
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "interfaz.h"

/**
 * @brief Crea un vector de primos con una relacion de 1:1
 * @param shared_data strcut shared_data_t
 * @param size el tamaño del vector de primos
 */
void create_prime_vector(shared_data_t* shared_data, int64_t size) {
  shared_data->prime_vector = (int64_t*)calloc(size, sizeof(int64_t));
  // Se crea un vector con el numero mas grande de los numeros ingresados
  shared_data->prime_vector[2] = 1;
  // Por si el numero es impar
  if (even_odd(size) == 0) {
    size = size - 1;
  }

  for (int64_t i = 1; i <= size / 2; i = i + 3) {
    // Aqui se revisan solo los numeros impares que son los posibles primos

    // Revisa el impar mas proximo
    if (is_prime((i * 2) + 1)) {
      shared_data->prime_vector[(i * 2) + 1] = 1;
    }

    // Revisa el siguiente impar del anterior
    if (is_prime((i * 2) + 3)) {
      shared_data->prime_vector[(i * 2) + 3] = 1;
    }

    // Revisa el siguiente impar del anterior
    if (is_prime((i * 2) + 5)) {
      shared_data->prime_vector[(i * 2) + 5] = 1;
    }
  }
}
/**
 * @brief Controla la impresion de todas las sumas de cada numero
 * @param shared_data struct shared_data
 * @return void
 */
void print_goldbach(shared_data_t* shared_data) {
  for (int64_t i = 0; i < shared_data->number_counter; i++) {
    if (shared_data->sums_vector[i].major_limit == 0) {
      fprintf(stdout, "NA");
    } else {
      if (shared_data->sums_vector[i].minor_limit == 0) {
        if (shared_data->sums_vector[i].number < 0) {
          shared_data->sums_vector[i].number =
              shared_data->sums_vector[i].number * -1;
          fprintf(stdout, "-%" PRIu64 ": NA\n",
                  shared_data->sums_vector[i].number);
        } else {
          fprintf(stdout, "%" PRIu64 ": NA\n",
                  shared_data->sums_vector[i].number);
        }
      } else {
        if ((shared_data->sums_vector[i].number % 2) == 0) {
          print_strong(shared_data, i);
        } else {
          print_weak(shared_data, i);
        }
      }
    }
  }
}

/**
 * @brief Controla el ingreso de datos y los coloca en un vector de numeros
 * @param shared_data struct shared_data_t
 * @param big_num el numero mas grande de los ingresados
 * @return int
 */
int input_number(shared_data_t* shared_data, int64_t* big_num) {
  int64_t number = 0;
  int64_t number_temp = 0;
  int size = 20;

  shared_data->numbers_vec = (int64_t*)calloc(size, sizeof(int64_t));

  if (shared_data->numbers_vec) {
    while (fscanf(stdin, "%" SCNu64, &number) == 1) {
      number_temp = number;
      // por si el numero es negativo
      if (number_temp < 0) {
        number_temp = number_temp * -1;
      }
      // para guardar el numero mas grnade ingresado
      if (number_temp > *big_num) {
        *big_num = number_temp;
      }
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

  } else {
    fprintf(stdout, "Could not allocate the memeory.");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

/**
 * @brief Imprime las sumas de la conjetura debil
 * @param shared_data struct shared_data_t
 * @param position para saber la posicion dentro edl vector de Sums
 */
void print_weak(shared_data_t* shared_data, int64_t position) {
  int64_t counter = shared_data->sums_vector[position].sums;
  Sums sums = shared_data->sums_vector[position];
  int64_t num_temp = shared_data->sums_vector[position].number;
  int64_t sums_count = 0;
  int64_t first = 0;
  int64_t second = 0;
  int64_t third = 0;
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
    for (int64_t x = 0; x < shared_data->number_of_threads; x++) {
      for (int64_t y = 0;
           y < shared_data->sums_vector[position].counter_of_sums[x]; y++) {
        if (sums_count != counter - 1) {
          queue_dequeue(&sums.sums_of_thread[x], &first);
          queue_dequeue(&sums.sums_of_thread[x], &second);
          queue_dequeue(&sums.sums_of_thread[x], &third);
          fprintf(stdout,
                  "%" PRIu64
                  " + "
                  "%" PRIu64
                  " + "
                  "%" PRIu64 ", ",
                  first, second, third);
          sums_count = sums_count + 1;
        } else {
          queue_dequeue(&sums.sums_of_thread[x], &first);
          queue_dequeue(&sums.sums_of_thread[x], &second);
          queue_dequeue(&sums.sums_of_thread[x], &third);
          fprintf(stdout,
                  "%" PRIu64
                  " + "
                  "%" PRIu64
                  " + "
                  "%" PRIu64 "\n",
                  first, second, third);
          sums_count = sums_count + 1;
        }
      }
      queue_destroy(&shared_data->sums_vector[position].sums_of_thread[x]);
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
 * @param shared_data struct shared_data_t
 * @param position para saber la posicion dentro edl vector de Sums
 */
void print_strong(shared_data_t* shared_data, int64_t position) {
  int64_t counter = shared_data->sums_vector[position].sums;
  Sums sums = shared_data->sums_vector[position];
  int64_t num_temp = shared_data->sums_vector[position].number;
  int64_t sums_count = 0;
  int64_t first = 0;
  int64_t second = 0;
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
    for (int64_t x = 0; x < shared_data->number_of_threads; x++) {
      for (int64_t y = 0;
           y < shared_data->sums_vector[position].counter_of_sums[x]; y++) {
        if (sums_count != counter - 1) {
          queue_dequeue(&sums.sums_of_thread[x], &first);
          queue_dequeue(&sums.sums_of_thread[x], &second);
          fprintf(stdout,
                  "%" PRIu64
                  " + "
                  "%" PRIu64 ", ",
                  first, second);
          sums_count = sums_count + 1;
        } else {
          queue_dequeue(&sums.sums_of_thread[x], &first);
          queue_dequeue(&sums.sums_of_thread[x], &second);
          fprintf(stdout,
                  "%" PRIu64
                  " + "
                  "%" PRIu64 "\n",
                  first, second);
          sums_count = sums_count + 1;
        }
      }
      queue_destroy(&shared_data->sums_vector[position].sums_of_thread[x]);
    }
  } else {
    fprintf(stdout,
            "%" PRIu64
            ": "
            "%" PRIu64 " sums\n",
            num_temp, counter);
  }
}
