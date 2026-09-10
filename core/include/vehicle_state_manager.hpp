#pragma once

#include "vehicle_state.hpp"

class VehicleStateManager
{
    public:

        void update(
            const VehicleState& state
        );

        const VehicleState& get_state() const;

    private:

        VehicleState current_state;
};