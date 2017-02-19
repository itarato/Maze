#pragma once

class MazeGenerator;

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
