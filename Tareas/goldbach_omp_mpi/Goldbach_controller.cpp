/**
 * @file Goldbach_controller.cpp
 * @author Jarod Venegas Alpizar (JAROD.VENEGAS@ucr.ac.cr)
 * @brief Controla la conjetura del goldbach y la parte del MPI
 * @version 1.0
 * @date 2021-07-27
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "Goldbach_controller.hpp"

/**
 * @brief Construye un nuevo objeto Goldbach_controller
 *
 */
Goldbach_controller::Goldbach_controller() {}

/**
 * @brief Destruye un objeto Goldbach_controller
 *
 */
Goldbach_controller::~Goldbach_controller() {}

/**
 * @brief Hace un set de la cantidad de hilos ingresado por el usuario
 *
 * @param num_threads
 */
void Goldbach_controller::set_threads(int num_threads) {
  this->number_of_threads = num_threads;
}

/**
 * @brief Verifica si el numero ingresado es valido
 *
 * @param number
 * @return true
 * @return false
 */
bool Goldbach_controller::is_valid(int64_t number) {
  int64_t limite = (int64_t)pow(2, 63) - 1;
  if ((number < (limite * -1)) || (number > limite) ||
      ((number <= 5) && (number >= -5))) {
    return false;
  }
  return true;
}
/**
 * @brief Calcula donde empiezan las iteraciones de un hilo
 * @param process_rank id del process
 * @param number_of_process cantidad de procesos
 * @param iterations cantidad de iteraciones
 * @param start donde empieza el proceso
 * @return int64_t
 */
int64_t Goldbach_controller::where_to_begin(int64_t process_rank,
                                            int64_t number_of_process,
                                            int64_t iterations, int64_t start) {
  int64_t normal = process_rank * ((iterations - start) / number_of_process);
  int64_t remainder = 0;
  if (process_rank < ((iterations - start) % number_of_process)) {
    remainder = process_rank;
  } else {
    remainder = (iterations - start) % number_of_process;
  }
  int64_t begin = start + normal + remainder;
  return begin;
}

/**
 * @brief Calcula donde terminan las iteraciones de un hilo
 * @param process_rank id del process
 * @param number_of_process cantidad de procesos
 * @param iterations cantidad de iteraciones
 * @param start donde empieza el proceso
 * @return int64_t
 */
int64_t Goldbach_controller::where_to_end(int64_t process_rank,
                                          int64_t number_of_process,
                                          int64_t iterations, int64_t start) {
  int64_t next_rank = process_rank + 1;
  return where_to_begin(next_rank, number_of_process, iterations, start);
}
/**
 * @brief Calcula las sumas enviadas por el usuario. Los procesos se reparten la
 * cantidad de numeros.
 *
 * @param goldbach_numbers vector de numeros
 * @param prime_vector vector de primos
 * @param counter cantidad de numeros
 * @param my_rank id de cada proceso
 * @param number_of_process cantidad de procesos
 * @return std::string
 */
std::string Goldbach_controller::goldbach_conjecture(
    std::vector<int64_t> goldbach_numbers, std::vector<int64_t> prime_vector,
    int64_t counter, int my_rank, int number_of_process) {
  // Se crea el vector de la data de cada numero
  Data_of_number* data_of_number =
      (Data_of_number*)calloc(counter, sizeof(Data_of_number));

  // Para luego imprimir las sumas
  std::string output = "";

  // Inicializar el vector de las sumas hechas por cada hilo
  for (int i = 0; i < counter; i++) {
    data_of_number[i].sums_by_threads =
        (Thread_sums*)calloc(number_of_threads, sizeof(Thread_sums));
  }

  // Aqui los procesos se dividen equitativamente la cantidad de numeros
  int64_t begin = where_to_begin(my_rank, number_of_process, counter, 0);
  int64_t end = where_to_end(my_rank, number_of_process, counter, 0);

  // Goldbach
  for (int64_t x = begin; x < end; x++) {
    if (is_valid(goldbach_numbers[x])) {
      data_of_number[x].number = goldbach_numbers[x];

      if (goldbach.even_odd(goldbach_numbers[x])) {
        goldbach.strong_conjecture(data_of_number[x], prime_vector,
                                   number_of_threads);
        output += interfaz.toString_even(data_of_number[x], number_of_threads);
      } else {
        goldbach.weak_conjecture(data_of_number[x], prime_vector,
                                 number_of_threads);
        output += interfaz.toString_odd(data_of_number[x], number_of_threads);
      }
    } else {
      output += std::to_string(goldbach_numbers[x]) + ": ";
      output += "NA\n";
    }
  }
  free(data_of_number);
  return output;
}
/**
 * @brief Crea un vector de primos. Se mapean los numeros con una relacion de
 * 1:1, donde 1 significa que es primo y 0 que no es primo
 *
 * @param prime_vector vector de primos
 * @param size tamaño del vector
 */
void Goldbach_controller::create_prime_vector(
    std::vector<int64_t>& prime_vector, int64_t size) {
  prime_vector.resize(size);
  // Se crea un vector con el numero mas grande de los numeros ingresados
  prime_vector[2] = 1;
  // Por si el numero es impar
  if (goldbach.even_odd(size) == 0) {
    size = size - 1;
  }

  for (int64_t i = 1; i <= size / 2; i = i + 3) {
    // Aqui se revisan solo los numeros impares que son los posibles primos

    // Revisa el impar mas proximo
    if (goldbach.is_prime((i * 2) + 1)) {
      prime_vector[(i * 2) + 1] = 1;
    }

    // Revisa el siguiente impar del anterior
    if (goldbach.is_prime((i * 2) + 3)) {
      prime_vector[(i * 2) + 3] = 1;
    }

    // Revisa el siguiente impar del anterior
    if (goldbach.is_prime((i * 2) + 5)) {
      prime_vector[(i * 2) + 5] = 1;
    }
  }
}
