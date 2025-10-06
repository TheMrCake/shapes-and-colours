#include "positionable.hpp"
#include "SFML/System/Vector2.hpp"

Positionable::Positionable()
  : position() {}

Positionable::Positionable(const sf::Vector2f& position)
  : position(position) {}

Positionable::~Positionable() {}



const sf::Vector2f& Positionable::get_position() {
  return position;  
}

void Positionable::set_position(const sf::Vector2f& p) {
  position = p;
}
