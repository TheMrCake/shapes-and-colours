//
// Created by deborah ama on 05/12/2025.
//
#pragma once
#include "managers/entity_manager.hpp"
#include "system.hpp"

class LightSystem : public System {
public:
    explicit LightSystem(EntityManager& em)
        : System(em),
          entityManager(em) {}
    void update(float dt) override;

private:
    EntityManager& entityManager;
};
