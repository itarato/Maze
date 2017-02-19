#include <iostream>
#include <string>

#include "MazeGenerator.h"
#include "AsciiMazePrinter.h"
#include "2DMazePrinterSDL.h"
#include "BasicMazeSolver.h"

int main(int argc, char* argv[]) {
  if (argc < 3) {
    std::cerr << "Missing arguments. Usage: ./bin <WIDTH> <HEIGHT>" << std::endl;
    exit(1);
  }

  MazeGenerator mg{static_cast<size_t>(std::stoi(argv[1])), static_cast<size_t>(std::stoi(argv[2]))};

  //print_maze__ascii(mg);
  DrawEngine de{mg, 4};

  BasicMazeSolver bms{mg};
  bms.solve();  

  return 0;
}
