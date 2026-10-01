#pragma once

#include "vehicle_state.hpp"
#include "vehicle_context.hpp"


class ContextEngine
{
public:

    VehicleContext evaluate(const VehicleState& state) const;
};