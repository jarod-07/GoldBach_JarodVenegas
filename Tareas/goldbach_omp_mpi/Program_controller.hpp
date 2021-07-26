/**
 * @file Program_controller.hpp
 * @author Jarod Venegas Alpizar (JAROD.VENEGAS@ucr.ac.cr)
 * @brief COntrola el programa y es el main del MPI
 * @version 1.0
 * @date 2021-07-27
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef PROGRAM_CONTROLLER_
#define PROGRAM_CONTROLLER_

#include <vector>

#include "Goldbach_controller.hpp"

class Program_controller {
 public:
  Program_controller();
  ~Program_controller();
  void run(int argc, char* argv[]);

 private:
  Goldbach_controller goldbach_controller;
  Interfaz interfaz;
  int get_num_threads(int argc, char* argv[]);
};
#endif
