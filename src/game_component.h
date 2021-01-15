#ifndef GAME_COMPONENT_H
#define GAME_COMPONENT_H

#include "renderer.h"

class GameComponent{
  public:
  virtual void update();
  virtual void render();
  protected:
  Renderer* _parent_renderer_handle;

}



#endif // GAME_COMPONENT_H