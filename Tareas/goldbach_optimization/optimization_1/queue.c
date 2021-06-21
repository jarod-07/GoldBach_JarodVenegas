// Copyright 2021 Jeisson Hidalgo-Cespedes <jeisson.hidalgo@ucr.ac.cr> CC-BY-4
// Implements a thread-safe queue

#include "queue.h"

#include <assert.h>
#include <stdlib.h>

void queue_remove_first_unsafe(queue_t* queue);
bool queue_is_empty_unsafe(const queue_t* queue);

/**
 * @brief Inicializa la cola
 * @param queue struct queue_t
 * @return int inicializa el semaforo
 */
int queue_init(queue_t* queue) {
    assert(queue);
    queue->head = NULL;
    queue->tail = NULL;
    return pthread_mutex_init(&queue->can_access_queue, NULL);
}

/**
 * @brief Destruye la cola
 * @param queue struct queue_t
 * @return int destruye el semaforo
 */
int queue_destroy(queue_t* queue) {
    queue_clear(queue);
    return pthread_mutex_destroy(&queue->can_access_queue);
}

/**
 * @brief Determina si la cola esta vacia o no
 * @param queue struct queue_t
 * @return bool dependiendo si esta vacio o no
 */
bool queue_is_empty_unsafe(const queue_t* queue) {
    assert(queue);
    return queue->head == NULL;
}

/**
 * @brief Determina si la cola esta vacia o no (controla los hilos con un
 * semaforo)
 * @param queue struct queue_t
 * @return bool dependiendo si esta vacio o no
 */
bool queue_is_empty(queue_t* queue) {
    assert(queue);
    pthread_mutex_lock(&queue->can_access_queue);
    bool result = queue_is_empty_unsafe(queue);
    pthread_mutex_unlock(&queue->can_access_queue);
    return result;
}

/**
 * @brief Coloca un numero en el tope de la cola (controla los hilos con un
 * semaforo)
 * @param queue struct queue_t
 * @param data int de 64 bits
 * @return int de 64 bits
 */
int64_t queue_enqueue(queue_t* queue, const int64_t data) {
    assert(queue);
    int error = EXIT_SUCCESS;

    queue_node_t* new_node = (queue_node_t*)calloc(1, sizeof(queue_node_t));

    if (new_node) {
        new_node->data = data;

        pthread_mutex_lock(&queue->can_access_queue);
        if (queue->tail) {
            queue->tail = queue->tail->next = new_node;
        } else {
            queue->head = queue->tail = new_node;
        }
        pthread_mutex_unlock(&queue->can_access_queue);
    } else {
        error = EXIT_FAILURE;
    }

    return error;
}

/**
 * @brief Saca el valor del tope de la cola (controla los hilos con un semaforo)
 * @param queue struct queue_t
 * @param data int de 64 bits
 * @return int de 64 bits
 */
int64_t queue_dequeue(queue_t* queue, int64_t* data) {
    assert(queue);
    int error = 0;

    pthread_mutex_lock(&queue->can_access_queue);
    if (!queue_is_empty_unsafe(queue)) {
        if (data) {
            *data = queue->head->data;
        }
        queue_remove_first_unsafe(queue);
    } else {
        error = EXIT_FAILURE;
    }
    pthread_mutex_unlock(&queue->can_access_queue);

    return error;
}

/**
 * @brief Quita el numero del tope de la cola(no tiene semaforo)
 * @param queue struct queue_t
 * @return void
 */
void queue_remove_first_unsafe(queue_t* queue) {
    assert(queue);
    assert(!queue_is_empty_unsafe(queue));
    queue_node_t* node = queue->head;
    queue->head = queue->head->next;
    free(node);
    if (queue->head == NULL) {
        queue->tail = NULL;
    }
}

/**
 * @brief Limpia la cola
 * @param queue struct queue_t
 * @return void
 */
void queue_clear(queue_t* queue) {
    assert(queue);
    pthread_mutex_lock(&queue->can_access_queue);
    while (!queue_is_empty_unsafe(queue)) {
        queue_remove_first_unsafe(queue);
    }
    pthread_mutex_unlock(&queue->can_access_queue);
}
