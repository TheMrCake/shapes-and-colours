//
// Created by deborah ama on 03/12/2025.
//

#pragma once
#include "scene.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/ConvexShape.hpp>

#include "managers/entity_manager.hpp"
#include "systems/light_system.hpp"

class GameScene : public Scene {
public:
    GameScene(sf::Vector2u windowSize, EntityManager &em);

    void handleEvent(const sf::Event &event) override;
    void update(float dt) override;
    void render(sf::RenderWindow &window) override;
    Scene *nextScene() override;

    void resumeGame();

    bool isPaused() const { return paused; };

private:
    EntityManager &entityManager;
    EntityId beamId;
    bool paused;

    // add bulbling
    sf::Texture bulbTexture;
    sf::Sprite bulbSprite;
    Scene *m_next;
    sf::Vector2u windowSize;

    LightSystem lightSystem;
    // crystal
    sf::ConvexShape crystalShape;
    // border
    sf::RectangleShape border;
    sf::Clock glowClock;
};
