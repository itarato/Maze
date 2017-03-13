#include <iostream>
#include <string>
#include <unistd.h>

#include "MazeGenerator.h"
#include "AsciiMazePrinter.h"
#include "2DMazePrinterSDL.h"
#include "BasicMazeSolver.h"

int main(int argc, char* argv[]) {
  if (argc < 3) {
    std::cerr << "Missing arguments. Usage: ./bin <WIDTH> <HEIGHT>" << std::endl;
    exit(1);
  }

  size_t w = static_cast<size_t>(std::stoi(argv[1]));
  size_t h = static_cast<size_t>(std::stoi(argv[2]));

  int opt;
  bool flagDrawAsciiMap = false;
  bool flagDrawGraphicalMap = false;
  while ((opt = getopt(argc, argv, "ag")) != -1) {
    switch (opt) {
      case 'a':
        flagDrawAsciiMap = true;
        break;

      case 'g':
        flagDrawGraphicalMap = true;
        break;
    }
  }

  MazeGenerator mg{w, h};

  if (flagDrawAsciiMap) print_maze__ascii(mg);
  if (flagDrawGraphicalMap) {
    DrawEngine de{mg, 8};

    BasicMazeSolver bms{mg};
    de.add_drawer(&bms);

    de.run();
  }

  return 0;
}
