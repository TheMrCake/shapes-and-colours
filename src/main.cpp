#include "SFML/Window/Event.hpp"

#include "game_parameters.hpp"
#include "game_system.hpp"
#include <SFML/Graphics.hpp>

int main() {
  // Create window
  sf::RenderWindow window(sf::VideoMode({GameParameters::game_width, GameParameters::game_height}), "Shapes and Colours");
  GameSystem game_system{};
  game_system.init();

  sf::Clock clock = sf::Clock();

  // Initialise and load
  while(window.isOpen()) {
    // Calculate dt
    const float dt = clock.restart().asSeconds();
    window.clear();
    game_system.update(dt);
    game_system.render(window);

    sf::Event event{};
    while (window.pollEvent(event))
    {
      // "close requested" event: we close the window
      if (event.type == sf::Event::Closed)
        window.close();
    }
    window.display();
  }

  window.close();
  return 0;
}

// sf::Color bg(20, 20, 20); // near-black
