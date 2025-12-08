#include "game_objects/components/input_component.hpp"

// Local includes
#include "game_objects/entity.hpp"

Input::Input()
    : Component<Input>(INVALID_ENTITY_ID) {}

Input::Input(EntityId entity_id)
    : Component<Input>(entity_id) {}
