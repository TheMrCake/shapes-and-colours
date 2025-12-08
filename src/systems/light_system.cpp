//
// Created by deborah ama on 05/12/2025.
//

#include "systems/light_system.hpp"

// STD includes
#include <cmath>

// Local includes
#include "game_objects/components/light_component.hpp"
#include "game_objects/components/transform_component.hpp"
#include "utils/b2d_utils.hpp"

void LightSystem::update(float dt) {
    auto& rays = entity_manager.get_component_map<Light>();
    for (auto& [id, ray_ptr] : rays) {
        Light& ray = *ray_ptr;

        if (auto shape_opt = entity_manager.get_entity_component<Shape>(id)) {
            Shape* ray_shape = *shape_opt;

            // Skip updating if it's hidden
            if (!ray_shape->visible)
                continue;
        }

        float current_angle = std::atan2(ray.direction.y, ray.direction.x);

        float rotation_speed_deg = 90.f; // degrees per second
        float rotation_speed_rad = Box2DUtils::deg_to_rad(rotation_speed_deg);

        if (ray.rotatingLeft)
            current_angle -= rotation_speed_rad * dt;
        if (ray.rotatingRight)
            current_angle += rotation_speed_rad * dt;

        ray.direction = {std::cos(current_angle), std::sin(current_angle)};
        if (auto transformOpt =
                entity_manager.get_entity_component<Transform>(id)) {
            Transform* transform = *transformOpt;

            if (auto shapeOpt =
                    entity_manager.get_entity_component<Shape>(id)) {
                Shape* shapeComp = *shapeOpt;
                if (shapeComp->shape) {
                    if (auto* rect = dynamic_cast<sf::RectangleShape*>(
                            shapeComp->shape.get())) {
                        rect->setPosition(transform->transform.position);

                        float angleDeg =
                            std::atan2(ray.direction.y, ray.direction.x) *
                            180.f / M_PI;
                        rect->setRotation(angleDeg);

                        rect->setSize(sf::Vector2f(950.f, 6.f));
                    }
                }
            }
        }
    }
}
