//
// Created by deborah ama on 04/12/2025.
//

#include "systems/crystal_system.hpp"
#include "game_objects/components/sprite_component.hpp"
#include "game_objects/components/crystal_component.hpp"

CrystalSystem::CrystalSystem(EntityManager& entity_manager) : System(entity_manager) {
}

void CrystalSystem::update(float delta_time) {
    auto& crystals = entity_manager.get_component_map<Crystal>();
    for (auto& [id, cptr] : crystals) {
        Crystal& crystal = *cptr;

        // Get sprite if present
        if (auto spritePtrOpt = entity_manager.get_entity_component<Sprite>(id)) {
            Sprite* sprite = *spritePtrOpt;

            if (!crystal.activated && crystal.charge >= crystal.target_charge) {
                crystal.activated = true;
                sprite->sprite.setColor(sf::Color(200, 255, 200)); // glow green
            }
        }
    }
}

