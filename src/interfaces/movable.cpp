
#include "movable.hpp"

Movable::Movable()
  : Positionable()
  , velocity()
{}

Movable::Movable(const Positionable& positionable, const sf::Vector2f& velocity)
  : Positionable(positionable)
  , velocity(velocity)
{}

Movable::~Movable()
{}



const sf::Vector2f& Movable::get_velocity() {
  return velocity;
}
void Movable::set_velocity(const sf::Vector2f& v) {
  velocity = v;  
}
