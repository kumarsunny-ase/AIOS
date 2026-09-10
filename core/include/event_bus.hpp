#pragma once

#include <functional>
#include <vector>

#include "vehicle_state.hpp"


class EventBus
{
public:

    using VehicleStateListener =
        std::function<void(const VehicleState&)>;

    void subscribe(
        VehicleStateListener listener
    );

    void publish(
        const VehicleState& state
    );

private:

    std::vector<VehicleStateListener>
        vehicle_state_listeners;
};