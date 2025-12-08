#pragma once

// Local includes
#include "game_objects/components/input_component.hpp"
#include "game_objects/components/light_component.hpp"
#include "game_objects/components/physics_component.hpp"
#include "game_objects/components/transform_component.hpp"
#include "game_objects/entity.hpp"
#include "managers/entity_manager.hpp"

using LightCrystal = Entity<Transform, Crystal, Shape, Physics>;
using LightRay = Entity<Transform, Light, Shape>;
using LightEmitter = Entity<Physics, Transform>;
using Player = Entity<Physics, Transform, Input, Sprite>;

inline EntityId create_light_ray(EntityManager& em,
                                 const sf::Vector2u& windowSize,
                                 const sf::Vector2f& dir,
                                 float wavelength = 550.f) {
    EntityId id = em.make_entity<LightRay>();

    auto& transform = *em.get_entity_component<Transform>(id).value();
    transform.transform.position = sf::Vector2f(windowSize.x, 0.f);

    auto& light = *em.get_entity_component<Light>(id).value();
    light.direction = dir;
    light.speed = 400.f;
    light.wavelength = wavelength;
    light.remaining_collisions = Light::max_collisions;

    auto& shape = *em.get_entity_component<Shape>(id).value();
    shape.shape = std::make_unique<sf::RectangleShape>(
        sf::Vector2f(windowSize.x, 6.f)); // long beam
    shape.shape->setFillColor(sf::Color::Yellow);
    shape.shape->setOrigin(0.f, 3.f);
    shape.shape->setPosition(sf::Vector2f(950.f, 0.f));
    shape.visible = true;
    return id;
}
