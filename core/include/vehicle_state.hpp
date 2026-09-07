#pragma once

#include <string>


struct VehicleState {
    std::string timestamp;

    double speed_kmh = 0.0;
    double battery_percent = 0.0;
    double cabin_temperature_c = 0.0;

    bool engine_on = false;
    bool doors_locked = false;

    double latitude = 0.0;
    double longitude = 0.0;
};