#pragma once

class MazeGenerator;
class DrawEngine;

#include "types.h"
#include "Drawer.h"

/**
 * This solver is pretending to only see the path it had walked (with memory).
 */
class BasicMazeSolver : public Drawer {
private:
  MazeGenerator& mg;
  // History keeps track of the parents in a matrix.
  // Each crossection will be discovered each time, and only parent info is saved
  // on the low 4 bits. UP bit means the parent is the cell to UP (y-1).
  Vector2D<uint_t> history;

public:
  BasicMazeSolver(MazeGenerator&);
  void solve();
  virtual void draw(DrawEngine *);
};
