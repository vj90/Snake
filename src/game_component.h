#ifndef GAME_COMPONENT_H
#define GAME_COMPONENT_H

#include "renderer.h"

class GameComponent {
 public:
  virtual void Update(){}
  virtual void Render(){}
  virtual const bool FromFile(const std::string& line){ return false;}
  void SetParentRendererHandle(Renderer* handle) {
    _parent_renderer_handle = handle;
  }

 protected:
  Renderer* _parent_renderer_handle{nullptr};
};

#endif  // GAME_COMPONENT_H