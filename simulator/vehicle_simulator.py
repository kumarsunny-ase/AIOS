import datetime
import json
import random
import time


import paho.mqtt.client as mqtt

from mqtt_config import (
    MQTT_BROKER,
    MQTT_PORT, 
    VEHICLE_STATUS_TOPIC,
)

class Vehicle:
    def __init__(self):
        self.speed = 0.0
        self.position = 80.0
        self.cabin_temperature = 22.0
        self.battery = 100.0
        self.engine_on = True
        self.doors_locked = True

        self.latitude = 49.1406
        self.longitude = 9.2200

    def update(self):

        #Simulate speed changes
        speed_change = random.uniform(-5, 5)
        self.speed = max(0,min(130, self.speed + speed_change))

        #Simulate battery consumption
        if self.engine_on and self.speed > 0:
            self.battery -= 0.02

        # Keep the battery in valid range
        self.battery = max(0.0, min(100.0, self.battery))

        # simulate GPS movement
        if self.speed > 0:
            self.latitude += random.uniform(-0.0001, 0.0001)
            self.longitude += random.uniform(-0.0001, 0.0001)

    def get_state(self):
        return {
            "timestamp": datetime.datetime.now(datetime.timezone.utc).isoformat(),
            "speed_kmh": round(self.speed, 2),
            "battery_percentage": round(self.battery, 2),
            "cabin_temperature": round(self.cabin_temperature, 2),
            "engine_on": self.engine_on,
            "doors_locked": self.doors_locked,
            "latitude": round(self.latitude, 6),
            "longitude": round(self.longitude, 6)
        }
    
def create_mqtt_client():
    """
    Creates and conncets an MQTT client instance.
    """
    client = mqtt.Client(
        mqtt.CallbackAPIVersion.VERSION2
    )
    client.connect(MQTT_BROKER, MQTT_PORT, 60)
    return client


def main():
    vehicle = Vehicle()

    mqtt_client = create_mqtt_client()

    print("AIOS Vehicle Simulator Started")
    print("MQTT Connected")
    print("================================")

    while True:
        vehicle.update()
        state = vehicle.get_state()

        #Convert Python dictionary to JSON string
        message = json.dumps(state)

        #Publish vehicle state
        mqtt_client.publish(VEHICLE_STATUS_TOPIC, message)

        print("\n--- Vehicle State Published ---")
        print(message)
        
        time.sleep(1)


if __name__ == "__main__":
    main()