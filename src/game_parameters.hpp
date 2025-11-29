#pragma once

struct GameParameters {
  constexpr static int game_width = 800;
  constexpr static int game_height = 600;

  constexpr static int max_ray_collisions = 10;
  constexpr static int max_ray_length = 5000;
  constexpr static int max_emitted_rays = 100;

  constexpr static float physics_scale = 30.f;
  constexpr static float physics_scale_inv = 1.f / 30.f;

  constexpr static float default_density = 10.f;
  constexpr static float default_friction = 0.8f;
  constexpr static float default_restitution = 1.0f;

  constexpr static int sprite_size = 32;
  constexpr static int sprite_gap = 10;
  constexpr static int total_sprite_size = sprite_size + sprite_gap;
  
  constexpr static int invader_columns = (game_width/(sprite_size+sprite_gap)) - 2;
  constexpr static int invader_rows = 5;
  static_assert(game_height/(sprite_size + sprite_gap) >= invader_rows);

  constexpr static float bullet_speed = 200.f;
};

