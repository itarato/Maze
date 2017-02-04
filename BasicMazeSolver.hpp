#include <iostream>
#include <vector>

#include "MazeGenerator.h"
#include "types.hpp"

class BasicMazeSolver {
private:
  MazeGenerator& mg;
  Vector2D<uint> history;

public:
  BasicMazeSolver(MazeGenerator&);
  void solve();
};

BasicMazeSolver::BasicMazeSolver(MazeGenerator& _mg) : mg(_mg), history(mg.getH() * mg.getW(), CELL_EMPTY) {
  
}

void BasicMazeSolver::solve() {

}
