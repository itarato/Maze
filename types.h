#pragma once

#include <utility>
#include <iostream>
#include <vector>
#include <map>

using uint_t = unsigned int;
using coord_t = std::pair<uint_t, uint_t>;
using coord_i_t = std::pair<int, int>;

const uint_t CELL_EMPTY = 0x0;
const uint_t CELL_UP    = 0x1;
const uint_t CELL_RIGHT = 0x2;
const uint_t CELL_DOWN  = 0x4;
const uint_t CELL_LEFT  = 0x8;

static std::map<uint_t, coord_i_t> OFFSET_MAP = {
  {CELL_LEFT, {-1, 0}}, 
  {CELL_RIGHT, {1, 0}},
  {CELL_UP, {0, -1}},
  {CELL_DOWN, {0, 1}},
};

uint_t opposite_direction(uint_t);

struct Point {
  uint_t x;
  uint_t y;

  Point (uint_t _x, uint_t _y) : x(_x), y(_y) {};
  Point (coord_t c) : Point(c.first, c.second) {};

  Point operator+(const Point& rhs) const { return Point{x + rhs.x, y + rhs.y}; }
  bool operator==(const Point& rhs) const { return x == rhs.x && y == rhs.y; }
  bool operator!=(const Point& rhs) const { return !(*this == rhs); }
};

template<class T, class Allocator = std::allocator<T>>
class Vector2D : public std::vector<T, Allocator> {
private:
  size_t w;
  size_t h;
public:
  Vector2D(size_t _w, size_t _h, T def) : std::vector<T, Allocator>(_w * _h, def), w(_w), h(_h) {};
  Vector2D(size_t s, T def) : std::vector<T, Allocator>(s, def), w(0), h(0) {};

  void setW(size_t _w) { w = _w; };
  void setH(size_t _h) { h = _h; };
  const T& at2D(size_t x, size_t y) { return std::vector<T, Allocator>::at(y * w + x); };
  const T& at2D(Point p) { return at2D(p.x, p.y); };

  // Convenience.
  void bitOr(size_t x, size_t y, T mask)  { std::vector<T, Allocator>::operator[](y * w + x) |= mask; };
  void bitAnd(size_t x, size_t y, T mask) { std::vector<T, Allocator>::operator[](y * w + x) &= mask; };
  void bitOr(Point p, T mask)  { this->bitOr(p.x, p.y, mask); };
  void bitAnd(Point p, T mask) { this->bitAnd(p.x, p.y, mask); };
};
