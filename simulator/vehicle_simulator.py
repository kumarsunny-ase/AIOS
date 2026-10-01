import json
import random
import time
from datetime import datetime, timezone

import paho.mqtt.client as mqtt

from mqtt_config import (
    MQTT_BROKER,
    MQTT_PORT,
    VEHICLE_STATE_TOPIC,
)


class Vehicle:
    def __init__(self):
        self.speed = 0.0
        self.battery = 100.0
        self.cabin_temperature = 22.0
        self.engine_on = True
        self.doors_locked = True
        self.latitude = 49.1406
        self.longitude = 9.2200

    def update(self):
        # Speed changes
        self.speed = max(0, min(130, self.speed + random.uniform(-5, 5)))

        # Battery consumption
        if self.engine_on and self.speed > 0:
            self.battery = max(0, self.battery - 0.02)

        # Cabin temperature changes
        self.cabin_temperature += random.uniform(-0.2, 0.2)

        # GPS movement
        if self.speed > 0:
            self.latitude += random.uniform(-0.0001, 0.0001)
            self.longitude += random.uniform(-0.0001, 0.0001)

    def get_state(self):
        # Key names MUST match the C++ MessageHandler
        return {
            "timestamp": datetime.now(timezone.utc).isoformat(),
            "speed_kmh": round(self.speed, 2),
            "battery_percent": round(self.battery, 2),
            "cabin_temperature_c": round(self.cabin_temperature, 2),
            "engine_on": self.engine_on,
            "doors_locked": self.doors_locked,
            "latitude": round(self.latitude, 6),
            "longitude": round(self.longitude, 6),
        }


def create_mqtt_client():
    client = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)
    client.connect(MQTT_BROKER, MQTT_PORT, 60)
    client.loop_start()  # keeps the connection alive in the background
    return client


def main():
    vehicle = Vehicle()
    mqtt_client = create_mqtt_client()

    print("================================")
    print(" AIOS Vehicle Simulator Started")
    print(f" Publishing to: {VEHICLE_STATE_TOPIC}")
    print("================================")

    try:
        while True:
            vehicle.update()
            message = json.dumps(vehicle.get_state())

            result = mqtt_client.publish(VEHICLE_STATE_TOPIC, message)
            result.wait_for_publish()  # confirms it really reached the broker

            print("\n--- Vehicle State Published ---")
            print(message)

            time.sleep(1)
    except KeyboardInterrupt:
        print("\nSimulator stopped.")
    finally:
        mqtt_client.loop_stop()
        mqtt_client.disconnect()


if __name__ == "__main__":
    main()