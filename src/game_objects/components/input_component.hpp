 #pragma once

// Local includes
#include "game_objects/entity.hpp"



struct Input : Component<Input> {
  Input();
  Input(EntityId entity_id);
};
