//
// Created by deborah ama on 04/12/2025.
//

#pragma once
#include "game_objects/entity.hpp"

struct Crystal : Component<Crystal> {
    Crystal();
    Crystal(EntityId entity_id);

    float charge;
    float target_charge;
    bool activated;
};
