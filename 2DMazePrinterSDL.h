#pragma once

class MazeGenerator

#include "SDL.h"

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
