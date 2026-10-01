#include <iostream>

#include  "context_engine.hpp"
#include "event_bus.hpp"
#include "message_handler.hpp"
#include "mqtt_client.hpp"
#include "vehicle_state_manager.hpp"


const std::string MQTT_SERVER =
    "tcp://localhost:1883";

const std::string MQTT_CLIENT_ID =
    "aios-core";

const std::string VEHICLE_STATE_TOPIC =
    "aios/vehicle/state";


int main()
{
    std::cout
        << "====================================\n";

    std::cout
        << "          AIOS Core\n";

    std::cout
        << "====================================\n";


    MqttClient mqtt_client(
        MQTT_SERVER,
        MQTT_CLIENT_ID
    );

    MessageHandler message_handler;

    VehicleStateManager state_manager;

    ContextEngine context_engine;

    EventBus event_bus;


    event_bus.subscribe(
    [
        &state_manager,
        &context_engine
    ](
        const VehicleState& state
    )
    {
        state_manager.update(state);


        VehicleContext context =
            context_engine.evaluate(state);


        std::cout
            << "\n========== AIOS ==========\n";

        std::cout
            << "Speed: "
            << state.speed_kmh
            << " km/h\n";

        std::cout
            << "Battery: "
            << state.battery_percent
            << " %\n";


        std::cout
            << "\n--- Vehicle Context ---\n";

        std::cout
            << "Mode: "
            << context.vehicle_mode
            << "\n";

        std::cout
            << "Speed Level: "
            << context.speed_level
            << "\n";

        std::cout
            << "Energy: "
            << context.energy_status
            << "\n";

        std::cout
            << "Cabin: "
            << context.cabin_condition
            << "\n";

        std::cout
            << "Risk: "
            << context.overall_risk
            << "\n";
    }
);


    try
    {
        std::cout
            << "Connecting to MQTT..."
            << std::endl;

        mqtt_client.connect();

        mqtt_client.subscribe(
            VEHICLE_STATE_TOPIC
        );

        std::cout
            << "Subscribed to: "
            << VEHICLE_STATE_TOPIC
            << std::endl;


        while (true)
        {
            std::string payload =
                mqtt_client.wait_for_message();

            if (payload.empty())
            {
                continue;
            }


            try
            {
                VehicleState state =
                    message_handler
                        .parse_vehicle_state(
                            payload
                        );

                event_bus.publish(state);
            }
            catch (
                const std::exception& error
            )
            {
                std::cerr
                    << "Message processing error: "
                    << error.what()
                    << std::endl;
            }
        }
    }
    catch (
        const std::exception& error
    )
    {
        std::cerr
            << "AIOS Core error: "
            << error.what()
            << std::endl;

        return 1;
    }


    return 0;
}