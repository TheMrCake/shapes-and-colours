#pragma once


// Local includes
#include "systems/system.hpp"


class TransformSystem : System {
public:   
    TransformSystem(EntityManager& entity_manager);

    virtual void update(const float dt) override;
};
