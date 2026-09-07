## AIOS Core

The AIOS Core is implemented in C++ and acts as the central runtime for the Automotive Intelligence OS.

### Current Responsibilities

- Subscribe to real-time vehicle events.
- Receive MQTT messages.
- Parse JSON payloads.
- Maintain the latest vehicle state.

### Current Data Flow

```text
Vehicle Simulator
       ↓
MQTT Broker
       ↓
AIOS Core
       ↓
VehicleState