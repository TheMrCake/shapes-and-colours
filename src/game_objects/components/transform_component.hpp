#pragma once

// Local includes
#include "game_objects/entity.hpp"
#include "utils/b2d_utils.hpp"

struct Transform : Component<Transform> {
    Transform();
    Transform(EntityId entit_id);

    // private:
    //   void update_impl(const float delta_time);

    //   void apply_transforms();

    //   std::vector<transform_info> transforms_to_apply;

    transform_info transform;
};
