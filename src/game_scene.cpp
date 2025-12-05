//
// Created by deborah ama on 03/12/2025.
//

#include "game_scene.hpp"
#include "pause_menu.hpp"
#include <cmath>
#include <iostream>
#include <objc/objc.h>

#include "game_objects/entities.hpp"
#include "managers/entity_manager.hpp"


GameScene::GameScene(sf::Vector2u windowSize, EntityManager& em)
    : m_next(this), windowSize(windowSize), entityManager(em), lightSystem(em)
{
    // bulbling
    if (!bulbTexture.loadFromFile("resources/bulbling.png")) {
        std::cerr << "Failed to load bulb image\n";
    }
    bulbSprite.setTexture(bulbTexture);
    bulbSprite.setOrigin(bulbTexture.getSize().x / 2.f, bulbTexture.getSize().y / 2.f);
    bulbSprite.setPosition(windowSize.x / 2.f, windowSize.y / 2.f);
    bulbSprite.setScale(0.15f,0.15f);

    // crystal
    crystalShape.setPointCount(6);
    crystalShape.setPoint(0, sf::Vector2f(0.f, -50.f));   // top point
    crystalShape.setPoint(1, sf::Vector2f(30.f, -20.f));  // upper right
    crystalShape.setPoint(2, sf::Vector2f(30.f, 20.f));   // lower right
    crystalShape.setPoint(3, sf::Vector2f(0.f, 50.f));    // bottom point
    crystalShape.setPoint(4, sf::Vector2f(-30.f, 20.f));  // lower left
    crystalShape.setPoint(5, sf::Vector2f(-30.f, -20.f)); // upper left

    crystalShape.setFillColor(sf::Color(101, 96, 98));   // icy blue
    crystalShape.setOutlineColor(sf::Color(129, 121, 125));
    crystalShape.setOutlineThickness(2.f);
    crystalShape.setPosition(windowSize.x / 3.f, windowSize.y / 2.f);

    beamId = create_light_ray(entityManager, windowSize, sf::Vector2f(-1.f, 1.f));

    // Border
    float thickness = 10.f;

    border.setSize(sf::Vector2f(windowSize.x - 20.f, windowSize.y - 20.f));
    border.setPosition(10.f, 10.f);
    border.setFillColor(sf::Color::Transparent); // no fill
    border.setOutlineThickness(10.f);
    border.setOutlineColor(sf::Color(80, 100, 150));

}

void GameScene::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        m_next = new PauseMenuScene(windowSize, entityManager,this);
    }

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::A) {
            auto& lights = entityManager.get_component_map<Light>();
            for (auto& [id, lightPtr] : lights) {
                lightPtr->rotatingLeft = true;
            }
        }
        if (event.key.code == sf::Keyboard::D) {
            auto& lights = entityManager.get_component_map<Light>();
            for (auto& [id, lightPtr] : lights) {
                lightPtr->rotatingRight = true;
            }
        }
    }
    if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::A) {
            auto& lights = entityManager.get_component_map<Light>();
            for (auto& [id, lightPtr] : lights) {
                lightPtr->rotatingLeft = false;
            }
        }
        if (event.key.code == sf::Keyboard::D) {
            auto& lights = entityManager.get_component_map<Light>();
            for (auto& [id, lightPtr] : lights) {
                lightPtr->rotatingRight = false;
            }
        }
    }

    // auto& light = *entityManager.get_entity_component<Light>(beamId).value();
    // light.rotatingLeft = true;  // or false depending on input


}

void GameScene::update(float dt) {
    // controls - arrow keys
    float speed = 200.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) bulbSprite.move(-speed * dt, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) bulbSprite.move(speed * dt, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) bulbSprite.move(0, -speed * dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) bulbSprite.move(0, speed * dt);


    if (auto beamLight = entityManager.get_entity_component<Light>(beamId)) {
        (*beamLight)->rotatingLeft  = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
        (*beamLight)->rotatingRight = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
    }

    // border pulse effect
    float t = glowClock.getElapsedTime().asSeconds();
    int alpha = 100 + static_cast<int>(100 * std::sin(t * 2.f));

    sf::Color glowColour(80, 100, 150, alpha);
    border.setOutlineColor(glowColour);

    lightSystem.update(dt);


}

void GameScene::resumeGame() {
    paused = false;
    if (auto shapeOpt = entityManager.get_entity_component<Shape>(beamId)) {
        (*shapeOpt)->visible = true;
    }
}

void GameScene::render(sf::RenderWindow& window) {
    window.draw(bulbSprite);
    window.draw(border);
    window.draw(crystalShape);

    auto& shapes = entityManager.get_component_map<Shape>();
    for (auto& [id, shapePtr] : shapes) {
        if (shapePtr->shape) {
            window.draw(*shapePtr->shape);
        }
    }
}

Scene* GameScene::nextScene() { return m_next; }
