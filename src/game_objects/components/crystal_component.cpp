//
// Created by deborah ama on 05/12/2025.
//

#include "crystal_component.hpp"
Crystal::Crystal()
    : Component<Crystal>(INVALID_ENTITY_ID),
      charge(0.f),
      target_charge(100.f),
      activated(false) {}

Crystal::Crystal(EntityId entity_id)
    : Component<Crystal>(entity_id),
      charge(0.f),
      target_charge(100.f),
      activated(false) {}