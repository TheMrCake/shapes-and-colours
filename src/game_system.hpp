#pragma once

// SFML includes
#include "SFML/Graphics/RenderWindow.hpp"

// Local includes
#include "managers/entity_manager.hpp"
#include "systems/physics_system.hpp"

class GameSystem {
public:
  GameSystem();

  void init();

  void update(const float dt);

  void render(sf::RenderWindow& window);

private:
  EntityManager entity_manager;
  PhysicsSystem physics_system;
};
