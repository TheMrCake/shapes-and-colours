#pragma once

// STD includes
#include <vector>

// Local includes
#include "SFML/System/Vector2.hpp"
#include "game_objects/entity.hpp"

struct transform_info {
  sf::Vector2f translation;
  float rotation; // Radians
};

class Transform : Component<Transform> {
  friend Component<Transform>;
public:  
  Transform();
  Transform(EntityId entit_id);

  void add_transform(transform_info new_transform);

private:
  void update_impl(const float delta_time);

  void apply_transforms();

  std::vector<transform_info> transforms_to_apply;

  transform_info current_transform;
};

