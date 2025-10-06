#include "invader.hpp"

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Vector2.hpp"

#include "game_parameters.hpp"
#include <memory>

Invader::Invader() : Ship() {}
Invader::Invader(sf::Sprite& sprite) : Ship(sprite) {}
Invader::Invader(sf::Sprite &sprite, sf::Vector2i column_row)
    : Ship(sprite, column_row_to_pos(column_row), Invader::group_velocity),
      column_row(column_row) {}

void Invader::update(const float& dt) {
  Ship::update(dt);

  const sf::Sprite& sprite = get_sprite();
  if ((group_velocity.x > 0 && sprite.getPosition().x > GameParameters::game_width - GameParameters::sprite_size/2.f) ||
     (group_velocity.x < 0 && sprite.getPosition().x < GameParameters::sprite_size/2.f)) {
    group_velocity.x *= -velocity_multiplier;
    sf::Vector2f position = get_position(); 
    group_y_position = group_y_position + move_down_distance;
  }

  set_y_position(group_y_position + column_row_to_pos(column_row).y);
  set_velocity(group_velocity);
}

std::unique_ptr<Bullet> Invader::shoot() {
  set_ready_to_fire(false);
  std::unique_ptr<Bullet> bullet = std::make_unique<Bullet>(bullet_sprite, get_position() + bullet_offset, sf::Vector2f(0, -GameParameters::bullet_speed));
  return std::move(std::make_unique<Bullet>(bullet_sprite, get_position(), sf::Vector2f(0, GameParameters::bullet_speed)));
}


void Invader::set_bullet_sprite(sf::Sprite &new_bullet_sprite) {
  bullet_sprite = new_bullet_sprite;
}



sf::Vector2f Invader::column_row_to_pos(const sf::Vector2i& column_row) {
  return sf::Vector2f(column_row.x * GameParameters::total_sprite_size * 1.f,
                   column_row.y * GameParameters::total_sprite_size * 1.f);
}



void Invader::set_y_position(const float& y_position) {
  set_position({get_position().x, y_position});  
}
