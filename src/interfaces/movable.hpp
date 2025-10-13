#pragma once

// SFML includes
#include "SFML/System/Vector2.hpp"

// Local includes 
#include "interfaces/positionable.hpp"

class Movable : public Positionable {
public:
  Movable();
  Movable(const Positionable& positionable, const sf::Vector2f& velocity);
  Movable(const Movable& movable) = default;

  virtual ~Movable() = 0;

  virtual const sf::Vector2f& get_velocity();
  virtual void set_velocity(const sf::Vector2f& v);
private:
  sf::Vector2f velocity;
};
