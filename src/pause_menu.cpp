//
// Created by deborah ama on 03/12/2025.
//

#include "pause_menu.hpp"
#include "game_scene.hpp"
#include <iostream>

PauseMenuScene::PauseMenuScene(sf::Vector2u windowSize, EntityManager& em, GameScene* gameScene)
    : m_selectedIndex(0), m_resumeSelected(false), m_quitSelected(false),
       m_next(this), windowSize(windowSize), entityManager(em), gameScene(gameScene)
{
    if (!m_font.loadFromFile("resources/ScienceGothic.ttf")){
        std::cerr << "Failed to load font\n";
    }

    // Title
    m_title.setFont(m_font);
    m_title.setString("Paused");
    m_title.setCharacterSize(56);
    m_title.setFillColor(sf::Color::White);
    m_title.setPosition(windowSize.x / 2.f - m_title.getGlobalBounds().width / 2.f,
                        windowSize.y / 4.f);

    // Resume
    m_resumeText.setFont(m_font);
    m_resumeText.setString("Resume");
    m_resumeText.setCharacterSize(34);
    m_resumeText.setFillColor(sf::Color::Yellow);
    m_resumeText.setPosition(windowSize.x / 2.f - m_resumeText.getGlobalBounds().width / 2.f,
                             windowSize.y / 2.f);

    // Quit
    m_quitText.setFont(m_font);
    m_quitText.setString("Quit");
    m_quitText.setCharacterSize(34);
    m_quitText.setFillColor(sf::Color::White);
    m_quitText.setPosition(windowSize.x / 2.f - m_quitText.getGlobalBounds().width / 2.f,
                           windowSize.y / 2.f + 60.f);
}

void PauseMenuScene::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down) {
            m_selectedIndex = 1 - m_selectedIndex;
            updateSelection();
        }
        else if (event.key.code == sf::Keyboard::Enter) {
            if (m_selectedIndex == 0) {
                m_resumeSelected = true;
            } else {
                m_quitSelected = true;
            }
        }
        //std::cout << "Enter pressed, resumeSelected = " << m_resumeSelected << "\n";
    }
}

void PauseMenuScene::update(float) {
    if (m_resumeSelected) {
        m_resumeSelected = false;
//        m_next = new GameScene(windowSize, entityManager); // back to gameplay
    }
    if (m_quitSelected) {
        m_quitSelected = false;
        m_next = nullptr; // exit game
    }
}

void PauseMenuScene::render(sf::RenderWindow& window) {
    sf::RectangleShape overlay(sf::Vector2f(window.getSize().x, window.getSize().y));
    overlay.setFillColor(sf::Color(0, 0, 0, 150));
    window.draw(overlay);

    window.draw(m_title);
    window.draw(m_resumeText);
    window.draw(m_quitText);
}

Scene* PauseMenuScene::nextScene() {
    if (m_resumeSelected) {
        gameScene->resumeGame();

        return gameScene; // return the same instance

    }
    if (m_quitSelected) {
        // handle quitting to start menu or exit
        //std::cout << "Enter pressed, quiteSelcted = " << m_resumeSelected << "\n";

    }
    return this;
    std::cout << "Enter pressed, resumeSelected = " << m_resumeSelected << "\n";
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

