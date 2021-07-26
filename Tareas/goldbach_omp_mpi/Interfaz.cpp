/**
 * @file Interfaz.cpp
 * @author Jarod Venegas Alpizar (JAROD.VENEGAS@ucr.ac.cr)
 * @brief Maneja todo lo que hace interaccion con el usuario
 * @version 1.0
 * @date 2021-07-27
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "Interfaz.hpp"

/**
 * @brief Construye un nuevo objeto Interfaz
 *
 */
Interfaz::Interfaz(){};

/**
 * @brief Destruye un objeto Interfaz
 *
 */
Interfaz::~Interfaz(){};

/**
 * @brief Almacena los numeros ingresados por el usuario dentro de un vector de
 * numeros
 *
 * @param vector_of_numbers
 * @param counter_of_numbers
 * @param size_of_prime tamaño del vector de primos
 */
void Interfaz::input_numbers(std::vector<int64_t> &vector_of_numbers,
                             int64_t &counter_of_numbers,
                             int64_t &size_of_prime) {
  int64_t size = 10;
  int64_t number = 0;
  int64_t number_temp = 0;
  vector_of_numbers.resize(size);
  while (fscanf(stdin, "%" SCNu64, &number) == 1) {
    number_temp = number;
    // por si el numero es negativo
    if (number_temp < 0) {
      number_temp = number_temp * -1;
    }
    // para guardar el numero mas grande ingresado
    if (number_temp > size_of_prime) {
      size_of_prime = number_temp;
    }
    if (counter_of_numbers == size) {
      size = size * 2;
      vector_of_numbers.resize(size);
    }
    vector_of_numbers[counter_of_numbers] = number;
    counter_of_numbers++;
  }
}

/**
 * @brief Crea una hilera con las sumas de los numeros pares ingresados
 *
 * @param data struct Data
 * @param threads cantidad de hilos
 * @return std::string
 */
std::string Interfaz::toString_even(Data_of_number data, int threads) {
  std::string output = std::to_string(data.number) + ": ";
  int64_t total_sums = 0;
  // Para saber la cantidad de sumas totales del numero
  for (int i = 0; i < threads; i++) {
    total_sums += data.sums_by_threads[i].number_of_sums;
  }
  // Este es el caso positivo
  output += std::to_string(total_sums) + " sums";
  // Caso donde el numero es negativo (hay que agregar las sumas)
  if (data.number < 0) {
    output += ": ";
    for (int j = 0; j < threads; j++) {
      for (int i = 0; i < data.sums_by_threads[j].number_of_sums; i++) {
        output += std::to_string(data.sums_by_threads[j].sums[i].first) +
                  " + " +
                  std::to_string(data.sums_by_threads[j].sums[i].second);
        output += ", ";
      }
    }
    // Esto es para quitarle el ultimo espacio y la ultima coma
    output.pop_back();
    output.pop_back();

    // Cambio de linea por el caso negativo
    output += "\n";
  } else {
    // Cambio de linea por el caso positivo
    output += "\n";
  }

  // Se libera toda la memoria de las estructuras
  for (int i = 0; i < threads; i++) {
    free(data.sums_by_threads[i].sums);
  }
  free(data.sums_by_threads);

  return output;
}

/**
 * @brief Crea una hilera con las sumas de los numeros impares ingresados
 *
 * @param data struct Data
 * @param threads cantidad de hilos
 * @return std::string
 */
std::string Interfaz::toString_odd(Data_of_number data, int threads) {
  std::string output = std::to_string(data.number) + ": ";
  int64_t total_sums = 0;

  // Para saber la cantidad de sumas totales del numero
  for (int i = 0; i < threads; i++) {
    total_sums += data.sums_by_threads[i].number_of_sums;
  }

  // Este es el caso positivo
  output += std::to_string(total_sums) + " sums";
  // Caso donde el numero es negativo (hay que agregar las sumas)
  if (data.number < 0) {
    output += ": ";
    for (int i = 0; i < threads; i++) {
      for (int j = 0; j < data.sums_by_threads[i].number_of_sums; j++) {
        output += std::to_string(data.sums_by_threads[i].sums[j].first) +
                  " + " +
                  std::to_string(data.sums_by_threads[i].sums[j].second);
        output += " + " + std::to_string(data.sums_by_threads[i].sums[j].third);
        output += ", ";
      }
    }
    // Esto es para quitarle el ultimo espacio y la ultima coma
    output.pop_back();
    output.pop_back();

    // Cambio de linea por el caso negativo
    output += "\n";
  } else {
    // Cambio de linea por el caso positivo
    output += "\n";
  }

  // Se libera toda la memoria de las estructuras
  for (int i = 0; i < threads; i++) {
    free(data.sums_by_threads[i].sums);
  }
  free(data.sums_by_threads);

  return output;
}
