#pragma once

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Clock.hpp"
#include "SFML/System/Vector2.hpp"


class Bullet {
public:
  Bullet();
  Bullet(const Bullet& s) = default;
  Bullet(sf::Sprite& sprite, sf::Vector2f position, sf::Vector2f velocity);

  void update(const float dt);

  void set_sprite(sf::Sprite& new_sprite);
  const sf::Sprite& get_sprite();

  void set_position(const sf::Vector2f new_position);
  const sf::Vector2f get_position();
  
  void set_velocity(const sf::Vector2f new_velocity);
  const sf::Vector2f get_velocity();

  bool get_alive();
  void kill();
private:
  constexpr static float max_lifetime_seconds = 5.f;

  sf::Sprite sprite;

  sf::Vector2f position;
  sf::Vector2f velocity;

  sf::Clock lifetime;
  bool killed;
};
