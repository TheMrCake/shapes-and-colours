#pragma once

// Box2D includes
#include "SFML/Window/Event.hpp"
#include "box2d/id.h"

// Local includes
#include "managers/entity_manager.hpp"
#include "systems/system.hpp"

class InputSystem : System {
public:
    InputSystem(EntityManager &entity_manager);

    virtual void update(const float delta_time) override;
    void handle_event(sf::Event event);

private:
    b2WorldId world_id;
};
