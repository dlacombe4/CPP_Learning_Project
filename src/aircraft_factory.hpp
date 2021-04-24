#pragma once

#include "aircraft.hpp"
#include "airport.hpp"

#include <experimental/random>
#include <string>
#include <vector>

constexpr size_t NUM_AIRCRAFT_TYPES = 3;

class AircraftFactory
{
    private:
        AircraftType* aircraft_types[NUM_AIRCRAFT_TYPES] {};
        const std::string airlines[8] = { "AF", "LH", "EY", "DL", "KL", "BA", "AY", "EY" };
        std::vector<std::string> flight_numbers;

    public:
        void init_aircraft_types();
        std::unique_ptr<Aircraft> create_aircraft(const AircraftType& type, Airport* airport);
        std::unique_ptr<Aircraft> create_random_aircraft(Airport* airport);
        void delete_flight_number(std::unique_ptr<Aircraft>&);
        std::string get_airline(int x);
};
