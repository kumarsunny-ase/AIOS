#include <cassert>
#include <iostream>

#include "context_engine.hpp"

int main()
{
    ContextEngine engine;

    // Test 1: high speed + critical battery + cold
    {
        VehicleState s;
        s.engine_on = true;
        s.speed_kmh = 120;
        s.battery_percent = 8;
        s.cabin_temperature_c = 5;

        VehicleContext c = engine.evaluate(s);
        assert(c.vehicle_mode == "DRIVING");
        assert(c.speed_level == "HIGH");
        assert(c.energy_status == "CRITICAL");
        assert(c.cabin_condition == "COLD");
        assert(c.overall_risk == "HIGH");
    }

    // Test 2: normal city driving
    {
        VehicleState s;
        s.engine_on = true;
        s.speed_kmh = 50;
        s.battery_percent = 80;
        s.cabin_temperature_c = 22;

        VehicleContext c = engine.evaluate(s);
        assert(c.speed_level == "NORMAL");
        assert(c.energy_status == "NORMAL");
        assert(c.cabin_condition == "COMFORTABLE");
        assert(c.overall_risk == "LOW");
    }

    // Test 3: engine off
    {
        VehicleState s;
        s.engine_on = false;

        VehicleContext c = engine.evaluate(s);
        assert(c.vehicle_mode == "OFF");
    }

    std::cout << "All ContextEngine tests passed." << std::endl;
    return 0;
}