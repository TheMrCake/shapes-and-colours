#pragma once

// Local includes
#include "box2d/id.h"
#include "game_objects/entity.hpp"

struct Physics : Component<Physics> {
    Physics();
    Physics(EntityId entity_id);

    b2BodyId body_id;
};
