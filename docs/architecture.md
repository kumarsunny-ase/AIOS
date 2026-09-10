## AIOS Core Architecture

The AIOS Core is organized into independent components.

### Components

- MqttClient — handles MQTT communication.
- MessageHandler — parses incoming vehicle messages.
- VehicleStateManager — maintains the latest vehicle state.
- EventBus — distributes vehicle state events.
- VehicleState — represents the current vehicle state.

### Data Flow

```text
Vehicle Simulator
       ↓
MQTT Broker
       ↓
MqttClient
       ↓
MessageHandler
       ↓
VehicleState
       ↓
EventBus
       ↓
VehicleStateManager