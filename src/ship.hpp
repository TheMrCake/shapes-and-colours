#pragma once

#include <memory>

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Vector2.hpp"

#include "bullet.hpp"

class Ship {
public:
  Ship();
  Ship(const Ship& s) = default;
  Ship(sf::Sprite& sprite);
  Ship(sf::Sprite& sprite, sf::Vector2f position);
  Ship(sf::Sprite& sprite, sf::Vector2f position, sf::Vector2f velocity);

  virtual ~Ship() = 0;

  virtual void update(const float& dt);

  virtual std::unique_ptr<Bullet> shoot() = 0;

  void set_sprite(sf::Sprite& new_sprite);
  const sf::Sprite& get_sprite();

  void set_position(const sf::Vector2f new_position);
  const sf::Vector2f get_position();
  
  void set_velocity(const sf::Vector2f new_velocity);
  const sf::Vector2f get_velocity();

  void kill();
  bool get_alive();

  bool get_ready_to_fire();
protected:
  void set_ready_to_fire(bool new_ready_to_fire);

  inline const static sf::Vector2f bullet_offset = {0, 50};
private:
  bool alive;
  bool ready_to_fire;

  sf::Sprite sprite;

  sf::Vector2f position;
  sf::Vector2f velocity;
};
