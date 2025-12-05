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
#include "game_scene.hpp"
#include "pause_menu.hpp"

GameSystem::GameSystem(sf::Vector2u window_size)
  : entity_manager()
  , physics_system(entity_manager)
  , input_system(entity_manager)
  , crystal_system(entity_manager)
  , light_system(entity_manager)
  , current_scene(std::make_unique<StartMenuScene>(window_size, entity_manager))
  , saved_game_scene(nullptr)
  ,in_game(false)
  , running(true) {
  std::cout << "GameSystem initialized\n";

}

void GameSystem::init() {
  // entity_manager.make_entity<LightRay>();
}

void GameSystem::update(const float dt) {
    // Safety check
    if (!current_scene) {
        std::cout << "No current scene, stopping\n";
        running = false;
        return;
    }

    // Update current scene
    current_scene->update(dt);

    // Check for scene transitions
    Scene* next = current_scene->nextScene();
    if (next != current_scene.get()) {
        std::cout << "Scene transition detected\n";

        if (next == nullptr) {
            std::cout << "Exit signal received\n";
            running = false;
            current_scene.reset();
            return;
        }

        // Check what type of scene we're transitioning to
        if (GameScene* gameScene = dynamic_cast<GameScene*>(next)) {
            std::cout << "Transitioning to GameScene\n";
            in_game = true;

            // Check if this is our saved game scene being returned from pause
            if (saved_game_scene && saved_game_scene.get() == gameScene) {
                std::cout << "Returning to saved GameScene from pause\n";
                // Move saved_game_scene back to current_scene
                current_scene = std::move(saved_game_scene);
            } else {
                // New game scene from start menu
                std::cout << "New GameScene created\n";
                current_scene.reset(gameScene);
            }
        } else if (dynamic_cast<StartMenuScene*>(next)) {
            std::cout << "Transitioning to StartMenuScene\n";
            in_game = false;
            saved_game_scene.reset(); // Clear saved game when returning to menu
            current_scene.reset(next);
        } else if (dynamic_cast<PauseMenuScene*>(next)) {
            std::cout << "Transitioning to PauseMenuScene\n";
            // Save the current GameScene before switching to pause menu
            if (GameScene* gameScene = dynamic_cast<GameScene*>(current_scene.get())) {
                std::cout << "Saving GameScene\n";
                // Move current_scene to saved_game_scene
                saved_game_scene.reset(dynamic_cast<GameScene*>(current_scene.release()));
            }
            // Now set the pause menu as current
            current_scene.reset(next);
        }
    }

    // Only update game systems when in game and not paused
    GameScene* gameScene = dynamic_cast<GameScene*>(current_scene.get());
    if (!gameScene && saved_game_scene) {
        // If we're in pause menu, check the saved game scene
        gameScene = saved_game_scene.get();
    }
    bool isPaused = gameScene && gameScene->isPaused();

    if (in_game && !isPaused) {
        physics_system.update(dt);
        crystal_system.update(dt);
        light_system.update(dt);
    }
}


void GameSystem::render(sf::RenderWindow& window) {
    if (!current_scene) return;

    // Render current scene
    current_scene->render(window);

    // Render all sprites
    for (auto&& [e_id, component] : entity_manager.get_component_map<Sprite>()) {
        window.draw(component->sprite);
    }

    // Render all shapes
    for (auto&& [e_id, component] : entity_manager.get_component_map<Shape>()) {
        if (component->shape) {
            window.draw(*component->shape);
        }
    }
}

void GameSystem::handle_event(sf::Event event) {
    if (!current_scene) return;

    std::cout << "GameSystem handle_event, type: " << event.type << "\n";

    current_scene->handleEvent(event);

    // Don't pass events to input system when not in game
    if (in_game) {
        input_system.handle_event(event);
    }
}
