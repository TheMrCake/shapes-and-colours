#pragma once

// STD includes
#include <memory>

// SFML includes
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/System/Vector2.hpp"

// Box2D includes
#include "box2d/id.h"
#include "box2d/math_functions.h"

// SFML based transform
struct transform_info {
    sf::Vector2f position;
    float rotation_deg;
};

namespace Box2DUtils {
    // Convert from b2Transform to a transform_info
    const transform_info
    btransform_to_transform_info(const b2Transform& transform);
    // Convert from transform_info to a b2Transform
    const b2Transform
    transform_info_to_btransform(const transform_info& transform);

    // Convert from radians to degrees
    const float rad_to_deg(const float rad);
    // Convert from degrees to radians
    const float deg_to_rad(const float deg);

    // Convert from b2Vec2 to a Vector2f
    const sf::Vector2f bv2_to_sv2(const b2Vec2& in);
    // Convert from Vector2f to a b2Vec2
    const b2Vec2 sv2_to_bv2(const sf::Vector2f& in);

    // Convert between screenspace.y to physics.y
    const sf::Vector2f invert_height(const sf::Vector2f& in);
    // Get magnitude squared of the sfml vector
    const float magnitude_squared(const sf::Vector2f& in);
    // Get magnitude of the sfml vector
    const float magnitude(const sf::Vector2f& in);
    // Normalise sfml vector
    const sf::Vector2f normalize(const sf::Vector2f& in);

    // Create a Box2D rectangle body
    b2BodyId create_physics_rect(b2WorldId& world_id, const bool dynamic,
                                 const sf::Vector2f& position,
                                 const sf::Vector2f& size);
    b2BodyId create_physics_rect(b2WorldId& world_id, const bool dynamic,
                                 const sf::RectangleShape& rs);

    // Create a Box2D circle body
    b2BodyId create_physics_circle(b2WorldId& world_id, const bool dynamic,
                                   const sf::Vector2f& position,
                                   const float radius);
    b2BodyId create_physics_circle(b2WorldId& world_id, const bool dynamic,
                                   const sf::CircleShape& rs);
} // namespace Box2DUtils
