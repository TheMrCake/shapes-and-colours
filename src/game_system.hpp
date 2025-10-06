#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "ship.hpp"
#include <memory>
#include <vector>

class GameSystem {
public:
  void init();

  void update(const float dt);

  void render(sf::RenderWindow& window);

private:
  sf::Texture spritesheet;
  std::vector<std::unique_ptr<Ship>> ships;
  std::vector<std::unique_ptr<Bullet>> bullets;
};
