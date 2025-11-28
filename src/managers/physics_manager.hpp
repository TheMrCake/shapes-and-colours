#pragma once

// Box2D includes
#include "box2d/id.h"

// Local includes
#include "managers/entity_manager.hpp"



class PhysicsManager {
public:
  PhysicsManager(EntityManager& entity_manager);

private:
  b2WorldId world_id;

  EntityManager& entity_manager;
};
