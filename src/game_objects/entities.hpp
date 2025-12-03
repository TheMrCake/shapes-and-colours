#pragma once

// Local includes
#include "game_objects/components/physics_component.hpp"
#include "game_objects/components/light_component.hpp"
#include "game_objects/components/transform_component.hpp"
#include "game_objects/components/input_component.hpp"
#include "game_objects/entity.hpp"



using LightRay = Entity<Transform, Light>;
using LightEmitter = Entity<Physics, Transform>;
using Player = Entity<Physics, Transform, Input>;
