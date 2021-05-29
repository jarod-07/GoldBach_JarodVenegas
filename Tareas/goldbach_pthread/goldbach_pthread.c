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
    private_data->shared_data->sums_vector[private_data->position]
        ->major_limit = 0;
    private_data->shared_data->sums_vector[private_data->position]
        ->minor_limit = 1;
}

/**
 * @brief metodo necesario para asignar los valores adecuados dentro de la
 * estructura Sums en caso de que el numero sea un valor entre [-5 , 5]
 * @param private_data struct que contiene los datos privados del hilo
 * @return void
 */
void minor_limit_def(private_data_t* private_data) {
    Sums* invalid_cases = (Sums*)calloc(1, sizeof(Sums));
    private_data->shared_data->sums_vector[private_data->position] =
        invalid_cases;
    private_data->shared_data->sums_vector[private_data->position]
        ->major_limit = 1;
    private_data->shared_data->sums_vector[private_data->position]
        ->minor_limit = 0;
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
    Sums* even_sums = strong_conjecture(number, &sums_counter,
                                        private_data->shared_data->output);

    even_sums->sums = sums_counter;
    private_data->shared_data->sums_vector[private_data->position] = even_sums;
    private_data->shared_data->sums_vector[private_data->position]->number =
        number;
    private_data->shared_data->sums_vector[private_data->position]
        ->major_limit = 1;
    private_data->shared_data->sums_vector[private_data->position]
        ->minor_limit = 1;
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
    Sums* odd_sums = weak_conjecture(number, &sums_counter,
                                     private_data->shared_data->output);
    odd_sums->sums = sums_counter;
    private_data->shared_data->sums_vector[private_data->position] = odd_sums;
    private_data->shared_data->sums_vector[private_data->position]->number =
        number;
    private_data->shared_data->sums_vector[private_data->position]
        ->major_limit = 1;
    private_data->shared_data->sums_vector[private_data->position]
        ->minor_limit = 1;
}
// fin de metodos privados

/**
 * @brief Controla la entrada de datos y aplica la conjetura de goldbach
 * @param private_data struct que contiene los datos privados del hilo
 * @return void
 */
void goldbach(private_data_t* private_data) {
    int64_t number = private_data->goldbach_number;

    if (number > ((int64_t)pow(2, 63) - 1) ||
        number < -((int64_t)pow(2, 63) - 1)) {
        major_limit_def(private_data);
    } else {
        if ((number <= 5 && number >= -5)) {
            minor_limit_def(private_data);
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
 * @brief Funcion para controlar los hilos
 * @param data void que recibe un private data
 * @return void
 */
void* run_threads(void* data) {
    private_data_t* private_data = (private_data_t*)data;
    shared_data_t* shared_data = private_data->shared_data;
    while (!(queue_is_empty(shared_data->numbers_queue))) {
        sem_wait(&shared_data->sem_get_position);
        queue_dequeue(
            shared_data->numbers_queue,
            &private_data->goldbach_number);  // LA COLA ES THREAD SAFE
                                              
        private_data->position = shared_data->thread_position;
        shared_data->thread_position++;
        sem_post(&shared_data->sem_get_position);
        goldbach(private_data);
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
        for (int64_t index = 0; index < shared_data->number_of_threads;
             ++index) {
            private_data[index].shared_data = shared_data;
            sem_init(&shared_data->sem_get_position, /*pshared*/ 0,
                     /*value*/ 1);
            if (pthread_create(&threads[index], /*attr*/ NULL, run_threads,
                               &private_data[index]) == EXIT_SUCCESS) {
            } else {
                fprintf(stderr, "error: could not create thread %zu\n", index);
                error = 21;
                break;
            }
        }
        for (int64_t index = 0; index < shared_data->number_of_threads;
             ++index) {
            pthread_join(threads[index], /*value_ptr*/ NULL);
            sem_destroy(&shared_data->sem_get_position);
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
