#pragma once

// SFML includes
#include "SFML/Graphics/Color.hpp"

// Local includes
#include "game_parameters.hpp"
#include "game_objects/entity.hpp"


class Light : Component<Light> {
  friend Component<Light>;
public:
  Light();
  
  void update_impl(const float delta_time) { /* Implement in Derived classes */ }; 
  const sf::Color get_color();
  const float& get_wavelength_as_nm();

  const int& get_remaining_collisions();

private:
  constexpr static int max_collisions = GameParameters::max_ray_collisions;
  constexpr static float max_length = GameParameters::max_ray_length;

  const float wavelength;
  const int remaining_collisions;
};
