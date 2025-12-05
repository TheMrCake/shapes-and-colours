#include "SFML/Window/Event.hpp"

// SFML includes
#include <SFML/Graphics.hpp>

// Local includes
#include "game_parameters.hpp"
#include "game_system.hpp"
#include "start_menu_scene.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Scene System");
    window.setFramerateLimit(60);

    GameSystem game_system{window.getSize()};
    sf::Clock clock;

    while (window.isOpen() && game_system.running) {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            game_system.handle_event(event);
        }

        // Update game
        float dt = clock.restart().asSeconds();
        game_system.update(dt);

        // Check if we should exit
        if (!game_system.running) {
            window.close();
            break;
        }

        // Render
        window.clear(sf::Color::Black);
        game_system.render(window);
        window.display();
    }

    return 0;
}


