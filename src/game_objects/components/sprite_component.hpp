#pragma once

// Local includes
#include "SFML/Graphics/Sprite.hpp"
#include "game_objects/entity.hpp"


class Sprite : Component<Sprite> {
  friend Component<Sprite>;
public:
  sf::Sprite& get_sprite();
  const sf::Sprite& get_sprite_const();

private:
  void update_impl(const float delta_time) { /* Implement in Derived classes */ }; 

  sf::Sprite sprite;
};
