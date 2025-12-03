#pragma once

// Local includes
#include "managers/entity_manager.hpp"


class System {
public:
  System(EntityManager& entity_manager);

  virtual void update(const float delta_time) = 0;
protected:
  EntityManager& entity_manager;
};
