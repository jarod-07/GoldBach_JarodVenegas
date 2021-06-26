/**
 * @file queue.c
 * @author Jeisson Hidalgo-Cespedes <jeisson.hidalgo@ucr.ac.cr> CC-BY-4
 * @brief Simulates a producer and a consumer that share a bounded buffer
 * @version 1.0
 * @date 2021
 *
 * @copyright Copyright (c) 2021
 *
 */
// Copyright 2021 Jeisson Hidalgo-Cespedes <jeisson.hidalgo@ucr.ac.cr> CC-BY-4
// Simulates a producer and a consumer that share a bounded buffer
#ifndef QUEUE_H
#define QUEUE_H

#include <assert.h>
#include <inttypes.h>
#include <pthread.h>
#include <stdbool.h>

/**
 * @brief Estructura utilizada para almacenar los datos del nodo
 *
 */
typedef struct queue_node {
  int64_t data;
  struct queue_node* next;
} queue_node_t;

/**
 * @brief Estructura utilizada para almacenar los datos de la cola
 *
 */
typedef struct {
  pthread_mutex_t can_access_queue;
  queue_node_t* head;
  queue_node_t* tail;
} queue_t;

/**
 *  This subroutine is NOT thread-safe
 */
int queue_init(queue_t* queue);

int queue_destroy(queue_t* queue);

bool queue_is_empty(queue_t* queue);
int64_t queue_enqueue(queue_t* queue, const int64_t data);
int64_t queue_dequeue(queue_t* queue, int64_t* data);
void queue_clear(queue_t* queue);

#endif  // QUEUE_H
