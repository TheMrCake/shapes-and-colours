//
// Created by deborah ama on 04/12/2025.
//

#pragma once
#include "managers/entity_manager.hpp"
#include "system.hpp"

class CrystalSystem : public System {
public:
    explicit CrystalSystem(EntityManager &entity_manager);

    void update(float delta_time) override;
};