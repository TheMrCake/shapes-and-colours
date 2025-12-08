#pragma once

// STD includes
#include <memory>

// Local includes
#include "SFML/Graphics/Shape.hpp"
#include "game_objects/entity.hpp"

struct Shape : Component<Shape> {
    Shape();
    Shape(EntityId entity_id);

    std::unique_ptr<sf::Shape> shape;
    bool visible = true;
};
