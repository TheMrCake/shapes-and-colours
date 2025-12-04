//
// Created by deborah ama on 03/12/2025.
//

#pragma once
#include "scene.hpp"
#include <SFML/Graphics.hpp>

class PauseMenuScene : public Scene {
public:
    PauseMenuScene(sf::Vector2u windowSize);

    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
    Scene* nextScene() override;

private:
    sf::Font m_font;
    sf::Text m_title;
    sf::Text m_resumeText;
    sf::Text m_quitText;

    int m_selectedIndex;
    bool m_resumeSelected;
    bool m_quitSelected;

    Scene* m_next;
    sf::Vector2u windowSize;

    void updateSelection();
};


