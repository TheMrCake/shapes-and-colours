//
// Created by deborah ama on 05/12/2025.
//
#pragma once
#include "system.hpp"
#include "managers/entity_manager.hpp"

class LightSystem : public System {
public:
    explicit LightSystem(EntityManager& em) : System(em), entityManager(em) {}
    void update(float dt) override;

    private:
    EntityManager& entityManager;
};
