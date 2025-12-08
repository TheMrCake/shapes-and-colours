#pragma once

struct GameParameters {
    constexpr static int game_width = 800;
    constexpr static int game_height = 600;

    constexpr static int max_ray_collisions = 10;
    constexpr static int max_ray_length = 5000;
    constexpr static int max_emitted_rays = 100;

    constexpr static float physics_scale = 30.f;
    constexpr static float physics_scale_inv = 1.f / 30.f;

    constexpr static int physics_sub_step_count = 4;
    constexpr static float physics_time_step = 1.f / 60.f;

    constexpr static float default_density = 10.f;
    constexpr static float default_friction = 0.8f;
    constexpr static float default_restitution = 1.0f;

    constexpr static float character_speed = 200.f;
};
