#ifndef FOOD_H
#define FOOD_H

#include <iostream>
#include <random>

#include "SDL.h"
#include "game_component.h"

class Food : public GameComponent, public SDL_Point {
 public:
  Food(const std::size_t grid_width, const std::size_t grid_height);
  void Update();
  void Render();
  const bool FromFile(const std::string line);
  friend std::ostream& operator<<(std::ostream& os, const Food& food);

 private:
  std::random_device _dev;
  std::mt19937 _engine;
  std::uniform_int_distribution<int> _random_w;
  std::uniform_int_distribution<int> _random_h;
};

std::ostream& operator<<(std::ostream& os, const Food& food);

#endif