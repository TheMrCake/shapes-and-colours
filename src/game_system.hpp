#pragma once

#include "SFML/Graphics/RenderWindow.hpp"

class GameSystem {
public:
  void init();

  void update(const float dt);

  void render(sf::RenderWindow& window);

private:
};
