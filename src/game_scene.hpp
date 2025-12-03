//
// Created by deborah ama on 03/12/2025.
//

#pragma once
#include "Scene.hpp"
#include <SFML/Graphics.hpp>

class GameScene : public Scene {
public:
    GameScene(sf::Vector2u windowSize);

    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
    Scene* nextScene() override;

private:
    // add bulbling
    sf::Texture bulbTexture;
    sf::Sprite bulbSprite;
    Scene* m_next;
    sf::Vector2u windowSize;

    //border
    sf::RectangleShape border;
    sf::Clock glowClock;
};
