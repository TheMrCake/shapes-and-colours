//
// Created by deborah ama on 03/12/2025.
//
#include "start_menu_scene.hpp"

// SFML includes
#include <SFML/Graphics.hpp>

// Local includes
#include "game_scene.hpp"
#include "managers/entity_manager.hpp"

StartMenuScene::StartMenuScene(sf::Vector2u windowSize, EntityManager& em)
    : m_selectedIndex(0), m_next(this), m_windowSize(windowSize), entityManager(em)
{
    if (!m_font.loadFromFile("resources/ScienceGothic.ttf")){
        std::cerr << "Failed to load font\n";
    }
    // m_font.loadFromFile("/Users/amade/CLionProjects/shapes-and-colours/resources/ScienceGothic.ttf");


    m_title.setFont(m_font);
    m_title.setString("Start Menu");
    m_title.setCharacterSize(48);
    m_title.setFillColor(sf::Color::White);
    m_title.setPosition(windowSize.x / 2.f - m_title.getGlobalBounds().width / 2.f,
                        windowSize.y / 4.f);

    m_startText.setFont(m_font);
    m_startText.setString("Start Game");
    m_startText.setCharacterSize(32);
    m_startText.setFillColor(sf::Color::Yellow);
    m_startText.setPosition(windowSize.x / 2.f - m_startText.getGlobalBounds().width / 2.f,
                            windowSize.y / 2.f);

    m_quitText.setFont(m_font);
    m_quitText.setString("Quit");
    m_quitText.setCharacterSize(32);
    m_quitText.setFillColor(sf::Color::White);
    m_quitText.setPosition(windowSize.x / 2.f - m_quitText.getGlobalBounds().width / 2.f,
                           windowSize.y / 2.f + 60.f);
}

void StartMenuScene::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down) {
            m_selectedIndex = 1 - m_selectedIndex;
            m_startText.setFillColor(m_selectedIndex == 0 ? sf::Color::Yellow : sf::Color::White);
            m_quitText.setFillColor(m_selectedIndex == 1 ? sf::Color::Yellow : sf::Color::White);
        }
        else if (event.key.code == sf::Keyboard::Enter) {
            if (m_selectedIndex == 0) {
                m_next = new GameScene(m_windowSize, entityManager); // start gameplay
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
