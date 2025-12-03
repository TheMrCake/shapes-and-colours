#include "game_system.hpp"

// STD includes
#include <cstdio>
#include <memory>

// Local includes
#include "game_objects/components/shape_component.hpp"
#include "game_objects/components/sprite_component.hpp"
#include "game_objects/entities.hpp"
#include "managers/entity_manager.hpp"
#include "systems/input_system.hpp"
#include "systems/physics_system.hpp"

GameSystem::GameSystem()
  : entity_manager()
  , physics_system(entity_manager)
  , input_system(entity_manager)
  , in_game(false)
  {}

void GameSystem::init() {
  // entity_manager.make_entity<LightRay>();
}

void GameSystem::update(const float dt) {
  // for (auto& ship : ships) {  
  //   ship->update(dt);
  //   if (ship->get_ready_to_fire()) {
  //     bullets.emplace_back(std::move(ship->shoot()));
  //   }
  // }

  // for (auto& bullet : bullets) {
  //   bullet->update(dt);
  // }

  // std::erase_if(ships,
  //     [dt, this](auto &ship) -> bool {
  //       return !ship->get_alive();
  //     });
  // std::erase_if(bullets,
  //     [dt](auto &bullet) -> bool {
  //        return !bullet->get_alive();
  //     });
}

void GameSystem::render(sf::RenderWindow& window) {  
  for (auto&& [e_id, component] : entity_manager.get_component_map<Sprite>()) {
    window.draw(component->sprite);
  }

  for (auto&& [e_id, component] : entity_manager.get_component_map<Shape>()) {
    window.draw(*component->shape);
  }
  // for (auto& ship : ships) {
  //   window.draw(ship->get_sprite());
  // }
  // for (auto& bullet : bullets) {
  //   window.draw(bullet->get_sprite());
  // }
  // window.draw(shape);
}


void GameSystem::handle_event(sf::Event event) {
  if (in_game)
  {
    input_system.handle_event(event);
  }
}
