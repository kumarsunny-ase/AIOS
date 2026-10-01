#include "mqtt_client.hpp"

#include <iostream>


MqttClient::MqttClient(
    const std::string& server_address,
    const std::string& client_id
)
    : client(
        server_address,
        client_id
    )
{
    connection_options.set_clean_session(true);
}


void MqttClient::connect()
{
    std::cout
        << "Connecting to broker..."
        << std::endl;

    client.connect(
        connection_options
    )->wait();

    std::cout
        << "Connected to MQTT broker."
        << std::endl;

    client.start_consuming();
}


void MqttClient::subscribe(
    const std::string& topic
)
{
    std::cout
        << "Subscribing to: "
        << topic
        << std::endl;

    client.subscribe(
        topic,
        1
    )->wait();
}


std::string MqttClient::wait_for_message()
{
    auto message =
        client.consume_message();

    if (!message)
    {
        return "";
    }

    return message->to_string();
}