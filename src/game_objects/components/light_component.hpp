#pragma once

// SFML includes
#include "SFML/Graphics/Color.hpp"

// Local includes
#include "SFML/System/Vector2.hpp"
#include "game_objects/entity.hpp"
#include "game_parameters.hpp"

struct Light : Component<Light> {
    Light();
    Light(EntityId entity_id);

    constexpr static int max_collisions = GameParameters::max_ray_collisions;
    constexpr static float max_length = GameParameters::max_ray_length;

    float wavelength;
    int remaining_collisions;

    sf::Vector2f direction{1.f, 0.f};
    sf::Vector2f targetDirection;
    float speed = 400.f;

    bool rotatingLeft = false;
    bool rotatingRight = false;
};
