#include "utils/b2d_utils.hpp"

// Box2d includes
#include "box2d/box2d.h"
#include "box2d/collision.h"
#include "box2d/types.h"

// Local includes
#include "game_parameters.hpp"



// Convert from b2Vec2 to a Vector2f
const sf::Vector2f Box2DUtils::bv2_to_sv2(const b2Vec2& in) {
  return {in.x * GameParameters::physics_scale, (in.y * GameParameters::physics_scale)};
}

// Convert from Vector2f to a b2Vec2
const b2Vec2 sv2_to_bv2(const sf::Vector2f& in) {
  return {in.x * GameParameters::physics_scale_inv, in.y * GameParameters::physics_scale_inv};
}

// Convert from screenspace.y to physics.y 
const sf::Vector2f Box2DUtils::invert_height(const sf::Vector2f& in) {
  return sf::Vector2f(in.x, GameParameters::game_height - in.y);
}

// Create box2d rectangle
b2BodyId Box2DUtils::create_physics_rect(b2WorldId& world_id, const bool dynamic, const sf::Vector2f& position, const sf::Vector2f& size) {
  b2BodyDef body_def = b2DefaultBodyDef();

  // Is Dynamic(moving), or static(Stationary)
  body_def.type = dynamic ? b2_dynamicBody : b2_staticBody;
  body_def.position = sv2_to_bv2(position);

  // Create the body
  b2BodyId body_id = b2CreateBody(world_id, &body_def);

  // Create the fixture shape
  b2ShapeDef shape_def = b2DefaultShapeDef();
  shape_def.density = dynamic ? 10.f : 0.f;
  shape_def.material.friction =  dynamic ? 0.8f : 1.f;
  shape_def.material.restitution = 1.0f;
  b2Polygon polygon = b2MakeBox(sv2_to_bv2(size).x * 0.5f, sv2_to_bv2(size).y * 0.5f);
  b2CreatePolygonShape(body_id, &shape_def, &polygon);
  return body_id;
}

// Create box2d rectangle with sfml rectangle
b2BodyId Box2DUtils::create_physics_rect(b2WorldId& world_id, const bool dynamic, const sf::RectangleShape& rs) {
  return create_physics_rect(world_id, dynamic, rs.getPosition(), rs.getSize());
}

// Create box2d circle
b2BodyId Box2DUtils::create_physics_circle(b2WorldId& world_id, const bool dynamic, const sf::Vector2f& center_position, const float radius) {
  b2BodyDef body_def = b2DefaultBodyDef();

  // Is Dynamic(moving), or static(Stationary)
  body_def.type = dynamic ? b2_dynamicBody : b2_staticBody;
  body_def.position = sv2_to_bv2(center_position);

  // Create the body
  b2BodyId body_id = b2CreateBody(world_id, &body_def);

  // Create the fixture shape
  b2ShapeDef shape_def = b2DefaultShapeDef();
  shape_def.density = dynamic ? GameParameters::default_density : 0.f;
  shape_def.material.friction =  dynamic ? GameParameters::default_friction : 1.f;
  shape_def.material.restitution = GameParameters::default_restitution;
  b2Circle circle {{}, radius};

  b2CreateCircleShape(body_id, &shape_def, &circle);

  return body_id;
}

// Create box2d circle with sfml circle
b2BodyId Box2DUtils::create_physics_circle(b2WorldId& world_id, const bool dynamic, const sf::CircleShape& cs) {
  return create_physics_circle(world_id, dynamic, cs.getPosition(), cs.getRadius());
}
