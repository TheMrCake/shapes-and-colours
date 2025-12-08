#pragma once

// SFML includes
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Event.hpp"

// Local includes
#include "managers/entity_manager.hpp"
#include "scene.hpp"
#include "systems/input_system.hpp"
#include "systems/physics_system.hpp"
#include "systems/movement_system.hpp"
#include "systems/transform_system.hpp"
#include <memory>

#include "systems/crystal_system.hpp"
#include "systems/light_system.hpp"

class GameSystem {
public:
    GameSystem();
    ~GameSystem() = default;

    void start_game();

    void update(const float dt);

    void render(sf::RenderWindow& window);

    void handle_event(sf::Event event);

    bool running;
    bool in_game;

private:
    EntityManager entity_manager;
    ResourceManager resource_manager;

    PhysicsSystem physics_system;
    InputSystem input_system;
    CrystalSystem crystal_system;
    LightSystem light_system;
    MovementSystem movement_system;
    TransformSystem transform_system;
    std::unique_ptr<Scene> current_scene;
};
