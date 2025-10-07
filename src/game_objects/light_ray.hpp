#pragma once

// STD includes
#include <optional>

// SFML includes
#include "SFML/Graphics/Color.hpp"
#include "SFML/System/Vector2.hpp"

// Local includes
#include "game_parameters.hpp"
#include "interfaces/positionable.hpp"

class Collision;

class LightRay : public Positionable {
public:
  LightRay();
  LightRay(const sf::Vector2f& position, const sf::Vector2f& end_position, const float& wavelength);

  std::optional<LightRay> collide(const Collision& collision);

  const sf::Vector2f& get_end_position();
  void set_end_position(const sf::Vector2f& end_position);

  const sf::Color get_color();
  const float& get_wavelength_as_nm();

  const int& get_remaining_collisions();
private:
  LightRay(const sf::Vector2f& position, const sf::Vector2f& end_position, const float& wavelength, const int& remaining_collisions);

  constexpr static int max_collisions = GameParameters::max_ray_collisions;
  sf::Vector2f end_position;
  const float wavelength;
  const int remaining_collisions;
};
