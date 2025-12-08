#include "utils/color_utils.hpp"

// STD include
#include <algorithm>
#include <cmath>
// SFML includes
#include "SFML/Graphics/Color.hpp"

sf::Color ColorUtils::wavelength_to_color(const float& wavelength) {
    // Use namepsace
    using namespace ColorUtils;

    if (wavelength < 380.0f || wavelength > 780.0f) {
        return sf::Color::Black;
    }

    // Calculate Gaussian response
    auto gaussian = [](float wavelength, float mu, float sigma) -> float {
        float a = (wavelength - mu) / sigma;
        return std::exp(-0.5f * a * a);
    };

    // Calculate the Intensity for each color channel
    float r_response = gaussian(wavelength, r_mu, r_sigma);
    float g_response = gaussian(wavelength, g_mu, g_sigma);
    float b_response = gaussian(wavelength, b_mu, b_sigma);

    // Rest of the clamping and scaling logic
    int r = static_cast<int>(r_response * 255.0f);
    int g = static_cast<int>(g_response * 255.0f);
    int b = static_cast<int>(b_response * 255.0f);

    r = std::min(255, std::max(0, r));
    g = std::min(255, std::max(0, g));
    b = std::min(255, std::max(0, b));

    return sf::Color(r, g, b);
}
