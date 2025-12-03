#include "game_objects/components/shape_component.hpp"

Shape::Shape()
  : Component<Shape>(INVALID_ENTITY_ID)
  {}

Shape::Shape(EntityId entity_id)
  : Component<Shape>(entity_id)
  {}
