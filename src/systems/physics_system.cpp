#include "systems/physics_system.hpp"

// Box2D includes
#include "box2d/box2d.h"
#include "box2d/id.h"
#include "box2d/types.h"

// Local includes
#include "utils/b2d_utils.hpp"
#include "game_objects/components/physics_component.hpp"
#include "game_objects/components/transform_component.hpp"
#include "managers/entity_manager.hpp"
#include "game_parameters.hpp"

PhysicsSystem::PhysicsSystem(EntityManager& entity_manager)
  : System(entity_manager)
  , world_id()
  {
  b2WorldDef world_def = b2DefaultWorldDef();
  world_def.gravity = {0.0f, 0.0f};
  world_def.enableSleep = true;
  
  world_id = b2CreateWorld(&world_def);
}



void PhysicsSystem::update(const float delta_time) {
  b2World_Step(world_id, GameParameters::physics_time_step, GameParameters::physics_sub_step_count);

  ComponentMap<Physics>& physics_component_map = entity_manager.get_component_map<Physics>();
  ComponentMap<Transform>& transform_component_map = entity_manager.get_component_map<Transform>();

  for (auto& [entity_id, physics_component] : physics_component_map) {
    if (
      auto component_option = entity_manager.get_entity_component<Transform>(entity_id);
      component_option.has_value()
      ) {
      ComponentWeakPtr<Transform> transform_component = component_option.value();

      const b2Transform b2_transform = b2Body_GetTransform(physics_component->body_id);
      transform_component->transform = Box2DUtils::btransform_to_transform_info(b2_transform);  
    }
  }
}
