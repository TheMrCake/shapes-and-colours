#include "game_system.hpp"

// STD includes
#include <memory>
#include <iostream>

// Local includes
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/ConvexShape.hpp"
#include "game_objects/components/physics_component.hpp"
#include "game_objects/components/shape_component.hpp"
#include "game_objects/components/sprite_component.hpp"
#include "game_objects/entities.hpp"
#include "game_parameters.hpp"
#include "game_scene.hpp"
#include "managers/entity_manager.hpp"
#include "pause_menu.hpp"
#include "start_menu_scene.hpp"
#include "systems/input_system.hpp"
#include "systems/physics_system.hpp"
#include "utils/b2d_utils.hpp"

GameSystem::GameSystem()
    : entity_manager(),
      resource_manager(),
      physics_system(entity_manager),
      input_system(entity_manager),
      crystal_system(entity_manager),
      light_system(entity_manager),
      current_scene(
          std::make_unique<StartMenuScene>(*this)),
      in_game(false),
      running(true) {
    std::cout << "GameSystem initialized" << std::endl;
}

void GameSystem::start_game() {
    EntityId player = entity_manager.make_entity<Player>();

    if (auto player_physics_comp = entity_manager.get_entity_component<Physics>(player);
        player_physics_comp.has_value()) {
        player_physics_comp.value()->body_id = Box2DUtils::create_physics_circle(physics_system.get_world_id(), true, sf::CircleShape(2));
    }

    auto player_sprite_comp = entity_manager.get_entity_component<Sprite>(player);

    if (!player_sprite_comp.has_value()) {
        // Something has gone terribly wrong
        std::cerr << "Failed to find player entity sprite component" << std::endl;
    };

    sf::Texture bulb_texture{};
    // Load bulb texture
    if (!bulb_texture.loadFromFile("resources/bulbling.png")) {
        std::cerr << "Failed to load bulb image" << std::endl;
    }

    player_sprite_comp.value()->resource_id = resource_manager.new_resource(bulb_texture);

    sf::Sprite& player_sprite = player_sprite_comp.value()->sprite;
    
    player_sprite.setTexture(bulb_texture);
    player_sprite.setOrigin(bulb_texture.getSize().x / 2.f,
                         bulb_texture.getSize().y / 2.f);
    player_sprite.setPosition(GameParameters::game_width / 2.f, GameParameters::game_height / 2.f);
    player_sprite.setScale(0.15f, 0.15f);
    
    // Setup crystal

    EntityId crystal = entity_manager.make_entity<LightCrystal>();

    auto crystal_physics_comp = entity_manager.get_entity_component<Physics>(crystal);
    crystal_physics_comp.value()->body_id = Box2DUtils::create_physics_circle(physics_system.get_world_id(), false, sf::CircleShape(2));

    auto crystal_shape_comp = entity_manager.get_entity_component<Shape>(crystal);
    crystal_shape_comp.value()->shape = std::make_unique<sf::ConvexShape>();
    sf::ConvexShape& crystalShape = static_cast<sf::ConvexShape&>(*crystal_shape_comp.value()->shape);

    crystalShape.setPointCount(6);
    crystalShape.setPoint(0, sf::Vector2f(0.f, -50.f));
    crystalShape.setPoint(1, sf::Vector2f(30.f, -20.f));
    crystalShape.setPoint(2, sf::Vector2f(30.f, 20.f));
    crystalShape.setPoint(3, sf::Vector2f(0.f, 50.f));
    crystalShape.setPoint(4, sf::Vector2f(-30.f, 20.f));
    crystalShape.setPoint(5, sf::Vector2f(-30.f, -20.f));

    crystalShape.setFillColor(sf::Color(101, 96, 98));
    crystalShape.setOutlineColor(sf::Color(129, 121, 125));
    crystalShape.setOutlineThickness(2.f);
    crystalShape.setPosition(GameParameters::game_width / 3.f, GameParameters::game_height / 2.f);

    // Create light beam
    // beamId =
    //     create_light_ray(entity_manager, windowSize, sf::Vector2f(-1.f, 1.f));
    // std::cout << "Light beam created with ID: " << beamId << "\n";

    // // Verify the light beam was created
    // if (auto lightOpt = entity_manager.get_entity_component<Light>(beamId)) {
    //     std::cout << "Light component found!\n";
    // } else {
    //     std::cout << "ERROR: Light component NOT found!\n";
    // }

    // if (auto shapeOpt = entity_manager.get_entity_component<Shape>(beamId)) {
    //     std::cout << "Shape component found, visible: " << (*shapeOpt)->visible
    //               << "\n";
    // } else {
    //     std::cout << "ERROR: Shape component NOT found!\n";
    // }

    // // Setup border
    // border.setSize(sf::Vector2f(windowSize.x - 20.f, windowSize.y - 20.f));
    // border.setPosition(10.f, 10.f);
    // border.setFillColor(sf::Color::Transparent);
    // border.setOutlineThickness(10.f);
    // border.setOutlineColor(sf::Color(80, 100, 150));
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

        } else if (dynamic_cast<StartMenuScene*>(next)) {
            std::cout << "Transitioning to StartMenuScene\n";
            in_game = false;
            current_scene.reset(next);
        } else if (dynamic_cast<PauseMenuScene*>(next)) {
            std::cout << "Transitioning to PauseMenuScene\n";
            // Save the current GameScene before switching to pause menu
            if (GameScene* gameScene =
                    dynamic_cast<GameScene*>(current_scene.get())) {
                std::cout << "Saving GameScene\n";
                // Move current_scene to saved_game_scene
            }
            // Now set the pause menu as current
            current_scene.reset(next);
        }
    }

    // Only update game systems when in game and not paused
    GameScene* gameScene = dynamic_cast<GameScene*>(current_scene.get());

    if (in_game) {
        physics_system.update(dt);
        input_system.update(dt);
        crystal_system.update(dt);
        light_system.update(dt);
    }
}

void GameSystem::render(sf::RenderWindow& window) {
    if (!current_scene)
        return;

    // Render current scene
    current_scene->render(window);

    // Render all sprites
    for (auto&& [e_id, component] :
         entity_manager.get_component_map<Sprite>()) {
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
    if (!current_scene)
        return;

    std::cout << "GameSystem handle_event, type: " << event.type << "\n";

    current_scene->handleEvent(event);

    // Don't pass events to input system when not in game
    if (in_game) {
        input_system.handle_event(event);
    }
}
