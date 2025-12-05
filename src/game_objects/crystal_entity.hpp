//
// Created by deborah ama on 04/12/2025.
//


#pragma once
#include "entity.hpp"
#include "managers/entity_manager.hpp"
#include "components/crystal_component.hpp"
#include "components/transform_component.hpp"
#include "components/sprite_component.hpp"
#include "components/physics_component.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <box2d/box2d.h>

constexpr float SCALE = 30.f;

inline EntityId create_crystal(EntityManager& em, sf::Vector2f position, sf::Texture& texture, b2World& world) {
    EntityId id = em.make_entity();

    // Crystal gameplay data
    em.add_component<Crystal>(id, Crystal(id));

    // Transform
    em.add_component<Transform>(id, Transform(id));
    auto& t = em.get_component<Transform>(id);
    t.position = position;

    // Sprite
    em.add_component<Sprite>(id, Sprite(id));
    auto& s = em.get_component<Sprite>(id);
    s.sprite.setTexture(texture);
    s.sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
    s.sprite.setPosition(position);

    // Physics body (static)
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(position.x / SCALE, position.y / SCALE);
    b2Body* body = world.CreateBody(&bodyDef);

    b2PolygonShape box;
    box.SetAsBox((texture.getSize().x / 2.f) / SCALE,
                 (texture.getSize().y / 2.f) / SCALE);
    body->CreateFixture(&box, 0.0f);

    em.add_component<Physics>(id, Physics(id, body));

    return id;
}