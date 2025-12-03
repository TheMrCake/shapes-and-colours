#pragma once

// Local includes
#include "SFML/Graphics/Sprite.hpp"
#include "game_objects/entity.hpp"


struct Sprite : Component<Sprite> {
  Sprite();
  Sprite(EntityId entity_id);

  sf::Sprite sprite;
};
