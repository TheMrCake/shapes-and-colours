#pragma once

// STD includes
#include <cstdint>
#include <type_traits>
#include <unordered_map>

// SFML includes
#include "SFML/Graphics/Texture.hpp"

using ResourceId = uint16_t;
constexpr ResourceId INVALID_RESOURCE_ID = -1;

template <typename ResourceType>
using ResourceMap = std::unordered_map<ResourceId, ResourceType>;

// Pool Resources for easy access
template <typename ResourceType>
struct ResourcePool {
    ResourceMap<ResourceType> resources;
};

template <typename... Resources>
struct ResourceStorage : ResourcePool<Resources>... {};

// When making new Resources also put their name here in alphabetical order
using AllResourceStorages = ResourceStorage<sf::Texture>;

class ResourceManager : AllResourceStorages {
public:
    ResourceManager();

    // Non-copyable
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    // Movable
    ResourceManager(ResourceManager&&) = default;
    ResourceManager& operator=(ResourceManager&&) = default;

    template <typename ResourceType, typename ResourceTypeDecayed = std::decay_t<ResourceType>>
    ResourceId new_resource(ResourceType&& resource) {
        ResourceId current_id = next_id;
        next_id++;
        get_resource_map<ResourceTypeDecayed>().insert({current_id, resource});
        return current_id;
    }

    // Return all resources of a specific type
    template <typename ResourceType, typename ResourceTypeDecayed = std::decay_t<ResourceType>>
    ResourceMap<ResourceTypeDecayed>& get_resource_map() {
        return static_cast<ResourcePool<ResourceTypeDecayed>*>(this)->resources;
    }

    template <typename ResourceType, typename ResourceTypeDecayed = std::decay_t<ResourceType>>
    ResourceTypeDecayed& get_resource(const ResourceId resource_id) {
        ResourceMap<ResourceTypeDecayed>& resource_map =
            get_Resource_map<ResourceTypeDecayed>();
        if (auto it = resource_map.find(resource_id);
            it != resource_map.end()) {
            return it->second.get();
        }
        return std::nullopt;
    }

private:
    ResourceId next_id;
};
