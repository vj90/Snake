#include "renderer.h"

#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : _screen_width(screen_width),
      _screen_height(screen_height),
      _grid_width(grid_width),
      _grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  _sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                 SDL_WINDOWPOS_CENTERED, screen_width,
                                 screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == _sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  _sdl_renderer = SDL_CreateRenderer(_sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == _sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Set block size
  _block.w = _screen_width / _grid_width;
  _block.h = _screen_height / _grid_height;
}

Renderer::~Renderer() {
  SDL_DestroyWindow(_sdl_window);
  SDL_Quit();
}

void Renderer::ClearScreen() {
  // Clear screen
  SetColor(0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(_sdl_renderer);
}

void Renderer::UpdateScreen() {
  // Update Screen
  SDL_RenderPresent(_sdl_renderer);
}

void Renderer::SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  SDL_SetRenderDrawColor(_sdl_renderer, r, g, b, a);
}

void Renderer::FillBlock(int x, int y) {
  _block.x = x * _block.w;
  _block.y = y * _block.h;
  SDL_RenderFillRect(_sdl_renderer, &_block);
}

void Renderer::UpdateWindowTitle(const int score, const int fps,
                                 const int high_score) {
  std::string title{"Score: " + std::to_string(score) +               //
                    "   High Score: " + std::to_string(high_score) +  //
                    "   FPS: " + std::to_string(fps) +                //
                    "   Esc: Menu"};
  SDL_SetWindowTitle(_sdl_window, title.c_str());
}
