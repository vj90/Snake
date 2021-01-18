#ifndef SNAKE_H
#define SNAKE_H

#include <iostream>
#include <vector>

#include "SDL.h"
#include "game_component.h"

class Snake : public GameComponent {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight, kPause };

  Snake(int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(grid_width / 2),
        head_y(grid_height / 2) {}

  void Update();
  void Render();
  void Reset();
  const bool FromFile(const std::string line);

  void GrowBody();
  bool SnakeCell(int x, int y);
  void SetDirection(Direction input, Direction opposite);

  float speed{0.1f};
  int size{1};
  bool alive{true};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;
  friend std::ostream& operator<<(std::ostream& os, const Snake& snake);

 private:
  void UpdateHead();
  void UpdateBody(SDL_Point& current_cell, SDL_Point& prev_cell);

  bool growing{false};
  int grid_width;
  int grid_height;
  Direction _direction = Direction::kUp;
};

std::ostream& operator<<(std::ostream& os, const Snake& snake);

#endif