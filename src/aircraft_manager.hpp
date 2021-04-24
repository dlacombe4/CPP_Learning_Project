#pragma once

#include "GL/dynamic_object.hpp"
#include "aircraft.hpp"
#include "aircraft_factory.hpp"

#include <algorithm>
#include <memory>
#include <vector>

class AircraftManager : public GL::DynamicObject
{
private:
    std::vector<std::unique_ptr<Aircraft>> aircrafts;
    AircraftFactory aircraft_factory;
    int crashed_aircrafts = 0;

public:
    void init();
    void add(std::unique_ptr<Aircraft> aircraft);
    bool update() override;
    int count(int line);
    void print_count_aircrafts_on_line(int line);
    int get_crashed_aircrafts() const;
    float get_required_fuel() const;
};
