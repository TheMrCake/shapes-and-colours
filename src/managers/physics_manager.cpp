#include "managers/physics_manager.hpp"

// Box2D includes
#include "box2d/box2d.h"
#include "box2d/id.h"
#include "box2d/types.h"

// Local includes
#include "managers/entity_manager.hpp"

PhysicsManager::PhysicsManager(EntityManager& entity_manager)
  : world_id()
  , entity_manager(entity_manager)
  {
  b2WorldDef world_def{};
  world_def.gravity = {0.0f, 0.0f};
  world_def.enableSleep = true;
  
  world_id = b2CreateWorld(&world_def);
}
