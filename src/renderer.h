#ifndef RENDERER_H
#define RENDERER_H

#include <vector>

#include "SDL.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void UpdateWindowTitle(int score, int fps);
  void ClearScreen();
  void UpdateScreen();
  void FillBlock(int x, int y);
  void SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
  const std::size_t GridWidth() { return _grid_width; }
  const std::size_t GridHeight() { return _grid_height; }
  
 private:
  SDL_Window* _sdl_window;
  SDL_Renderer* _sdl_renderer;

  const std::size_t _screen_width;
  const std::size_t _screen_height;
  const std::size_t _grid_width;
  const std::size_t _grid_height;
  SDL_Rect _block;  // helper for filling blocks
};

#endif