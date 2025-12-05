//
// Created by deborah ama on 05/12/2025.
//

#pragma once
#include "game_objects/entity.hpp"

struct LightBeam : Component<LightBeam> {
    LightBeam() = default;
    LightBeam(EntityId id) : Component<LightBeam>(id) {}

    sf::Vector2f direction;
    sf::Vector2f targetDirection;
    float speed = 400.f;
};
