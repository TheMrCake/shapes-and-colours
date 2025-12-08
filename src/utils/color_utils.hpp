#pragma once

// SFML includes
#include "SFML/Graphics/Color.hpp"

namespace ColorUtils {
    sf::Color wavelength_to_color(const float &wavelength);

    // Gaussian Parameters in nanometers
    // RED
    constexpr float r_mu = 600.0f;
    constexpr float r_sigma = 50.0f;
    // GREEN
    constexpr float g_mu = 550.0f;
    constexpr float g_sigma = 45.0f;
    // BLUE
    constexpr float b_mu = 450.0f;
    constexpr float b_sigma = 30.0f;

} // namespace ColorUtils
