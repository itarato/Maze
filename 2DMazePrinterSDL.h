#pragma once

class MazeGenerator;
class Drawer;

#include <SDL2/SDL.h>
#include <vector>

class DrawEngine {
private:
  SDL_Window *win;

  MazeGenerator& mg;
  std::vector<Drawer*> drawers;

  bool quit;

  void draw();

public:
  DrawEngine(MazeGenerator&, size_t);
  ~DrawEngine();

  SDL_Renderer *renderer;
  size_t pixelSize;

  void add_drawer(Drawer *);
  void run();
};
