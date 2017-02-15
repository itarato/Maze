#include <iostream>
#include <vector>

#include "MazeGenerator.h"
#include "types.h"

/**
 * This solver is pretending to only see the path it had walked (with memory).
 */
class BasicMazeSolver {
private:
  MazeGenerator& mg;
  Vector2D<uint_t> history;

public:
  BasicMazeSolver(MazeGenerator&);
  void solve();
};

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
