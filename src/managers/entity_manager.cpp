#include "managers/entity_manager.hpp"

// Local includes
#include <memory>
#include <optional>

EntityManager::EntityManager()
  : next_id(0)
  , entities()
{}



EntityMap& EntityManager::get_entities() {
  return entities;
}

const EntityMap& EntityManager::get_entities_const() {
  return get_entities();  
}
