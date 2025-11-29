#include "game_objects/components/sprite_component.hpp"



sf::Sprite& Sprite::get_sprite() {
  return sprite;
}

const sf::Sprite& Sprite::get_sprite_const(){
  return get_sprite();
}
