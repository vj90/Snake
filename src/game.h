#ifndef GAME_H
#define GAME_H

#include <memory>
#include <random>

#include "SDL.h"
#include "controller.h"
#include "food.h"
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
  Food _food;
  std::unique_ptr<Renderer> _renderer{nullptr};
  std::unique_ptr<Controller> _controller{nullptr};

  int _score{0};

  void PlaceFood();
  void Update();
};

#endif