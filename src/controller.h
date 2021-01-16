#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"

class Controller {
 public:
  enum class ControllerOutput { Quit, Game, Menu };
  void HandleInput(bool& output, Snake& snake,
                   Controller::ControllerOutput& controller_output) const;

 private:
};

#endif