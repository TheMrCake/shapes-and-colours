#include "player.hpp"

#include <memory>


#include "SFML/System/Clock.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Keyboard.hpp"


#include "bullet.hpp"
#include "game_parameters.hpp"
#include "ship.hpp"

Player::Player() : Ship() {}
Player::Player(sf::Sprite& sprite, sf::Vector2f position) : Ship(sprite, position) {}

void Player::update(const float& dt) {
  Ship::update(dt);

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    set_velocity({-movement_speed, 0});
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    set_velocity({movement_speed, 0});
  } else {
    set_velocity({0, 0});
  }

  if (shoot_timer.getElapsedTime().asSeconds() >= 0.33f && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {    
    shoot_timer.restart();
    set_ready_to_fire(true);
  }
} 

std::unique_ptr<Bullet> Player::shoot() {
  set_ready_to_fire(false);
  std::unique_ptr<Bullet> bullet = std::make_unique<Bullet>(bullet_sprite, get_position() - bullet_offset, sf::Vector2f(0, -GameParameters::bullet_speed));
  return std::move(bullet);
}

void Player::set_bullet_sprite(sf::Sprite &new_bullet_sprite) {
  bullet_sprite = new_bullet_sprite;
}
