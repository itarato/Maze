#include <iostream>
#include <string>
#include "MazeGenerator.h"
#include "AsciiMazePrinter.h"

void print_maze__ascii(MazeGenerator& mg) {
  std::string w[16] = {" ", "║", "═", "╚", "║", "║", "╔", "╠", "═", "╝", "═", "╩", "╗", "╣", "╦", "╬"};

  for (int y = 0; y < mg.getH(); y++) {
    for (int x = 0; x < mg.getW(); x++) {
      std::cout << w[mg.getCell(x, y) & 15];
    }
    std::cout << std::endl;
  }
}
