#include "mqtt_client.hpp"


MqttClient::MqttClient(
    const std::string& server_address,
    const std::string& client_id
)
    : client(
        server_address,
        client_id
    )
{
}


void MqttClient::connect()
{
    client.connect(
        connection_options
    )->wait();

    client.start_consuming();
}


void MqttClient::subscribe(
    const std::string& topic
)
{
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