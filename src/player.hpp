#pragma once

#include <memory>

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Clock.hpp"
#include "SFML/System/Vector2.hpp"

#include "bullet.hpp"
#include "ship.hpp"


class Player : public Ship {
public:  
  Player();
  Player(sf::Sprite& sprite, sf::Vector2f position);
  Player(const Player& player) = default;

  virtual void update(const float& dt) override;

  virtual std::unique_ptr<Bullet> shoot() override;

  static void set_bullet_sprite(sf::Sprite& new_bullet_sprite);
private:
  inline static sf::Sprite bullet_sprite{};
  constexpr static float movement_speed = 150;

  sf::Clock shoot_timer{};
};
