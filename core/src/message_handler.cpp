#include "message_handler.hpp"

#include <nlohmann/json.hpp>


using json = nlohmann::json;


VehicleState MessageHandler::parse_vehicle_state(
    const std::string& payload
)
{
    VehicleState state;

    json data = json::parse(payload);

    state.timestamp =
        data.value("timestamp", "");

    state.speed_kmh =
        data.value("speed_kmh", 0.0);

    state.battery_percent =
        data.value("battery_percent", 0.0);

    state.cabin_temperature_c =
        data.value(
            "cabin_temperature_c",
            0.0
        );

    state.engine_on =
        data.value("engine_on", false);

    state.doors_locked =
        data.value("doors_locked", false);

    state.latitude =
        data.value("latitude", 0.0);

    state.longitude =
        data.value("longitude", 0.0);

    return state;
}