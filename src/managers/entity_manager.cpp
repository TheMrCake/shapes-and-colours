#include "managers/entity_manager.hpp"

// Local includes
#include <memory>
#include <optional>

EntityManager::EntityManager()
  : next_id(0)
  , entities()
{}
