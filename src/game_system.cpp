#include "game_system.hpp"

#include <cstdio>
#include <iostream>
#include <memory>
#include <vector>

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Vector2.hpp"

#include "game_parameters.hpp"
#include "ship.hpp"
#include "bullet.hpp"
#include "invader.hpp"
#include "player.hpp"

void GameSystem::init() {
  if (!spritesheet.loadFromFile("resources/invaders_sheet.png")) {
    std::cerr << "Failed to load spritesheet!" << std::endl;
  } 

  sf::Sprite player_bullet{};
  player_bullet.setTexture(spritesheet);
  player_bullet.setTextureRect({
                                 {GameParameters::sprite_size, GameParameters::sprite_size},
                                 {GameParameters::sprite_size, GameParameters::sprite_size}
                               });
  player_bullet.setOrigin(GameParameters::sprite_size/2.f, GameParameters::sprite_size/2.f);
  Player::set_bullet_sprite(player_bullet);

  sf::Sprite invader_bullet{};
  invader_bullet.setTexture(spritesheet);
  invader_bullet.setTextureRect({
                                 {2 * GameParameters::sprite_size, GameParameters::sprite_size},
                                 {GameParameters::sprite_size, GameParameters::sprite_size}
                               });
  invader_bullet.setOrigin(GameParameters::sprite_size/2.f, GameParameters::sprite_size/2.f);
  Invader::set_bullet_sprite(invader_bullet);

  // Create Invaders
  for (int row = 0; row < GameParameters::invader_rows; row++) {
    for (int column = 0; column < GameParameters::invader_columns; column++) {
      sf::Sprite invader{};
      invader.setTexture(spritesheet);
      invader.setTextureRect({
          {row * GameParameters::sprite_size, 0},
          {GameParameters::sprite_size, GameParameters::sprite_size}
        });
      invader.setOrigin(GameParameters::sprite_size/2.f, GameParameters::sprite_size/2.f);

      sf::Vector2i column_row = sf::Vector2i(column, row);
      ships.emplace_back(std::make_unique<Invader>(invader, column_row));
      }
  }

  // Create Player
  sf::Sprite player{};
  player.setTexture(spritesheet);
  player.setTextureRect({
                          {5*GameParameters::sprite_size, GameParameters::sprite_size},
                          {GameParameters::sprite_size, GameParameters::sprite_size}
                        });
  player.setOrigin(GameParameters::sprite_size/2.f, GameParameters::sprite_size/2.f);
  {
    using gp = GameParameters;
    sf::Vector2f player_position = sf::Vector2f(gp::game_width/2.f - gp::sprite_size/2.f, gp::game_height - gp::total_sprite_size);
    ships.emplace_back(std::make_unique<Player>(player, player_position));
  }
}

void GameSystem::update(const float dt) {
  for (auto& ship : ships) {  
    ship->update(dt);
    if (ship->get_ready_to_fire()) {
      bullets.emplace_back(std::move(ship->shoot()));
    }
  }

  for (auto& bullet : bullets) {
    bullet->update(dt);
  }

  std::erase_if(ships,
      [dt, this](auto &ship) -> bool {
        return !ship->get_alive();
      });
  std::erase_if(bullets,
      [dt](auto &bullet) -> bool {
         return !bullet->get_alive();
      });
}

void GameSystem::render(sf::RenderWindow& window) {  
  printf("dick");
  for (auto& ship : ships) {
    window.draw(ship->get_sprite());
  }
  printf("pussy");
  for (auto& bullet : bullets) {
    window.draw(bullet->get_sprite());
  }
}
