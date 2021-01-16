#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"

class Controller {
  enum class ControllerOutput { Quit, Game, Menu };

 public:
  ControllerOutput HandleInput(bool& output, Snake& snake) const;

 private:
};

#endif