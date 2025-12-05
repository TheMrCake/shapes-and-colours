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
    : m_next(this), windowSize(windowSize), entityManager(em), lightSystem(em), paused(false)
{
    std::cout << "GameScene constructor called\n";

    // Load bulb texture
    if (!bulbTexture.loadFromFile("resources/bulbling.png")) {
        std::cerr << "Failed to load bulb image\n";
    }
    bulbSprite.setTexture(bulbTexture);
    bulbSprite.setOrigin(bulbTexture.getSize().x / 2.f, bulbTexture.getSize().y / 2.f);
    bulbSprite.setPosition(windowSize.x / 2.f, windowSize.y / 2.f);
    bulbSprite.setScale(0.15f, 0.15f);

    // Setup crystal
    crystalShape.setPointCount(6);
    crystalShape.setPoint(0, sf::Vector2f(0.f, -50.f));
    crystalShape.setPoint(1, sf::Vector2f(30.f, -20.f));
    crystalShape.setPoint(2, sf::Vector2f(30.f, 20.f));
    crystalShape.setPoint(3, sf::Vector2f(0.f, 50.f));
    crystalShape.setPoint(4, sf::Vector2f(-30.f, 20.f));
    crystalShape.setPoint(5, sf::Vector2f(-30.f, -20.f));

    crystalShape.setFillColor(sf::Color(101, 96, 98));
    crystalShape.setOutlineColor(sf::Color(129, 121, 125));
    crystalShape.setOutlineThickness(2.f);
    crystalShape.setPosition(windowSize.x / 3.f, windowSize.y / 2.f);

    // Create light beam
    beamId = create_light_ray(entityManager, windowSize, sf::Vector2f(-1.f, 1.f));
    std::cout << "Light beam created with ID: " << beamId << "\n";

    // Verify the light beam was created
    if (auto lightOpt = entityManager.get_entity_component<Light>(beamId)) {
        std::cout << "Light component found!\n";
    } else {
        std::cout << "ERROR: Light component NOT found!\n";
    }

    if (auto shapeOpt = entityManager.get_entity_component<Shape>(beamId)) {
        std::cout << "Shape component found, visible: " << (*shapeOpt)->visible << "\n";
    } else {
        std::cout << "ERROR: Shape component NOT found!\n";
    }

    // Setup border
    border.setSize(sf::Vector2f(windowSize.x - 20.f, windowSize.y - 20.f));
    border.setPosition(10.f, 10.f);
    border.setFillColor(sf::Color::Transparent);
    border.setOutlineThickness(10.f);
    border.setOutlineColor(sf::Color(80, 100, 150));
}

void GameScene::handleEvent(const sf::Event& event) {
    std::cout << "GameScene handleEvent, paused: " << paused << "\n";

    // Handle pause/unpause
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        if (!paused) {
            std::cout << "Pausing game...\n";
            paused = true;

            // Hide all light beam shapes
            auto& lights = entityManager.get_component_map<Light>();
            std::cout << "Number of lights to hide: " << lights.size() << "\n";
            for (auto& [id, lightPtr] : lights) {
                if (auto shapeOpt = entityManager.get_entity_component<Shape>(id)) {
                    (*shapeOpt)->visible = false;
                    std::cout << "Hidden light shape for entity " << id << "\n";
                }
            }
            m_next = new PauseMenuScene(windowSize, entityManager, this);
        }
        return;
    }

    // Don't process game controls when paused
    if (paused) {
        std::cout << "Game is paused, ignoring input\n";
        return;
    }

    // Handle light rotation controls
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
}

void GameScene::update(float dt) {
    // Don't update game when paused
    if (paused) return;

    // Bulb movement controls
    float speed = 200.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) bulbSprite.move(-speed * dt, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) bulbSprite.move(speed * dt, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) bulbSprite.move(0, -speed * dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) bulbSprite.move(0, speed * dt);

    // Update light rotation
    if (auto beamLight = entityManager.get_entity_component<Light>(beamId)) {
        (*beamLight)->rotatingLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
        (*beamLight)->rotatingRight = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
    }

    // Border glow effect
    float t = glowClock.getElapsedTime().asSeconds();
    int alpha = 100 + static_cast<int>(100 * std::sin(t * 2.f));
    sf::Color glowColour(80, 100, 150, alpha);
    border.setOutlineColor(glowColour);
}

void GameScene::resumeGame() {
    std::cout << "Resuming game...\n";
    paused = false;
    m_next = this;

    // Show all light beam shapes again
    auto& lights = entityManager.get_component_map<Light>();
    std::cout << "Number of lights to show: " << lights.size() << "\n";
    for (auto& [id, lightPtr] : lights) {
        if (auto shapeOpt = entityManager.get_entity_component<Shape>(id)) {
            (*shapeOpt)->visible = true;
            std::cout << "Showed light shape for entity " << id << "\n";
        }
    }
}

void GameScene::render(sf::RenderWindow& window) {
    // Draw game objects
    window.draw(bulbSprite);
    window.draw(border);
    window.draw(crystalShape);

    // Draw all visible shapes (including light beams when not paused)
    auto& shapes = entityManager.get_component_map<Shape>();
    int visibleCount = 0;
    for (auto& [id, shapePtr] : shapes) {
        if (shapePtr->shape && shapePtr->visible) {
            window.draw(*shapePtr->shape);
            visibleCount++;
        }
    }
    // Only log occasionally to avoid spam
    static int frameCount = 0;
    if (frameCount++ % 60 == 0) {
        std::cout << "Rendering " << visibleCount << " visible shapes out of " << shapes.size() << " total\n";
    }
}

Scene* GameScene::nextScene() {
    return m_next;
}