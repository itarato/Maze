#pragma once

#include <vector>
#include <map>
#include "types.h"

class MazeGenerator {
private:
  size_t w;
  size_t h;
  // Cells keep the allowed movements and parent relationship for each cell in the following way:
  // The first 4 bits are the allowed path mask. (Path direction are from types.hpp.) For example
  // If bit-0 is 1 than UP is allowed. Bit-1 == 1 indicates RIGHT.
  // Bit 4-7 to mark the parent using the same directions. For example if bit-4 is 1 than the
  // parent is the cell UP to the current cell.
  std::vector<uint_t> cells;

  void reset();
  void attemptGeneration();
  void generate();
  size_t c2idx(size_t, size_t);
  size_t c2idx(coord_t);
  std::map<uint_t, coord_t> getAvailables(coord_t);

public:
  MazeGenerator(size_t, size_t);

  std::vector<uint_t>& getMaze();
  uint_t getCell(size_t, size_t);
  uint_t getCell(coord_t);
  size_t getW();
  size_t getH();
  coord_t getStart();
  coord_t getEnd();

  friend std::ostream& operator<<(std::ostream&, const MazeGenerator&);
};
