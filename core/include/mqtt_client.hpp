#pragma once

#include <string>

#include <mqtt/async_client.h>


class MqttClient
{
public:

    MqttClient(
        const std::string& server_address,
        const std::string& client_id
    );

    void connect();

    void subscribe(
        const std::string& topic
    );

    std::string wait_for_message();

private:

    mqtt::async_client client;
    mqtt::connect_options connection_options;
};