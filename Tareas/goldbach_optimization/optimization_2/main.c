/**
 * @file main.c
 * @author Jarod Venegas Alpizar (JAROD.VENEGAS@ucr.ac.cr)
 * @brief Controla el programa(crea los hilos e inicializa el shared_data,
 * imprime las sumas y libera la memoria)
 * @version 1.0
 * @date 2021-05-30
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "main.h"
/**
 * @brief Controla el programa(crea los hilos e inicializa el shared_data,
 * imprime las sumas y libera la memoria)
 * @param argc cantidad de argumentos ingresados
 * @param argv recibe un parametro para definir la cantidad de numeros
 */
int main(int argc, char* argv[]) {
  shared_data_t* shared_data = (shared_data_t*)calloc(1, sizeof(shared_data_t));
  if (shared_data) {
    shared_data->thread_position = 0;
    shared_data->number_counter = 0;
    shared_data->number_of_threads = sysconf(_SC_NPROCESSORS_ONLN);
    if (argc == 2) {
      if (sscanf(argv[1], "%zu", &shared_data->number_of_threads) < 1 ||
          shared_data->number_of_threads == 0) {
        fprintf(stderr, "error: invalid thread count\n");
      }
    }
    input_number(shared_data);
    shared_data->sums_vector =
        (Sums*)calloc(shared_data->number_counter, sizeof(Sums));
    complete_structure(shared_data);
    create_threads(shared_data);
    // Esto es por que se ocupa sumar la cantidad de sumas que hizo cada hilo en
    // una sola variable
    for (int64_t x = 0; x < shared_data->number_counter; x++) {
      for (int64_t y = 0; y < shared_data->number_of_threads; y++) {
        shared_data->sums_vector[x].sums =
            shared_data->sums_vector[x].sums +
            shared_data->sums_vector[x].counter_of_sums[y];
      }
    }
    print_goldbach(shared_data);
    // Aqui se hace toda la liberacion de memoria
    for (int i = 0; i < shared_data->number_counter; i++) {
      free(shared_data->sums_vector[i].counter_of_sums);
      free(shared_data->sums_vector[i].sums_of_thread);
    }
    free(shared_data->sums_vector);
    free(shared_data->numbers_vec);
    free(shared_data);
  }
  return 0;
}
