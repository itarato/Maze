#pragma once

#include <utility>

typedef unsigned int uint;

typedef std::pair<uint, uint> coord_t;

const uint CELL_EMPTY = 0x0;
const uint CELL_UP    = 0x1;
const uint CELL_RIGHT = 0x2;
const uint CELL_DOWN  = 0x4;
const uint CELL_LEFT  = 0x8;

uint opposite_dir(uint dir) {
  switch (dir) {
    case CELL_UP: return CELL_DOWN;
    case CELL_DOWN: return CELL_UP;
    case CELL_LEFT: return CELL_RIGHT;
    case CELL_RIGHT: return CELL_LEFT;
    default: exit(1);
  }
}
