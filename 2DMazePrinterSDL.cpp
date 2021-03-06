#include <SDL2/SDL.h>
#include <iostream>
#include <map>

#include "MazeGenerator.h"
#include "types.h"
#include "2DMazePrinterSDL.h"
#include "Drawer.h"

DrawEngine::DrawEngine(MazeGenerator& _mg, size_t _pixelSize = 1) : mg(_mg), pixelSize(_pixelSize), quit(false) {
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
  // Clear background.
  SDL_SetRenderDrawColor(renderer, 20, 40, 60, 255);
  SDL_RenderClear(renderer);

  // Basic cell background.
  SDL_SetRenderDrawColor(renderer, 100, 150, 200, 255);
  SDL_Rect rectFull{int(pixelSize * 4), int(pixelSize * 4), int(mg.getW() * pixelSize * 4), int(mg.getH() * pixelSize * 4)};
  SDL_RenderFillRect(renderer, &rectFull);
  
  SDL_SetRenderDrawColor(renderer, 20, 40, 60, 255);
  for (int y = 0; y < mg.getH(); y++) {
    for (int x = 0; x < mg.getW(); x++) {
      int cx = int(((x + 1) * pixelSize * 4));
      int cy = int(((y + 1) * pixelSize * 4));

      // "Carve" out the roads.
      std::map<uint_t, SDL_Rect> sides{
        {CELL_UP, {int(cx + pixelSize), cy, int(pixelSize * 2), int(pixelSize * 3)}},
        {CELL_DOWN, {int(cx + pixelSize), int(cy + pixelSize), int(pixelSize * 2), int(pixelSize * 3)}},
        {CELL_LEFT, {cx, int(cy + pixelSize), int(pixelSize * 3), int(pixelSize * 2)}},
        {CELL_RIGHT, {int(cx + pixelSize), int(cy + pixelSize), int(pixelSize * 3), int(pixelSize * 2)}},
      };
      for (auto const &side : sides) {
        if (side.first & mg.getCell(x, y)) {
          SDL_RenderFillRect(renderer, &side.second);
        }
      }
    }
  }

  // Solution.
  SDL_SetRenderDrawColor(renderer, 200, 220, 240, 255);

  // Quick fix to cover the very first block - do to the shifted print.
  SDL_Rect first_box_rect{int(pixelSize * 5.5), int(pixelSize * 5.5), int(pixelSize), int(pixelSize)};
  SDL_RenderFillRect(renderer, &first_box_rect);

  coord_t c{mg.getW() - 1, mg.getH() - 1};
  while (true) {
    uint_t p = mg.getCell(c) >> 4;

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

  for (auto drawer : drawers) {
    drawer->draw(this);
  }
}

void DrawEngine::add_drawer(Drawer* drawer) {
  drawers.push_back(drawer);
}
