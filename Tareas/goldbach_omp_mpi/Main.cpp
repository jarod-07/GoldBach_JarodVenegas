/**
 * @file Main.cpp
 * @author Jarod Venegas Alpizar (JAROD.VENEGAS@ucr.ac.cr)
 * @brief Main del programa
 * @version 1.0
 * @date 2021-07-27
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "Program_controller.hpp"

int main(int argc, char* argv[]) {
  Program_controller controller;
  controller.run(argc, argv);

  return 0;
}
