#pragma once

// STD includes
#include <memory>

// SFML includes
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

// Box2D includes
#include "box2d/id.h"
#include "box2d/math_functions.h"

namespace Box2DUtils {
  //Convert from b2Vec2 to a Vector2f
  const sf::Vector2f bv2_to_sv2(const b2Vec2& in);
  //Convert from Vector2f to a b2Vec2
  const b2Vec2 sv2_to_bv2(const sf::Vector2f& in);
  //Convert from screenspace.y to physics.y 
  const sf::Vector2f invert_height(const sf::Vector2f& in);
  
  // Create a Box2D rectangle body
  b2BodyId create_physics_rect(b2WorldId& world_id, const bool dynamic, const sf::Vector2f& position, const sf::Vector2f& size);
  b2BodyId create_physics_rect(b2WorldId& world_id, const bool dynamic, const sf::RectangleShape& rs);

  // Create a Box2D circle body
  b2BodyId create_physics_circle(b2WorldId& world_id, const bool dynamic, const sf::Vector2f& position, const float radius);
  b2BodyId create_physics_circle(b2WorldId& world_id, const bool dynamic, const sf::CircleShape& rs);
}
