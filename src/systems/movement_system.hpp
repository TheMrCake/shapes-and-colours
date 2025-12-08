#pragma once

// Local includes
#include "systems/system.hpp"


class MovementSystem : System {
public:   
    MovementSystem(EntityManager& entity_manager);

    virtual void update(const float dt) override;
};
