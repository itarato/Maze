#pragma once

#include <iostream>
#include "MazeGenerator.h"
#include <string>

void print_maze__ascii(MazeGenerator& mg) {
  std::string w[16] = {" ", "║", "═", "╚", "║", "║", "╔", "╠", "═", "╝", "═", "╩", "╗", "╣", "╦", "╬"};

  for (int y = 0; y < mg.getH(); y++) {
    for (int x = 0; x < mg.getW(); x++) {
      std::cout << w[mg.getCell(x, y) & 0b1111];
    }
    std::cout << std::endl;
  }
}
