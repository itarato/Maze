#include <SDL.h>
#include <iostream>
#include <map>
#include "MazeGenerator.h"
#include "types.hpp"

class DrawEngine {
private:
  SDL_Window *win;
  SDL_Renderer *renderer;

  MazeGenerator& mg;
  size_t pixelSize;
  
  bool quit;

  void draw();

public:
  DrawEngine(MazeGenerator&, size_t);
  ~DrawEngine();

  void run();
};

DrawEngine::DrawEngine(MazeGenerator& _mg, size_t _pixelSize = 1) : mg(_mg), pixelSize(_pixelSize) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cerr << "SDL Init Error\n";
    exit(1);
  }

  win = SDL_CreateWindow("Maze", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (mg.getW() + 2) * pixelSize * 4, (mg.getH() + 2) * pixelSize * 4, SDL_WINDOW_SHOWN);
  if (win == nullptr) {
    std::cerr << "Window creation error\n";
    exit(1);
  }

  renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer == nullptr) {
    std::cerr << "Renderer creation error\n";
    exit(1);
  }

  run();
}

DrawEngine::~DrawEngine() {
  SDL_DestroyWindow(win);
  SDL_DestroyRenderer(renderer);
}

void DrawEngine::run() {
  while (!quit) {
    draw();
    SDL_RenderPresent(renderer);
    SDL_Delay(100);

    SDL_Event e;
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_MOUSEBUTTONDOWN) quit = true;
    }
  }
}

void DrawEngine::draw() {
  SDL_SetRenderDrawColor(renderer, 200, 200, 100, 255);

  for (int y = 0; y < mg.getH(); y++) {
    for (int x = 0; x < mg.getW(); x++) {
      int cx = int(((x + 1) * pixelSize * 4));
      int cy = int(((y + 1) * pixelSize * 4));

      if (mg.getCell(x, y) == CELL_EMPTY) {
        SDL_Rect cell{cx, cy, int(pixelSize * 4), int(pixelSize * 4)};
        SDL_RenderFillRect(renderer, &cell);
      } else {
        std::map<uint, SDL_Rect> sides{
          {CELL_UP, {cx, cy, int(pixelSize * 4), int(pixelSize)}},
          {CELL_DOWN, {cx, int(cy + pixelSize * 3), int(pixelSize * 4), int(pixelSize)}},
          {CELL_LEFT, {cx, cy, int(pixelSize), int(pixelSize * 4)}},
          {CELL_RIGHT, {int(cx + pixelSize * 3), cy, int(pixelSize), int(pixelSize * 4)}},
        };
        for (auto const &side : sides) {
          if (!(side.first & mg.getCell(x, y))) {
            SDL_RenderFillRect(renderer, &side.second);
          }
        }
      }
    }
  }

  // Solution.
  SDL_SetRenderDrawColor(renderer, 200, 50, 50, 255);
  coord_t c{mg.getW() - 1, mg.getH() - 1};
  while (true) {
    uint p = mg.getCell(c) >> 4;

    int cx = int((c.first + 1) * pixelSize * 4 + pixelSize);
    int cy = int((c.second + 1) * pixelSize * 4 + pixelSize);

    SDL_Rect cell;
    switch (p) {
      case CELL_UP:    cell = {int(cx + pixelSize / 2), int(cy - pixelSize * 2.5), int(pixelSize), int(pixelSize * 4)}; break;
      case CELL_DOWN:  cell = {int(cx + pixelSize / 2), int(cy + pixelSize / 2), int(pixelSize), int(pixelSize * 4)}; break;
      case CELL_LEFT:  cell = {int(cx - pixelSize * 2.5), int(cy + pixelSize / 2), int(pixelSize * 4), int(pixelSize)}; break;
      case CELL_RIGHT: cell = {int(cx + pixelSize / 2), int(cy + pixelSize / 2), int(pixelSize * 4), int(pixelSize)}; break;
      default: break;
    }
    SDL_RenderFillRect(renderer, &cell);

    if (c.first == 0 && c.second == 0) break;

    switch (p) {
      case CELL_UP: c = {c.first, c.second - 1}; break;
      case CELL_DOWN: c = {c.first, c.second + 1}; break;
      case CELL_LEFT: c = {c.first - 1, c.second}; break;
      case CELL_RIGHT: c = {c.first + 1, c.second}; break;
      default: break;
    }
  }
}
