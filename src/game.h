#ifndef GAME_H
#define GAME_H

#include <memory>
#include <random>

#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"

class Game {
 public:
  Game(std::unique_ptr<Renderer>& renderer,
       std::unique_ptr<Controller>& controller);
  void Run(std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

 private:
  Snake _snake;
  SDL_Point _food;
  std::unique_ptr<Renderer> _renderer{nullptr};
  std::unique_ptr<Controller> _controller{nullptr};

  std::random_device _dev;
  std::mt19937 _engine;
  std::uniform_int_distribution<int> _random_w;
  std::uniform_int_distribution<int> _random_h;

  int score{0};

  void PlaceFood();
  void Update();
};

#endif