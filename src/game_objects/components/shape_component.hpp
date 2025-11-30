 #pragma once

// STD includes
#include <memory>

// Local includes
#include "SFML/Graphics/Shape.hpp"
#include "game_objects/entity.hpp"



class Shape : Component<Shape> {
  friend Component<Shape>;
public:
  std::unique_ptr<sf::Shape>& get_shape();
  const std::unique_ptr<sf::Shape>& get_shape_const();

private:
  void update_impl(const float delta_time); 

  std::unique_ptr<sf::Shape> shape;
};
