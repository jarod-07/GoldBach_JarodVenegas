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