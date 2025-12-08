//
// Created by deborah ama on 03/12/2025.
//
#pragma once

// SFML includes
#include <SFML/Graphics.hpp>

// Local includes
#include "game_system.hpp"
#include "scene.hpp"

class StartMenuScene : public Scene {
public:
    StartMenuScene(GameSystem& game_system);

    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
    Scene* nextScene() override;

private:
    sf::Font m_font;
    sf::Text m_title;
    sf::Text m_startText;
    sf::Text m_quitText;

    int m_selectedIndex;
    Scene* m_next;

    GameSystem& game_system;
};
