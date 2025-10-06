#pragma once

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Vector2.hpp"

#include "ship.hpp"

class Invader : public Ship {
public:
  Invader();
  Invader(const Invader& inv) = default;
  Invader(sf::Sprite& sprite);
  Invader(sf::Sprite& sprite, sf::Vector2i column_row);

  virtual ~Invader() override = default;

  virtual void update(const float& dt) override;

  virtual std::unique_ptr<Bullet> shoot() override;

  static void set_bullet_sprite(sf::Sprite& new_bullet_sprite);
private:
  static sf::Vector2f column_row_to_pos(const sf::Vector2i& column_row);

  void set_y_position(const float& y_position);
private:
  inline static sf::Sprite bullet_sprite{};

  inline static sf::Vector2f group_velocity{90, 0};
  inline static float group_y_position = 0;
  constexpr static float velocity_multiplier = 1.05;
  constexpr static float move_down_distance = 20;

  sf::Vector2i column_row;
};
