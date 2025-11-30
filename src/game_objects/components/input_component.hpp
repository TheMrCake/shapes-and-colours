 #pragma once

// Local includes
#include "game_objects/entity.hpp"



class Input : Component<Input> {
  friend Component<Input>;
public:
  Input();
  Input(EntityId entity_id);
  
private:
  void update_impl(const float delta_time); 
};
