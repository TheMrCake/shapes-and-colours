#include "game_objects/components/transform_component.hpp"

// Local includes
#include "game_objects/entity.hpp"

Transform::Transform()
    : Component<Transform>(INVALID_ENTITY_ID) {}

Transform::Transform(EntityId entity_id)
    : Component<Transform>(entity_id) {}

// void Transform::add_transform(transform_info new_transform) {
//   transforms_to_apply.push_back(new_transform);
// }

// void Transform::update_impl(const float delta_time) {
//   apply_transforms();
// }

// void Transform::apply_transforms() {
//   for (auto& trans_info : transforms_to_apply) {
//     current_transform.translation += trans_info.translation;
//     current_transform.rotation += trans_info.rotation;
//   }
//   transforms_to_apply.clear();
// }
