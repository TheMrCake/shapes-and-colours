#pragma once

// STD includes
#include <cstdint>
#include <tuple>
#include <type_traits>

using EntityId = uint16_t;
constexpr EntityId INVALID_ENTITY_ID = -1;

template <typename Derived>
struct Component {
    Component()
        : entity_id(INVALID_ENTITY_ID) {}

    Component(EntityId entity_id)
        : entity_id(entity_id) {}

    ~Component() = default;

    const EntityId entity_id;
};

template <typename T>
struct is_component {
    static constexpr bool value = std::is_base_of_v<Component<T>, T>;
};

template <typename T>
constexpr bool is_component_v = is_component<T>::value;

// Check if any of the parameter pack matches T
template <typename T, typename... Args>
using matches_any = std::disjunction<std::is_same<T, Args>...>;

template <typename T, typename... Args>
constexpr bool matches_any_v = matches_any<T, Args...>::value;

template <typename... Components>
class Entity {
public:
    static constexpr bool all_components_v =
        std::conjunction_v<is_component<Components>...>;
    using component_types = std::tuple<Components...>;

    Entity(EntityId id)
        : id(id) {
        static_assert(
            all_components_v,
            "Entity requires all template parameters to be valid Components.");
    };

private:
    EntityId id;
};

// Found from https://indii.org/blog/is-type-instantiation-of-template/
// It determines if T is an instance of the type U, which we can use to
// determine if a type is a template instance of an entity.
template <typename T, template <typename...> typename U>
constexpr bool is_instance_of_v = std::false_type{};

template <template <typename...> typename U, typename... Vs>
constexpr bool is_instance_of_v<U<Vs...>, U> = std::true_type{};

template <typename T>
constexpr bool is_entity_v = is_instance_of_v<T, Entity>;
