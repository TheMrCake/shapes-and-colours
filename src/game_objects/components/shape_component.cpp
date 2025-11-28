#include "game_objects/components/shape_component.hpp"

std::unique_ptr<sf::Shape>& Shape::get_shape() {
  return shape;
}

const std::unique_ptr<sf::Shape>& Shape::get_shape_const() {
  return get_shape();
}
