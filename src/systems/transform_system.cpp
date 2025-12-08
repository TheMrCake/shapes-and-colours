#include "transform_system.hpp"


TransformSystem::TransformSystem(EntityManager& entity_manager)
    : System(entity_manager) {}

void TransformSystem::update(const float delta_time) {
    ComponentMap<Transform>& transform_component_map =
        entity_manager.get_component_map<Transform>();

    for (auto& [entity_id, transform_component] : transform_component_map) {        
        if (auto component_option =
                entity_manager.get_entity_component<Shape>(entity_id);
            component_option.has_value()) {            
            ComponentWeakPtr<Shape> shape_comp = component_option.value();
            shape_comp->shape->setPosition(transform_component->transform.position);
            shape_comp->shape->setRotation(transform_component->transform.rotation_deg);
            // std::cout << shape_comp->shape->getPosition().x << " " << shape_comp->shape->getPosition().y << std::endl;
        }
        if (auto component_option =
                entity_manager.get_entity_component<Sprite>(entity_id);
            component_option.has_value()) {            
            ComponentWeakPtr<Sprite> sprite_comp = component_option.value();
            sprite_comp->sprite.setPosition(transform_component->transform.position);
            sprite_comp->sprite.setRotation(transform_component->transform.rotation_deg);
        }
    }
}
