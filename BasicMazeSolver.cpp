#include <iostream>
#include <vector>

#include "MazeGenerator.h"
#include "types.h"
#include "BasicMazeSolver.h"

BasicMazeSolver::BasicMazeSolver(MazeGenerator& _mg) : mg(_mg), history(mg.getH() * mg.getW(), CELL_EMPTY) {
  Point p{mg.getStart()};
  Point end{mg.getEnd()};

  history.bitOr(p, CELL_UP << 4);

  while (p != end) {
    break;
  }
}

void BasicMazeSolver::solve() {

}
