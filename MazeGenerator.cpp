#pragma once

#include "MazeGenerator.h"
#include <iostream>
#include <queue>
#include <utility>
#include <map>
#include <algorithm>
#include <iterator>
#include <random>

MazeGenerator::MazeGenerator(size_t w, size_t h) : w(w), h(h), cells(w * h, CELL_EMPTY) {
  generate();
}

void MazeGenerator::reset() {
  std::for_each(cells.begin(), cells.end(), [](uint& v){ v = CELL_EMPTY; });
}

void MazeGenerator::generate() {
  // Run as long as there is a maze generated that reaches the very end.
  while (cells.back() == CELL_EMPTY) {
    reset();
    attemptGeneration();
  }
  // Carve the destination.
  cells[w * h - 1] |= CELL_DOWN;
}

void MazeGenerator::attemptGeneration() {
  std::queue<coord_t> q;
  q.push({0, 0});
  cells[c2idx(0, 0)] = CELL_UP | (CELL_UP << 4);

  while (!q.empty()) {
    auto coord = q.front();
    q.pop();

    auto availables = getAvailables(coord);
    std::vector<std::pair<uint, coord_t>> availables_flat;
    std::copy(availables.begin(), availables.end(), std::back_inserter(availables_flat));

    std::random_device _random_device;
    std::mt19937_64 _random_generator{_random_device()};
    std::shuffle(availables_flat.begin(), availables_flat.end(), _random_generator);
    std::uniform_int_distribution<int> _random_dist(0, 10);
    for (const auto& elem : availables_flat) {
        cells[c2idx(coord)] |= elem.first;
        q.push(elem.second);

        uint _opposite = opposite_dir(elem.first);
        cells[c2idx(elem.second)] = _opposite | (_opposite << 4);
        
        if (_random_dist(_random_device) < 9) break;
    }
  }
}

std::vector<uint>& MazeGenerator::getMaze() { return cells; }

size_t MazeGenerator::getW() { return w; }
size_t MazeGenerator::getH() { return h; }

size_t MazeGenerator::c2idx(size_t x, size_t y) { return y * w + x; }
size_t MazeGenerator::c2idx(coord_t c) { return c.second * w + c.first; }

uint MazeGenerator::getCell(size_t x, size_t y) { return cells[c2idx(x, y)]; }
uint MazeGenerator::getCell(coord_t c) { return cells[c2idx(c)]; }

std::map<uint, coord_t> MazeGenerator::getAvailables(coord_t c) {
  std::map<uint, coord_t> m;
  std::map<uint, std::pair<int, int>> dirs {
    {CELL_LEFT, {-1, 0}}, 
    {CELL_RIGHT, {1, 0}},
    {CELL_UP, {0, -1}},
    {CELL_DOWN, {0, 1}},
  };

  for (const auto& elem : dirs) {
    int offX = c.first + elem.second.first;
    int offY = c.second + elem.second.second;
    if (0 <= offX && offX < w && 0 <= offY && offY < h && cells[c2idx(offX, offY)] == CELL_EMPTY) {
      m[elem.first] = {offX, offY};
    }
  }

  return m;
}

std::ostream& operator<<(std::ostream& os, const MazeGenerator& mg) {
  os << "MazeGenerator [" << mg.w << ':' << mg.h << ']';
  return os;
}
