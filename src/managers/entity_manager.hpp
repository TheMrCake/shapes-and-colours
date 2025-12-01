#pragma once

// STD includes
#include <memory>
#include <optional>
#include <type_traits>
#include <unordered_map>
#include <variant>

// Local includes
#include "game_objects/components/collision_component.hpp"
#include "game_objects/components/input_component.hpp"
#include "game_objects/components/light_component.hpp"
#include "game_objects/components/shape_component.hpp"
#include "game_objects/components/sprite_component.hpp"
#include "game_objects/components/transform_component.hpp"
#include "game_objects/entity.hpp"

template<typename ComponentType, typename = std::enable_if<is_component_v<ComponentType>>>
using ComponentMap = std::unordered_map<EntityId, std::unique_ptr<ComponentType>>;

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
  Input,
  Light,
  Shape,
  Sprite,
  Transform
>;

class EntityManager : AllComponentStorages {
public:
  EntityManager();

  // Non-copyable
  EntityManager(const EntityManager&) = delete;
  EntityManager& operator=(const EntityManager&) = delete;

  // Movable
  EntityManager(EntityManager&&) = default;
  EntityManager& operator=(EntityManager&&) = default;

  // Return all components of a specific type
  template<typename ComponentType>
  ComponentMap<ComponentType>& get_component_map() {
    return static_cast<ComponentPool<ComponentType>*>(this)->components;
  }

  template<typename ComponentType>
  ComponentType& get_entity_component(EntityId entity_id) {
    return static_cast<ComponentPool<ComponentType>*>(this)->components.get;
  }

  template<typename E, typename = std::enable_if<is_entity_v<E>>>
  E make_entity() {
    EntityId current_id = next_id;
    next_id++;

    std::apply([this, current_id](auto... component){
      this->add_components_to_pool<std::decay_t<decltype(component)>...>(current_id);
    }, typename E::component_types{});

    return {current_id};
  };
private:

  template<typename... ComponentTypes>
  void add_components_to_pool(EntityId id) {
    (add_single_component_to_pool<ComponentTypes>(id), ...);
  }

  template<typename ComponentType>
  void add_single_component_to_pool(EntityId id) {
    ComponentMap<ComponentType>& map = get_component_map<ComponentType>();
    map.emplace(id, std::make_unique<ComponentType>(id));
  }

  EntityId next_id;
};
