#include "controller.h"

#include <iostream>

#include "SDL.h"
#include "snake.h"

void Controller::HandleInput(
    bool &running, Snake &snake,
    Controller::ControllerOutput &controller_output) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
      controller_output = ControllerOutput::Quit;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          snake.SetDirection(Snake::Direction::kUp, Snake::Direction::kDown);
          controller_output = ControllerOutput::Game;
          break;

        case SDLK_DOWN:
          snake.SetDirection(Snake::Direction::kDown, Snake::Direction::kUp);
          controller_output = ControllerOutput::Game;
          break;

        case SDLK_LEFT:
          snake.SetDirection(Snake::Direction::kLeft, Snake::Direction::kRight);
          controller_output = ControllerOutput::Game;
          break;

        case SDLK_RIGHT:
          snake.SetDirection(Snake::Direction::kRight, Snake::Direction::kLeft);
          controller_output = ControllerOutput::Game;
          break;
        case SDLK_ESCAPE:
          controller_output = ControllerOutput::Menu;
      }
    }
  }
}