import random
import time


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
            "speed_kmh": round(self.speed, 2),
            "battery_percentage": round(self.battery, 2),
            "cabin_temperature": round(self.cabin_temperature, 2),
            "engine_on": self.engine_on,
            "doors_locked": self.doors_locked,
            "latitude": round(self.latitude, 6),
            "longitude": round(self.longitude, 6)
        }
    

def main():
    vehicle = Vehicle()

    print("AIOS Vehicle Simulator Started")
    print("================================")

    while True:
        vehicle.update()
        state = vehicle.get_state()
        print("\n--- Vehicle State ---")
        print(f"Speed:       {state['speed_kmh']} km/h")
        print(f"Battery:     {state['battery_percentage']} %")
        print(f"Cabin Temp:  {state['cabin_temperature']} °C")
        print(f"Engine:      {'ON' if state['engine_on'] else 'OFF'}")
        print(f"Doors:       {'LOCKED' if state['doors_locked'] else 'UNLOCKED'}")
        print(
            f"Location:    "
            f"{state['latitude']}, "
            f"{state['longitude']}"
        )

        
        time.sleep(1)


if __name__ == "__main__":
    main()