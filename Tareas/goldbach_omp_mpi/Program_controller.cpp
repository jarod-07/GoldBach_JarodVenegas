#include "Program_controller.hpp"

#include <inttypes.h>
#include <mpi.h>

#include <iostream>
Program_controller::Program_controller() {}
Program_controller::~Program_controller() {}

int Program_controller::get_num_threads(int argc, char *argv[]) {
  int threads_num = sysconf(_SC_NPROCESSORS_ONLN);
  if (argc == 1) {
    threads_num = atoi(argv[1]);
  }
  return threads_num;
}

void Program_controller::run(int argc, char *argv[]) {
  // Declaraciones de MPI
  MPI_Status status;
  MPI_Init(&argc, &argv);
  int rank = -1;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  int process_count = -1;
  MPI_Comm_size(MPI_COMM_WORLD, &process_count);

  // Declaraciones para el goldbach
  int64_t size_of_prime = 0;
  int64_t counter_of_numbers = 0;
  std::vector<int64_t> prime_vector;
  std::vector<int64_t> numbers_to_goldbach;

  // Solo el proceso 0 hace esta parte
  if (rank == 0) {
    interfaz.input_numbers(numbers_to_goldbach, counter_of_numbers,
                           size_of_prime);
    goldbach_controller.create_prime_vector(prime_vector, size_of_prime);
  }
  // El proceso 0 le envia al resto de procesos el vector de numeros
  MPI_Bcast(&counter_of_numbers, 1, MPI_INT64_T, 0, MPI_COMM_WORLD);
  if (rank != 0) {
    numbers_to_goldbach.resize(counter_of_numbers);
  }
  MPI_Bcast(&numbers_to_goldbach[0], counter_of_numbers, MPI_INT64_T, 0,
            MPI_COMM_WORLD);

  
  // El proceso 0 le envia al resto de procesos el vector de primos
  MPI_Bcast(&size_of_prime, 1, MPI_INT64_T, 0, MPI_COMM_WORLD);
    if (rank != 0) {
    prime_vector.resize(size_of_prime);
  }
  MPI_Bcast(&prime_vector[0], size_of_prime, MPI_INT64_T, 0, MPI_COMM_WORLD);

  // Empieza la manipulacion de la conjetura de goldbach

  // Se establece la cantidad de hilos para repartirse las sumas
  goldbach_controller.set_threads(get_num_threads(argc, argv));

  // Conjetura de goldbach
  std::string output = goldbach_controller.goldbach_conjecture(
      numbers_to_goldbach, prime_vector, counter_of_numbers, rank,
      process_count);

  // Para que los procesos impriman en orden (metodo visto en clase). Hay
  // comunicaion del proceso 0 con el resto de procesos y viceversa
  int you_can_print = 0;
  if (rank == 0) {
    std::cout << output;
    for (int i = 1; i < process_count; i++) {
      MPI_Send(&you_can_print, 1, MPI_INT, i, 2020, MPI_COMM_WORLD);
      MPI_Recv(&you_can_print, 1, MPI_INT, i, 2020, MPI_COMM_WORLD, &status);
    }
  } else {
    MPI_Recv(&you_can_print, 1, MPI_INT, 0, 2020, MPI_COMM_WORLD, &status);
    std::cout << output;
    MPI_Send(&you_can_print, 1, MPI_INT, 0, 2020, MPI_COMM_WORLD);
  }
  MPI_Finalize();
}
