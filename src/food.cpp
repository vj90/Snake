#include "food.h"

Food::Food(const std::size_t grid_width, const std::size_t grid_height)
    : _engine(_dev()),
      _random_w(0, static_cast<int>(grid_width) - 1),
      _random_h(0, static_cast<int>(grid_height) - 1) {}

void Food::Update() {
  this->x = _random_w(_engine);
  this->y = _random_h(_engine);
}

void Food::Render() {
  _parent_renderer_handle->SetColor(0xFF, 0xCC, 0x00, 0xFF);
  _parent_renderer_handle->FillBlock(this->x, this->y);
}

std::ostream& operator<<(std::ostream& os, const Food& food) {
  os << food.x << " " << food.y << std::endl;
  return os;
}