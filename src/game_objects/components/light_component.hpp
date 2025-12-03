#pragma once

// SFML includes
#include "SFML/Graphics/Color.hpp"

// Local includes
#include "game_parameters.hpp"
#include "game_objects/entity.hpp"


struct Light : Component<Light> {
  Light();
  Light(EntityId entity_id);

  constexpr static int max_collisions = GameParameters::max_ray_collisions;
  constexpr static float max_length = GameParameters::max_ray_length;

  float wavelength;
  int remaining_collisions;
};
