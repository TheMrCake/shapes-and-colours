#include "systems/input_system.hpp"

// SFML includes
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"

// Local includes
#include "game_objects/components/input_component.hpp"
#include "utils/b2d_utils.hpp"
#include <iostream>

InputSystem::InputSystem(EntityManager &entity_manager)
    : System(entity_manager) {}

void InputSystem::update(const float delta_time) {
    ComponentMap<Input> &input_component_map =
        entity_manager.get_component_map<Input>();
    for (auto &[entity_id, input_component] : input_component_map) {

        sf::Vector2f &input_vec = input_component->input_direction;
        input_vec = {0.f, 0.f};
        // Horizontal Input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            input_vec.x--;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            input_vec.x++;
        }

        // Vertical Input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            input_vec.y++;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            input_vec.y--;
        }

        input_component->input_direction =
            Box2DUtils::normalize(input_component->input_direction);
    }
}

void InputSystem::handle_event(sf::Event event) {
    Input new_input_component{};

    switch (event.type) {
    case sf::Event::EventType::KeyReleased:
        switch (event.key.code) {
        case sf::Keyboard::Key::Space: // Possess
            new_input_component.possess_pressed = true;
            break;
        default:
            // Commented out as it would log too much for now
            // std::cout << "Unhandled key: " << event.key.code << std::endl;
            break;
        }
        break;
    default:
        // Commented out as it would log too much for now
        // std::cout << "Unhandled event: " << event.type << std::endl;
        break;
    }

    ComponentMap<Input> &input_component_map =
        entity_manager.get_component_map<Input>();

    for (auto &[entity_id, input_component] : input_component_map) {
        input_component->possess_pressed = new_input_component.possess_pressed;
    }
}
