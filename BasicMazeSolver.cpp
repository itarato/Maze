#include <iostream>
#include <vector>
#include <cassert>

#include "MazeGenerator.h"
#include "types.h"
#include "BasicMazeSolver.h"

BasicMazeSolver::BasicMazeSolver(MazeGenerator& _mg) : mg(_mg), history(mg.getH() * mg.getW(), CELL_EMPTY) {
  solve();
}

void BasicMazeSolver::solve() {
  Point p{mg.getStart()};
  Point end{mg.getEnd()};

  history.bitOr(p, CELL_UP << 4);

  while (p != end) {
    uint_t history_parent_mask = history.at2D(p);
    assert(history_parent_mask);
    coord_i_t parent_offset = OFFSET_MAP[history_parent_mask];
    
    for (auto const &dir : OFFSET_MAP) {
      uint_t dir_mask = dir.first;
      coord_i_t offset = dir.second;

      int new_x = p.x + offset.first;
      int new_y = p.y + offset.second;
      // Out of bounds.
      if (new_x < 0 || new_x >= mg.getW() || new_y < 0 || new_y >= mg.getH()) continue;

      uint_t cell_mask = mg.getCell(new_x, new_y);
      // Not a path (but a wall).
      if (!(cell_mask & dir_mask)) continue;
      uint_t history_mask = history.at2D(new_x, new_y);
      // Direction is already discovered.
      if (history_mask & 0xF) continue;

      p = {static_cast<uint_t>(new_x), static_cast<uint_t>(new_y)};
      history.bitOr(p, opposite_direction(dir_mask));

      goto end_of_loop;
    }

    // No new unseen path -> time to backtrack.
    p = {static_cast<uint_t>(p.x + parent_offset.first), static_cast<uint_t>(p.y + parent_offset.second)};

    end_of_loop: ;
  }
}
