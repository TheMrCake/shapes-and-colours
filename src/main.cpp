#include "SFML/Window/Event.hpp"

#include "game_parameters.hpp"
#include "game_system.hpp"

// int main() {
//   // Create window
//   sf::RenderWindow window(sf::VideoMode({GameParameters::game_width, GameParameters::game_height}), "Shapes and Colours");
//   GameSystem game_system{};
//   game_system.init();
//
//   sf::Clock clock = sf::Clock();
//
//   // Initialise and load
//   while(window.isOpen()) {
//     // Calculate dt
//     const float dt = clock.restart().asSeconds();
//     window.clear();
//     game_system.update(dt);
//     game_system.render(window);
//
//     sf::Event event{};
//     while (window.pollEvent(event))
//     {
//       // "close requested" event: we close the window
//       if (event.type == sf::Event::Closed)
//         window.close();
//
//       game_system.handle_event(event);
//     }
//     window.display();
//   }
//
//   window.close();
//   return 0;
// }

#include <SFML/Graphics.hpp>
#include "StartMenuScene.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Scene System");
    window.setFramerateLimit(60);

    Scene* current = new StartMenuScene(window.getSize());
    sf::Clock clock;

    while (window.isOpen() && current) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            current->handleEvent(event);
        }

        float dt = clock.restart().asSeconds();
        current->update(dt);

        Scene* next = current->nextScene();
        if (next != current) {
            delete current;
            current = next;
        }

        window.clear();
        current->render(window);
        window.display();
    }

    delete current;
    return 0;
}


