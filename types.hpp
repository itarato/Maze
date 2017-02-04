#pragma once

#include <utility>
#include <iostream>
#include <vector>

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
    default: 
      std::cerr << "Invalid direction mask:" << dir << std::endl;
      exit(1);
  }
}

struct Point {
  uint x;
  uint y;
  Point operator+(const Point& rhs) const {
    return Point{x + rhs.x, y + rhs.y};
  }
};

template<class T, class Allocator = std::allocator<T>>
class Vector2D : public std::vector<T, Allocator> {
private:
  size_t w;
  size_t h;
public:
  Vector2D(size_t s, T def) : std::vector<T, Allocator>(s, def) {};

  void setW(size_t _w) { w = _w; };
  void setH(size_t _h) { h = _h; };
  const T& at2D(size_t x, size_t y) { return std::vector<T, Allocator>::at(y * w + x); };
};
