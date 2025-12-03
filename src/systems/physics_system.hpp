#pragma once

// Box2D includes
#include "box2d/id.h"

// Local includes
#include "managers/entity_manager.hpp"



class PhysicsSystem {
public:
  PhysicsSystem(EntityManager& entity_manager);

  void update(const float delta_time);

private:
  b2WorldId world_id;

  EntityManager& entity_manager;
};
