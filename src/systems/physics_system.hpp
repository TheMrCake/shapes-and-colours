#pragma once

// Box2D includes
#include "box2d/id.h"

// Local includes
#include "managers/entity_manager.hpp"
#include "systems/system.hpp"

class PhysicsSystem : System {
public:
    PhysicsSystem(EntityManager& entity_manager);

    virtual void update(const float delta_time) override;

    const b2WorldId get_world_id();
private:
    b2WorldId world_id;
};
