#include "snake.h"

#include <cmath>
#include <iostream>

#include "SDL.h"

void Snake::Update() {
  SDL_Point prev_cell{
      static_cast<int>(head_x),
      static_cast<int>(
          head_y)};  // We first capture the head's cell before updating.
  UpdateHead();
  SDL_Point current_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};  // Capture the head's cell after updating.

  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
    UpdateBody(current_cell, prev_cell);
  }
}

void Snake::SetDirection(Snake::Direction input, Snake::Direction opposite) {
  // direction does not change to opposite even if snake size is 1
  _direction = input == opposite ? _direction : input;
}

void Snake::Render() {
  // Render snake's body
  _parent_renderer_handle->SetColor(0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : this->body) {
    _parent_renderer_handle->FillBlock(point.x, point.y);
  }

  // Render snake's head
  if (this->alive) {
    _parent_renderer_handle->SetColor(0x00, 0x7A, 0xCC, 0xFF);
  } else {
    _parent_renderer_handle->SetColor(0xFF, 0x00, 0x00, 0xFF);
  }
  _parent_renderer_handle->FillBlock(static_cast<int>(this->head_x),
                                     static_cast<int>(this->head_y));
}

void Snake::UpdateHead() {
  switch (_direction) {
    case Direction::kUp:
      head_y -= speed;
      break;

    case Direction::kDown:
      head_y += speed;
      break;

    case Direction::kLeft:
      head_x -= speed;
      break;

    case Direction::kRight:
      head_x += speed;
      break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  head_x = fmod(head_x + grid_width, grid_width);
  head_y = fmod(head_y + grid_height, grid_height);
}

void Snake::UpdateBody(SDL_Point &current_head_cell,
                       SDL_Point &prev_head_cell) {
  // Add previous head location to vector
  body.push_back(prev_head_cell);

  if (!growing) {
    // Remove the tail from the vector.
    body.erase(body.begin());
  } else {
    growing = false;
    size++;
  }

  // Check if the snake has died.
  for (auto const &item : body) {
    if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
      alive = false;
    }
  }
}

void Snake::GrowBody() { growing = true; }

// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeCell(int x, int y) {
  if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y)) {
    return true;
  }
  for (auto const &item : body) {
    if (x == item.x && y == item.y) {
      return true;
    }
  }
  return false;
}

std::ostream &operator<<(std::ostream &os, const Snake &snake) {
  os << snake.head_x << " " << snake.head_y << std::endl;
  for (const auto &pt : snake.body) {
    os << pt.x << " " << pt.y << std::endl;
  }
  return os;
}