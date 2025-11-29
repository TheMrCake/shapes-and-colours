#pragma once

// STD includes
#include <cstdint>
#include <tuple>
#include <type_traits>

using EntityId = uint16_t;

template <typename Derived>
class Component {
public:
  ~Component() = default;

  void update(const float delta_time) {
    static_cast<Derived*>(this)->update_impl(delta_time); 
  }

protected:
  EntityId* element_id;

private:
  void update_impl(const float delta_time) { /* Implement in Derived classes */ }; 
};

template<typename T>
struct is_component {
  static constexpr bool value = std::is_base_of_v<Component<T>, T>;
};

template<typename T>
constexpr bool is_component_v = is_component<T>::value;


// Check if any of the parameter pack matches T
template<typename T, typename... Args>
using matches_any = std::disjunction<std::is_same<T, Args>...>;

template<typename T, typename... Args>
constexpr bool matches_any_v = matches_any<T, Args...>::value;


template<typename... Components>
class Entity 
{
public:
  template<typename T = void>
  static constexpr bool all_components = 
    is_component_v<Components...>;

  Entity() {
    static_assert(
      all_components<void>,
      "Entity requires all template parameters to be valid Components."
    );
  };

  template<typename ComponentType, typename = std::enable_if<matches_any_v<ComponentType, Components...>>>
  ComponentType& get_component() {
    return std::get<ComponentType>(components);
  }

  void update_components(const float delta_time) {
    for (auto&& component : components) {
      component->update(delta_time);
    }
  }

private:
  EntityId id;

  std::tuple<Components...> components;
};
