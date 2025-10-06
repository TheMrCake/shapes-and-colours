#include "bullet.hpp"

Bullet::Bullet() : sprite(), lifetime() {}

Bullet::Bullet(sf::Sprite& sprite, sf::Vector2f position, sf::Vector2f velocity)
  : sprite(sprite)
  , position(position)
  , velocity(velocity) {}



void Bullet::update(const float dt) {
  set_position(position + velocity * dt);
}



void Bullet::set_sprite(sf::Sprite& new_sprite) {
  sprite = new_sprite;
  sprite.setPosition(position);
}

const sf::Sprite& Bullet::get_sprite() {
  return sprite;
}



void Bullet::set_position(sf::Vector2f new_position) {
  position = new_position;
  sprite.setPosition(position);
}

const sf::Vector2f Bullet::get_position() {
  return position;
}



void Bullet::set_velocity(sf::Vector2f new_velocity) {
  velocity = new_velocity;
}

const sf::Vector2f Bullet::get_velocity() {
  return velocity;
}

bool Bullet::get_alive() {
  return true ? lifetime.getElapsedTime().asSeconds() > max_lifetime_seconds || killed : false;
}

void Bullet::kill() {
  killed = true;
}
