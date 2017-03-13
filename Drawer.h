#pragma once

class DrawEngine;

class Drawer {
public:
  virtual void draw(DrawEngine *) = 0;
};
