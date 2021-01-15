#include "game.h"

#include <iostream>

#include "SDL.h"

Game::Game(std::unique_ptr<Renderer>& renderer,
           std::unique_ptr<Controller>& controller)
    : _snake(renderer->GridWidth(), renderer->GridHeight()),
      _engine(dev()),
      _random_w(0, static_cast<int>(renderer->GridWidth()) - 1),
      _random_h(0, static_cast<int>(renderer->GridHeight()) - 1) {
  _renderer = std::move(renderer);
  _controller = std::move(controller);
  snake.SetParentRendererHandle(_renderer.get());
  PlaceFood();
}

void Game::Run(std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    _controller->HandleInput(running, _snake);
    Update();

    // Render everything
    _renderer->ClearScreen();
    /_snake.Render();
    _renderer->UpdateScreen();
    //_renderer->Render(snake, food);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      _renderer->UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = _random_w(_engine);
    y = _random_h(_engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!_snake.SnakeCell(x, y)) {
      _food.x = x;
      _food.y = y;
      return;
    }
  }
}

void Game::Update() {
  if (!_snake.alive) return;

  _snake.Update();

  int new_x = static_cast<int>(_snake.head_x);
  int new_y = static_cast<int>(_snake.head_y);

  // Check if there's food over here
  if (_food.x == new_x && _food.y == new_y) {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    _snake.GrowBody();
    _snake.speed += 0.02;
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }