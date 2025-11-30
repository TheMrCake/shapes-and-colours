#include "game_objects/components/light_component.hpp"

// Local includes
#include "game_objects/entity.hpp"

Light::Light()
  : Component<Light>(INVALID_ENTITY_ID)
  , wavelength()
  , remaining_collisions()
  {}

Light::Light(EntityId entity_id)
  : Component<Light>(entity_id)
  , wavelength()
  , remaining_collisions()
  {}

void Light::update_impl(const float delta_time) {
  
}
