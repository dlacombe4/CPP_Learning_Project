#pragma once

#include "aircraft_factory.hpp"
#include "aircraft_manager.hpp"
#include "aircraft_manager.hpp"

#include <memory>

class Aircraft;
struct AircraftType;
class Airport;

class TowerSimulation
{
private:
    bool help        = false;
    Airport* airport = nullptr;
    AircraftManager manager;
    AircraftFactory aircraft_factory;

    TowerSimulation(const TowerSimulation&) = delete;
    TowerSimulation& operator=(const TowerSimulation&) = delete;

    std::unique_ptr<Aircraft> create_aircraft(const AircraftType& type);
    std::unique_ptr<Aircraft> create_random_aircraft();

    void create_keystrokes();
    void display_help() const;

    void init_airport();

public:
    TowerSimulation(int argc, char** argv);
    ~TowerSimulation();

    void launch();
};
