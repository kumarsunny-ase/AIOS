# AIOS v0.1 Architecture

## Purpose

AIOS v0.1 is the first prototype of an Automotive Intelligence Runtime.

The initial version does not connect to a real vehicle. Instead, a Vehicle Simulator generates real-time vehicle data.

## Components

### 1. Vehicle Simulator

Generates simulated vehicle information:

- Speed
- Battery level
- Cabin temperature
- GPS location
- Door status

### 2. Communication Layer

Transfers vehicle data to the AIOS Core.

The initial prototype will use an event-driven messaging approach.

### 3. AIOS Core

Responsible for:

- Receiving vehicle data
- Validating messages
- Maintaining the current vehicle state
- Managing internal events

### 4. Context Engine

Transforms raw vehicle data into meaningful context.

Example:

Raw data:

- Speed: 120 km/h
- Battery: 10%

Context:

The vehicle is travelling at high speed while battery energy is critically low.

## Initial Data Flow

Vehicle Simulator

↓

Communication Layer

↓

AIOS Core

↓

Vehicle State Manager

↓

Context Engine


## Current Architecture

AIOS currently uses an event-driven communication model.

```text
Vehicle Simulator
       │
       │ MQTT
       ▼
MQTT Broker
       │
       ▼
Subscribers