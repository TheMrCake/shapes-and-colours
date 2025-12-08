//
// Created by deborah ama on 03/12/2025.
//
#include "start_menu_scene.hpp"

// SFML includes
#include <SFML/Graphics.hpp>
#include <iostream>

// Local includes
#include "game_parameters.hpp"
#include "game_scene.hpp"
#include "game_system.hpp"

StartMenuScene::StartMenuScene(GameSystem& game_system)
    : m_selectedIndex(0),
      m_next(this),
      game_system(game_system) {
    if (!m_font.loadFromFile("resources/ScienceGothic.ttf")) {
        std::cerr << "Failed to load font\n";
    }

    m_title.setFont(m_font);
    m_title.setString("Start Menu");
    m_title.setCharacterSize(48);
    m_title.setFillColor(sf::Color::White);
    m_title.setPosition(GameParameters::game_width / 2.f -
                            m_title.getGlobalBounds().width / 2.f,
                        GameParameters::game_height / 4.f);

    m_startText.setFont(m_font);
    m_startText.setString("Start Game");
    m_startText.setCharacterSize(32);
    m_startText.setFillColor(sf::Color::Yellow);
    m_startText.setPosition(GameParameters::game_width / 2.f -
                                m_startText.getGlobalBounds().width / 2.f,
                            GameParameters::game_height / 2.f);

    m_quitText.setFont(m_font);
    m_quitText.setString("Quit");
    m_quitText.setCharacterSize(32);
    m_quitText.setFillColor(sf::Color::White);
    m_quitText.setPosition(GameParameters::game_width / 2.f -
                               m_quitText.getGlobalBounds().width / 2.f,
                           GameParameters::game_height / 2.f + 60.f);
}

void StartMenuScene::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up ||
            event.key.code == sf::Keyboard::Down) {
            m_selectedIndex = 1 - m_selectedIndex;
            m_startText.setFillColor(m_selectedIndex == 0 ? sf::Color::Yellow
                                                          : sf::Color::White);
            m_quitText.setFillColor(m_selectedIndex == 1 ? sf::Color::Yellow
                                                         : sf::Color::White);
        } else if (event.key.code == sf::Keyboard::Enter) {
            if (m_selectedIndex == 0) {
                m_next = new GameScene(game_system); // start gameplay
            } else {
                m_next = nullptr; // exit
            }
        }
    }
}

void StartMenuScene::update(float) {}

void StartMenuScene::render(sf::RenderWindow& window) {
    window.draw(m_title);
    window.draw(m_startText);
    window.draw(m_quitText);
}

Scene* StartMenuScene::nextScene() { return m_next; }
