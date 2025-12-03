//
// Created by deborah ama on 03/12/2025.
//

#pragma once
#include "Scene.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

class StartMenuScene : public Scene {
public:
    StartMenuScene(sf::Vector2u windowSize);

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

    sf::Vector2u m_windowSize;
};
