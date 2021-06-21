#include "main.h"
/**
 * @brief Controla el programa(crea los hilos e inicializa el shared_data,
 * imprime las sumas y libera la memoria)
 * @param argc cantidad de argumentos ingresados
 * @param argv recibe un parametro para definir la cantidad de numeros
 */
int main(int argc, char* argv[]) {
    shared_data_t* shared_data =
        (shared_data_t*)calloc(1, sizeof(shared_data_t));
    if (shared_data) {
        queue_init(&shared_data->numbers_queue);
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
            (Sums**)calloc(shared_data->number_counter, sizeof(Sums*));
        create_threads(shared_data);
        print_goldbach(shared_data);
        for (int i = 0; i < shared_data->number_counter; i++) {
            free(shared_data->sums_vector[i]);
        }
        free(shared_data->sums_vector);
        queue_destroy(&shared_data->numbers_queue);
        free(shared_data);
    }
    return 0;
}
