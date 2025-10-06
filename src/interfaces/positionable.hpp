#pragma once

// SFML includes
#include "SFML/System/Vector2.hpp"

class Positionable {
public:
  Positionable();
  Positionable(const sf::Vector2f& position);
  Positionable(const Positionable& positionable) = default;

  virtual ~Positionable() = 0;

  virtual const sf::Vector2f& get_position();
  virtual void set_position(const sf::Vector2f& p);
private:
  sf::Vector2f position;
};
