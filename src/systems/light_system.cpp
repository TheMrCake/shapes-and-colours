//
// Created by deborah ama on 05/12/2025.
//

#include "systems/light_system.hpp"
#include "game_objects/components/light_component.hpp"
#include "game_objects/components/transform_component.hpp"
#include "game_objects/components/crystal_component.hpp"

#include <cmath>
#include <iostream>

void LightSystem::update(float dt) {
    auto& rays = entity_manager.get_component_map<Light>();
    for (auto& [id, rayPtr] : rays) {
        Light& ray = *rayPtr;


        if (auto shapeOpt = entity_manager.get_entity_component<Shape>(id)) {
            Shape* rayShape = *shapeOpt;

            // ⬇️ Skip updating if it's hidden
            if (!rayShape->visible) continue;
        }

        float currentAngle = std::atan2(ray.direction.y, ray.direction.x);

        float rotationSpeedDeg = 90.f; // degrees per second
        float rotationSpeedRad = rotationSpeedDeg * M_PI / 180.f;

        if (ray.rotatingLeft)  currentAngle -= rotationSpeedRad * dt;
        if (ray.rotatingRight) currentAngle += rotationSpeedRad * dt;

        ray.direction = { std::cos(currentAngle), std::sin(currentAngle) };
        if (auto transformOpt = entity_manager.get_entity_component<Transform>(id)) {
            Transform* transform = *transformOpt;

            if (auto shapeOpt = entity_manager.get_entity_component<Shape>(id)) {
                Shape* shapeComp = *shapeOpt;
                if (shapeComp->shape) {
                    if (auto* rect = dynamic_cast<sf::RectangleShape*>(shapeComp->shape.get())) {
                        rect->setPosition(transform->transform.position);

                        float angleDeg = std::atan2(ray.direction.y, ray.direction.x) * 180.f / M_PI;
                        rect->setRotation(angleDeg);

                        rect->setSize(sf::Vector2f(950.f, 6.f));
                    }
                }
            }
        }
    }

}
