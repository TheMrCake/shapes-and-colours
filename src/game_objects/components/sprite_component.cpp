#include "game_objects/components/sprite_component.hpp"

// Local includes
#include "managers/resource_manager.hpp"

Sprite::Sprite()
    : Component<Sprite>(INVALID_ENTITY_ID),
    resource_id(INVALID_RESOURCE_ID) {}

Sprite::Sprite(EntityId entity_id)
    : Component<Sprite>(entity_id),
    resource_id(INVALID_RESOURCE_ID) {}
