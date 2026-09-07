#include <iostream>
#include <string>

#include "vehicle_state.hpp"

#include <mqtt/async_client.h>
#include <nlohmann/json.hpp>


using json = nlohmann::json;


const std::string MQTT_SERVER_ADDRESS =
    "tcp://localhost:1883";

const std::string CLIENT_ID =
    "aios-core";

const std::string VEHICLE_STATE_TOPIC =
    "aios/vehicle/state";


VehicleState current_vehicle_state;


void update_vehicle_state(
    const std::string& payload
) {
    try {
        json data = json::parse(payload);

        current_vehicle_state.timestamp =
            data.value("timestamp", "");

        current_vehicle_state.speed_kmh =
            data.value("speed_kmh", 0.0);

        current_vehicle_state.battery_percent =
            data.value("battery_percent", 0.0);

        current_vehicle_state.cabin_temperature_c =
            data.value(
                "cabin_temperature_c",
                0.0
            );

        current_vehicle_state.engine_on =
            data.value("engine_on", false);

        current_vehicle_state.doors_locked =
            data.value("doors_locked", false);

        current_vehicle_state.latitude =
            data.value("latitude", 0.0);

        current_vehicle_state.longitude =
            data.value("longitude", 0.0);

        std::cout << "\n--- AIOS Current Vehicle State ---\n";

        std::cout
            << "Speed: "
            << current_vehicle_state.speed_kmh
            << " km/h\n";

        std::cout
            << "Battery: "
            << current_vehicle_state.battery_percent
            << " %\n";

        std::cout
            << "Cabin Temperature: "
            << current_vehicle_state.cabin_temperature_c
            << " °C\n";

        std::cout
            << "Engine: "
            << (
                current_vehicle_state.engine_on
                ? "ON"
                : "OFF"
            )
            << "\n";

        std::cout
            << "Doors: "
            << (
                current_vehicle_state.doors_locked
                ? "LOCKED"
                : "UNLOCKED"
            )
            << "\n";

        std::cout
            << "Location: "
            << current_vehicle_state.latitude
            << ", "
            << current_vehicle_state.longitude
            << "\n";

    } catch (
        const std::exception& error
    ) {
        std::cerr
            << "Error parsing vehicle state: "
            << error.what()
            << std::endl;
    }
}


int main() {

    std::cout << "====================================\n";
    std::cout << "       AIOS Core Starting\n";
    std::cout << "====================================\n";

    try {

        mqtt::async_client client(
            MQTT_SERVER_ADDRESS,
            CLIENT_ID
        );

        mqtt::connect_options connection_options;

        std::cout
            << "Connecting to MQTT broker..."
            << std::endl;

        client.connect(
            connection_options
        )->wait();

        std::cout
            << "Connected to MQTT broker."
            << std::endl;

        client.start_consuming();

        client.subscribe(
            VEHICLE_STATE_TOPIC,
            1
        )->wait();

        std::cout
            << "Subscribed to: "
            << VEHICLE_STATE_TOPIC
            << std::endl;


        while (true) {

            auto message =
                client.consume_message();

            if (message) {

                update_vehicle_state(
                    message->to_string()
                );
            }
        }

    } catch (
        const mqtt::exception& error
    ) {

        std::cerr
            << "MQTT Error: "
            << error.what()
            << std::endl;

        return 1;
    }

    return 0;
}