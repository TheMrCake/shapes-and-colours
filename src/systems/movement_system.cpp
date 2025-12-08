#include "movement_system.hpp"
#include "box2d/box2d.h"
#include "game_parameters.hpp"
#include "managers/entity_manager.hpp"
#include "utils/b2d_utils.hpp"

MovementSystem::MovementSystem(EntityManager& entity_manager)
    : System(entity_manager) {}

void MovementSystem::update(const float delta_time) {
    ComponentMap<Input>& input_component_map =
        entity_manager.get_component_map<Input>();
    ComponentMap<Physics>& physics_component_map =
        entity_manager.get_component_map<Physics>();

    for (auto& [entity_id, input_component] : input_component_map) {
        if (auto component_option =
                entity_manager.get_entity_component<Physics>(entity_id);
            component_option.has_value()) {
            ComponentWeakPtr<Physics> physics_comp = component_option.value();
            b2Body_SetLinearVelocity(
                physics_comp->body_id,
                delta_time*GameParameters::character_speed*Box2DUtils::sv2_to_bv2(Box2DUtils::invert_height(
                    input_component->input_direction)));
        }
    }
}
