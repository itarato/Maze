#include <iostream>
#include <string>

#include "MazeGenerator.cpp"
#include "AsciiMazePrinter.hpp"
#include "2DMazePrinterSDL.hpp"

int main(int argc, char* argv[]) {
  if (argc < 3) {
    std::cerr << "Missing arguments. Usage: ./bin <WIDTH> <HEIGHT>" << std::endl;
    exit(1);
  }

  MazeGenerator mg{static_cast<size_t>(std::stoi(argv[1])), static_cast<size_t>(std::stoi(argv[2]))};

  // print_maze__ascii(mg);
  DrawEngine de{mg, 8};

  return 0;
}
