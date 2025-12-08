//
// Created by deborah ama on 03/12/2025.
//

#pragma once

// SFML includes
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/ConvexShape.hpp>

// Local includes
#include "game_system.hpp"
#include "scene.hpp"

class GameScene : public Scene {
public:
    GameScene(GameSystem& game_system);

    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
    Scene* nextScene() override;

    void resumeGame();
private:
    GameSystem& game_system;

    Scene* m_next;
};
