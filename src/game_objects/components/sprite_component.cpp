#include "game_objects/components/sprite_component.hpp"

Sprite::Sprite()
    : Component<Sprite>(INVALID_ENTITY_ID) {}

Sprite::Sprite(EntityId entity_id)
    : Component<Sprite>(entity_id) {}
