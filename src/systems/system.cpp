#include "systems/system.hpp"

// Local includes
#include "managers/entity_manager.hpp"

System::System(EntityManager &entity_manager)
    : entity_manager(entity_manager) {}
