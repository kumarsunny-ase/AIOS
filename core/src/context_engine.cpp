#include "context_engine.hpp"


VehicleContext ContextEngine::evaluate(const VehicleState& state) const
{
    VehicleContext context;

    // Vehicle mode
    if (!state.engine_on)
        context.vehicle_mode = "OFF";
    else if (state.speed_kmh < 1.0)
        context.vehicle_mode = "STATIONARY";
    else
        context.vehicle_mode = "DRIVING";

    // Speed level
    if (state.speed_kmh < 30)
        context.speed_level = "LOW";
    else if (state.speed_kmh < 90)
        context.speed_level = "NORMAL";
    else
        context.speed_level = "HIGH";

    // Energy status
    if (state.battery_percent < 10)
        context.energy_status = "CRITICAL";
    else if (state.battery_percent < 25)
        context.energy_status = "LOW";
    else
        context.energy_status = "NORMAL";

    // Cabin condition
    if (state.cabin_temperature_c < 16)
        context.cabin_condition = "COLD";
    else if (state.cabin_temperature_c > 26)
        context.cabin_condition = "HOT";
    else
        context.cabin_condition = "COMFORTABLE";

    // Overall risk
    bool critical_energy = context.energy_status == "CRITICAL";
    bool high_speed = context.speed_level == "HIGH";

    if (critical_energy && high_speed)
        context.overall_risk = "HIGH";
    else if (critical_energy || high_speed)
        context.overall_risk = "MEDIUM";
    else
        context.overall_risk = "LOW";

    return context;
}