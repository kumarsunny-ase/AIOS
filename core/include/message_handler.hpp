#pragma once

#include <string>

#include "vehicle_state.hpp"


class MessageHandler
{
public:

    VehicleState parse_vehicle_state(
        const std::string& payload
    );
};