#include "vehicle_state_manager.hpp"

void VehicleStateManager::update(
    const VehicleState& state
)
{
    current_state = state;
}

const VehicleState&
VehicleStateManager::get_state() const
{
    return  current_state;
}