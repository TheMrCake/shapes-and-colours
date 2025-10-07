#include "light_ray.hpp"

// STD includes
#include <optional>

// SFML includes
#include "SFML/Graphics/Color.hpp"

// Local includes
#include "interfaces/positionable.hpp"
#include "utils/color_utils.hpp"


LightRay::LightRay()
  : Positionable()
  , end_position()
  , wavelength()
  , remaining_collisions(max_collisions) {}

LightRay::LightRay(const sf::Vector2f& position, const sf::Vector2f& end_position, const float& wavelength_nm)
  : Positionable(position)
  , end_position(end_position)
  , wavelength(wavelength_nm)
  , remaining_collisions(max_collisions) {}

LightRay::LightRay(const sf::Vector2f& position, const sf::Vector2f& end_position, const float& wavelength_nm, const int& remaining_collisions)
  : Positionable(position)
  , end_position(end_position)
  , wavelength(wavelength_nm)
  , remaining_collisions(remaining_collisions) {}


std::optional<LightRay> LightRay::collide(const Collision& ) {
  return std::nullopt;
}

const sf::Vector2f& LightRay::get_end_position() {
  return end_position;
}

void LightRay::set_end_position(const sf::Vector2f& new_end_position) {
  end_position = new_end_position;
}

const sf::Color LightRay::get_color() {
  return ColorUtils::wavelength_to_color(wavelength);
}

const float& LightRay::get_wavelength_as_nm() {
  return wavelength;
}

const int& LightRay::get_remaining_collisions() {
  return remaining_collisions;
}
