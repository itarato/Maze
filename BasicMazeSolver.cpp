#include <iostream>
#include <vector>
#include <cassert>
#include <SDL2/SDL.h>

#include "MazeGenerator.h"
#include "types.h"
#include "BasicMazeSolver.h"
#include "2DMazePrinterSDL.h"

BasicMazeSolver::BasicMazeSolver(MazeGenerator& _mg) : mg(_mg), history(mg.getW(), mg.getH(), CELL_EMPTY) {
  solve();
}

void BasicMazeSolver::solve() {
  Point p{mg.getStart()};
  Point end{mg.getEnd()};

  history.bitOr(p, CELL_UP);

  while (p != end) {
    uint_t history_parent_mask = history.at2D(p);
    assert(history_parent_mask);
    coord_i_t parent_offset = OFFSET_MAP[history_parent_mask];

    for (auto const &dir : OFFSET_MAP) {
      uint_t dir_mask = dir.first;
      coord_i_t offset = dir.second;

      uint_t cell_mask = mg.getCell(p.x, p.y);
      // Not a path (but a wall).
      if (!(cell_mask & dir_mask)) continue;

      int new_x = p.x + offset.first;
      int new_y = p.y + offset.second;
      // Out of bounds.
      if (new_x < 0 || new_x >= mg.getW() || new_y < 0 || new_y >= mg.getH()) continue;

      uint_t history_mask = history.at2D(new_x, new_y);
      // Direction is already discovered.
      if (history_mask & 0xF) continue;

      // Green light to discovery. Set parent and go.
      p = {static_cast<uint_t>(new_x), static_cast<uint_t>(new_y)};
      history.bitOr(p, opposite_direction(dir_mask));

      goto end_of_loop;
    }

    // No new unseen path -> time to backtrack.
    p = {static_cast<uint_t>(p.x + parent_offset.first), static_cast<uint_t>(p.y + parent_offset.second)};

    end_of_loop: ;
  }

  std::cout << "Solved\n";
}

void BasicMazeSolver::draw(DrawEngine *engine) {
  SDL_SetRenderDrawColor(engine->renderer, 255, 100, 100, 255);
  for (int y = 0; y < mg.getH(); y++) {
    for (int x = 0; x < mg.getW(); x++) {
      uint_t h = history.at2D(x, y);
      if (h > 0) {
        int cx = int(((x + 1.375) * engine->pixelSize * 4));
        int cy = int(((y + 1.375) * engine->pixelSize * 4));
        SDL_Rect mark{cx, cy, int(engine->pixelSize), int(engine->pixelSize)};
        SDL_RenderFillRect(engine->renderer, &mark);
      }
    }
  }
}
