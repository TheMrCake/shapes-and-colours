#pragma once

// SFML includes
#include "SFML/Graphics/RenderWindow.hpp"

// Local includes
#include "managers/entity_manager.hpp"
#include "managers/physics_manager.hpp"

class GameSystem {
public:
  GameSystem();

  void init();

  void update(const float dt);

  void render(sf::RenderWindow& window);

private:
  EntityManager entity_manager;
  PhysicsManager physics_manager;
};
