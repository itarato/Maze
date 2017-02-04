#pragma once

#include <vector>
#include <map>
#include "types.hpp"

class MazeGenerator {
private:
  size_t w;
  size_t h;
  std::vector<uint> cells;

  void reset();
  void attemptGeneration();
  void generate();
  size_t c2idx(size_t, size_t);
  size_t c2idx(coord_t);
  std::map<uint, coord_t> getAvailables(coord_t);

public:
  MazeGenerator(size_t, size_t);

  std::vector<uint>& getMaze();
  uint getCell(size_t, size_t);
  uint getCell(coord_t);
  size_t getW();
  size_t getH();

  friend std::ostream& operator<<(std::ostream&, const MazeGenerator&);
};
