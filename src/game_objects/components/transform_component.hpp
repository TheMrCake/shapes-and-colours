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
  void add_transform(transform_info new_transform) {
    transforms_to_apply.push_back(new_transform);
  }

private:
  void update_impl(const float delta_time) {
    apply_transforms();
  }

  void apply_transforms() {
    for (auto& trans_info : transforms_to_apply) {
      current_transform.translation += trans_info.translation;
      current_transform.rotation += trans_info.rotation;
    }
    transforms_to_apply.clear();
  }

  std::vector<transform_info> transforms_to_apply;

  transform_info current_transform;
};

