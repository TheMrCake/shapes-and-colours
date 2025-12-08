//
// Created by deborah ama on 03/12/2025.
//

// STD includes
#include <cassert>
#include <cmath>
#include <iostream>

// Local Includes
#include "game_scene.hpp"
#include "game_system.hpp"
#include "pause_menu.hpp"

GameScene::GameScene(GameSystem& game_system)
    : game_system(game_system),
      m_next(this) {
    game_system.start_game();         
}

void GameScene::handleEvent(const sf::Event& event) {

    // Handle pause/unpause
    if (event.type == sf::Event::KeyPressed &&
        event.key.code == sf::Keyboard::Escape) {
        if (!game_system.in_game) {
            std::cout << "Pausing game...\n";
            game_system.in_game = true;

            m_next = new PauseMenuScene(game_system, this);
        }
        return;
    }

    // // Don't process game controls when paused
    // if (paused) {
    //     std::cout << "Game is paused, ignoring input\n";
    //     return;
    // }

    // // Handle light rotation controls
    // if (event.type == sf::Event::KeyPressed) {
    //     if (event.key.code == sf::Keyboard::A) {
    //         auto& lights = entity_manager.get_component_map<Light>();
    //         for (auto& [id, lightPtr] : lights) {
    //             lightPtr->rotatingLeft = true;
    //         }
    //     }
    //     if (event.key.code == sf::Keyboard::D) {
    //         auto& lights = entity_manager.get_component_map<Light>();
    //         for (auto& [id, lightPtr] : lights) {
    //             lightPtr->rotatingRight = true;
    //         }
    //     }
    // }

    // if (event.type == sf::Event::KeyReleased) {
    //     if (event.key.code == sf::Keyboard::A) {
    //         auto& lights = entity_manager.get_component_map<Light>();
    //         for (auto& [id, lightPtr] : lights) {
    //             lightPtr->rotatingLeft = false;
    //         }
    //     }
    //     if (event.key.code == sf::Keyboard::D) {
    //         auto& lights = entity_manager.get_component_map<Light>();
    //         for (auto& [id, lightPtr] : lights) {
    //             lightPtr->rotatingRight = false;
    //         }
    //     }
    // }
}

void GameScene::update(float dt) {
    // // Border glow effect
    // float t = glowClock.getElapsedTime().asSeconds();
    // int alpha = 100 + static_cast<int>(100 * std::sin(t * 2.f));
    // sf::Color glowColour(80, 100, 150, alpha);
    // border.setOutlineColor(glowColour);
}

void GameScene::resumeGame() {
    m_next = this;
}

void GameScene::render(sf::RenderWindow& window) {}

Scene* GameScene::nextScene() { return m_next; }
