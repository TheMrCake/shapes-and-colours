#include "game_system.hpp"

// STD includes
#include <cstdio>
#include <memory>

// Local includes
#include "game_objects/components/shape_component.hpp"
#include "game_objects/components/sprite_component.hpp"
#include "game_objects/entities.hpp"
#include "managers/entity_manager.hpp"
#include "start_menu_scene.hpp"
#include "systems/input_system.hpp"
#include "systems/physics_system.hpp"

GameSystem::GameSystem(sf::Vector2u window_size)
  : entity_manager()
  , physics_system(entity_manager)
  , input_system(entity_manager)
  , current_scene(std::make_unique<StartMenuScene>(window_size))
  , in_game(false)
  {}

void GameSystem::init() {
  // entity_manager.make_entity<LightRay>();
}

void GameSystem::update(const float dt) {
  current_scene->update(dt);

  Scene* next = current_scene->nextScene();
  if (next != current_scene.get()) {
    current_scene.reset(next);
    //current_scene = std::unique_ptr<Scene>(next);
  }

  if (in_game) {
    physics_system.update(dt);
  }
}

void GameSystem::render(sf::RenderWindow& window) {  
  current_scene->render(window);

  for (auto&& [e_id, component] : entity_manager.get_component_map<Sprite>()) {
    window.draw(component->sprite);
  }

  for (auto&& [e_id, component] : entity_manager.get_component_map<Shape>()) {
    window.draw(*component->shape);
  }
}


void GameSystem::handle_event(sf::Event event) {
  current_scene->handleEvent(event);

  if (in_game)
  {
    input_system.handle_event(event);
  }
}
