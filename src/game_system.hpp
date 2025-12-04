#pragma once

// SFML includes
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Event.hpp"

// Local includes
#include "managers/entity_manager.hpp"
#include "scene.hpp"
#include "systems/input_system.hpp"
#include "systems/physics_system.hpp"
#include <memory>

class GameSystem {
public:
  GameSystem(sf::Vector2u window_size);

  void init();

  void update(const float dt);

  void render(sf::RenderWindow& window);

  void handle_event(sf::Event event);

private:
  EntityManager entity_manager;

  PhysicsSystem physics_system;
  InputSystem input_system;

  std::unique_ptr<Scene> current_scene;

  bool in_game;
};
