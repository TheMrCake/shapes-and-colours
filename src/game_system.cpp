#include "game_system.hpp"

// STD includes
#include <cstdio>
#include <memory>

#include "managers/entity_manager.hpp"
#include "managers/physics_manager.hpp"

GameSystem::GameSystem()
  : entity_manager()
  , physics_manager(entity_manager)
  {}

void GameSystem::init() {
}

void GameSystem::update(const float dt) {

}

void GameSystem::render(sf::RenderWindow& window) {  
  }
  }
}
