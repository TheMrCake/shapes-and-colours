#pragma once

// Local includes
#include "game_objects/components/collision_component.hpp"
#include "game_objects/components/light_component.hpp"
#include "game_objects/components/transform_component.hpp"
#include "game_objects/entity.hpp"



using LightRay = Entity<Collision, Transform, Light>;
using LightEmitter = Entity<Collision, Transform>;
