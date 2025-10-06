#include "ship.hpp"

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Vector2.hpp"

Ship::Ship()
  : alive(true)
  , ready_to_fire(false)
  , sprite()
  , position(0, 0)
  , velocity(0, 0) {}

Ship::Ship(sf::Sprite& sprite)
  : alive(true)
  , ready_to_fire(false)
  , sprite(sprite)
  , position(0, 0)
  , velocity(0, 0) {}

Ship::Ship(sf::Sprite& sprite, sf::Vector2f position)
  : alive(true)
  , ready_to_fire(false)
  , sprite(sprite)
  , position(position)
  , velocity(0, 0) {}

Ship::Ship(sf::Sprite& sprite, sf::Vector2f position, sf::Vector2f velocity)
  : alive(true)
  , ready_to_fire(false)
  , sprite(sprite)
  , position(position)
  , velocity(velocity) {}

Ship::~Ship() {}



void Ship::update(const float& dt) {
  set_position(position + velocity * dt);
}



void Ship::set_sprite(sf::Sprite& new_sprite) {
  sprite = new_sprite;
  sprite.setPosition(position);
}

const sf::Sprite& Ship::get_sprite() {
  return sprite;
}



void Ship::set_position(sf::Vector2f new_position) {
  position = new_position;
  sprite.setPosition(position);
}

const sf::Vector2f Ship::get_position() {
  return position;
}



void Ship::set_velocity(sf::Vector2f new_velocity) {
  velocity = new_velocity;
}

const sf::Vector2f Ship::get_velocity() {
  return velocity;
}



void Ship::kill() {
  alive = false;
}

bool Ship::get_alive() {
  return alive;
}


bool Ship::get_ready_to_fire() {
  return ready_to_fire;  
}

void Ship::set_ready_to_fire(bool new_ready_to_fire) {
  ready_to_fire = new_ready_to_fire;
}
