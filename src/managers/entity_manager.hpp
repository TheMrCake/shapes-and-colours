#pragma once

// STD includes
#include <memory>
#include <unordered_map>
#include <variant>

// Local includes
#include "game_objects/components/collision_component.hpp"
#include "game_objects/components/light_component.hpp"
#include "game_objects/components/shape_component.hpp"
#include "game_objects/components/sprite_component.hpp"
#include "game_objects/components/transform_component.hpp"
#include "game_objects/entity.hpp"
#include "game_objects/light_ray.hpp"

using EntityVariant = std::variant<
  LightRay
>;

using EntityVariantPtr = std::unique_ptr<EntityVariant>;
using EntityMap = std::unordered_map<EntityId, EntityVariantPtr>;

template<typename ComponentType>
using ComponentMap = std::unordered_map<EntityId, std::shared_ptr<ComponentType>>;

// Pool components for easy access
template<typename ComponentType>
struct ComponentPool {
  ComponentMap<ComponentType> components;
};

template<typename... Components>
struct ComponentStorage : ComponentPool<Components>... {};


// When making new components also put their name here in alphabetical order
using AllComponentStorages = ComponentStorage<
  Collision,
  Light,
  Shape,
  Sprite,
  Transform
>;

class EntityManager : AllComponentStorages {
public:
  EntityManager();

  // Return all components of a specific type
  template<typename ComponentType>
  ComponentMap<ComponentType>& get_component_map() {
    return static_cast<ComponentPool<ComponentType>*>(this)->components;
  }

  template<typename ComponentType>
  ComponentType& get_entity_component(EntityId entity_id) {
    if (entities.contains(entity_id)) {
      return std::visit(
        [this, entity_id](auto&& entity) -> ComponentType& {
          return entity.template get_component<ComponentType>();
        }, entities.at(entity_id) );
    }
  }

  template<typename... Components>
  std::optional<EntityId> make_entity(Entity<Components...> entity) {
    auto [e, success] = entities.emplace(next_id, std::make_unique<EntityVariant>(entity));

    if (success) {
      add_components_to_pool<Components...>(next_id);
  
      return e->first;
      next_id++;
    }

    return std::nullopt;
  };

  EntityMap& get_entities();
  const EntityMap& get_entities_const();
private:

  template<typename... Components>
  void add_components_to_pool(EntityId id) {
    (add_single_component_to_pool<Components>(id), ...);
  }

  template<typename ComponentType>
  void add_single_component_to_pool(EntityId id) {
    ComponentMap<ComponentType> map = get_component_map<ComponentType>();
    map.emplace(id, {});
  }

  EntityId next_id;

  EntityMap entities;
};
