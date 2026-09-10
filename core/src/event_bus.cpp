#include "event_bus.hpp"


void EventBus::subscribe(
    VehicleStateListener listener
)
{
    vehicle_state_listeners.push_back(
        listener
    );
}


void EventBus::publish(
    const VehicleState& state
)
{
    for (
        const auto& listener :
        vehicle_state_listeners
    )
    {
        listener(state);
    }
}