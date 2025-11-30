#pragma once

// Local includes
#include "game_objects/entity.hpp"



class Collision : Component<Collision> {
  friend Component<Collision>;
public:
  Collision();
  Collision(EntityId entity_id);
  
private:
  void update_impl(const float delta_time) { /* Implement in Derived classes */ }; 
};
