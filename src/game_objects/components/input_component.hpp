#pragma once

// SFML includes
#include "SFML/System/Vector2.hpp"

// Local includes
#include "game_objects/entity.hpp"

struct Input : Component<Input> {
    Input();
    Input(EntityId entity_id);

    sf::Vector2f input_direction;
    bool possess_pressed;
};
