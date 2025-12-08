#include "game_objects/components/physics_component.hpp"

// Local includes
#include "game_objects/entity.hpp"

Physics::Physics()
    : Component<Physics>(INVALID_ENTITY_ID) {}

Physics::Physics(EntityId entity_id)
    : Component<Physics>(entity_id) {}
