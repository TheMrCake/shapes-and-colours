//
// Created by deborah ama on 03/12/2025.
//

#include "pause_menu.hpp"
#include "game_scene.hpp"
#include "managers/entity_manager.hpp"
#include "start_menu_scene.hpp"
#include <iostream>

PauseMenuScene::PauseMenuScene(sf::Vector2u windowSize, EntityManager &em,
                               GameScene *gameScene)
    : m_selectedIndex(0),
      m_resumeSelected(false),
      m_quitSelected(false),
      m_next(this),
      windowSize(windowSize),
      entityManager(em),
      gameScene(gameScene) {
    // Load font
    if (!m_font.loadFromFile("resources/ScienceGothic.ttf")) {
        std::cerr << "Failed to load font\n";
    }

    // Setup title
    m_title.setFont(m_font);
    m_title.setString("PAUSED");
    m_title.setCharacterSize(56);
    m_title.setFillColor(sf::Color::White);
    sf::FloatRect titleBounds = m_title.getLocalBounds();
    m_title.setOrigin(titleBounds.width / 2.f, titleBounds.height / 2.f);
    m_title.setPosition(windowSize.x / 2.f, windowSize.y / 4.f);

    // Setup resume button
    m_resumeText.setFont(m_font);
    m_resumeText.setString("Resume");
    m_resumeText.setCharacterSize(34);
    m_resumeText.setFillColor(sf::Color::Yellow);
    sf::FloatRect resumeBounds = m_resumeText.getLocalBounds();
    m_resumeText.setOrigin(resumeBounds.width / 2.f, resumeBounds.height / 2.f);
    m_resumeText.setPosition(windowSize.x / 2.f, windowSize.y / 2.f);

    // Setup quit button
    m_quitText.setFont(m_font);
    m_quitText.setString("Quit to Menu");
    m_quitText.setCharacterSize(34);
    m_quitText.setFillColor(sf::Color::White);
    sf::FloatRect quitBounds = m_quitText.getLocalBounds();
    m_quitText.setOrigin(quitBounds.width / 2.f, quitBounds.height / 2.f);
    m_quitText.setPosition(windowSize.x / 2.f, windowSize.y / 2.f + 70.f);

    std::cout << "PauseMenuScene created\n";
}

void PauseMenuScene::handleEvent(const sf::Event &event) {
    std::cout << "PauseMenu handleEvent called, type: " << event.type << "\n";

    if (event.type == sf::Event::KeyPressed) {
        std::cout << "Key pressed: " << event.key.code << "\n";

        // Navigate menu
        if (event.key.code == sf::Keyboard::Up ||
            event.key.code == sf::Keyboard::Down) {
            m_selectedIndex = 1 - m_selectedIndex;
            updateSelection();
            std::cout << "Selection changed to: " << m_selectedIndex << "\n";
        }
        // Select option
        else if (event.key.code == sf::Keyboard::Return) {
            std::cout << "Return pressed, selected index: " << m_selectedIndex
                      << "\n";
            if (m_selectedIndex == 0) {
                m_resumeSelected = true;
                std::cout << "Resume selected!\n";
            } else {
                m_quitSelected = true;
                std::cout << "Quit selected!\n";
            }
        }
        // ESC also resumes
        else if (event.key.code == sf::Keyboard::Escape) {
            m_resumeSelected = true;
            std::cout << "ESC pressed, resuming!\n";
        }
    }
}

void PauseMenuScene::update(float dt) {
    // Check flags immediately in update
    if (m_resumeSelected) {
        std::cout << "Update: Resume flag is true\n";
    }
    if (m_quitSelected) {
        std::cout << "Update: Quit flag is true\n";
    }
}

void PauseMenuScene::render(sf::RenderWindow &window) {
    // Draw the game scene in the background (frozen)
    if (gameScene) {
        gameScene->render(window);
    }

    // Draw semi-transparent overlay
    sf::RectangleShape overlay(sf::Vector2f(windowSize.x, windowSize.y));
    overlay.setFillColor(sf::Color(0, 0, 0, 180));
    window.draw(overlay);

    // Draw pause menu text
    window.draw(m_title);
    window.draw(m_resumeText);
    window.draw(m_quitText);
}

Scene *PauseMenuScene::nextScene() {
    std::cout << "nextScene called - resumeSelected: " << m_resumeSelected
              << ", quitSelected: " << m_quitSelected << "\n";

    if (m_resumeSelected) {
        std::cout << "Resuming game!\n";
        m_resumeSelected = false;
        if (gameScene) {
            gameScene->resumeGame();
            return gameScene;
        }
    }

    if (m_quitSelected) {
        std::cout << "Quitting to menu!\n";
        m_quitSelected = false;

        auto &lights = entityManager.get_component_map<Light>();
        std::vector<EntityId> entitiesToRemove;
        for (auto &[id, lightPtr] : lights) {
            entitiesToRemove.push_back(id);
        }
        for (EntityId id : entitiesToRemove) {
            entityManager.remove_entity(id);
        }

        return new StartMenuScene(windowSize, entityManager);
    }

    return this;
}

void PauseMenuScene::updateSelection() {
    if (m_selectedIndex == 0) {
        m_resumeText.setFillColor(sf::Color::Yellow);
        m_quitText.setFillColor(sf::Color::White);
    } else {
        m_resumeText.setFillColor(sf::Color::White);
        m_quitText.setFillColor(sf::Color::Yellow);
    }
}