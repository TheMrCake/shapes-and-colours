#include "game_objects/components/collision_component.hpp"

// Local includes
#include "game_objects/entity.hpp"



Collision::Collision()
  : Component<Collision>(INVALID_ENTITY_ID)
  {}

Collision::Collision(EntityId entity_id)
  : Component<Collision>(entity_id)
  {}

void Collision::update_impl(const float delta_time) {
  
}
