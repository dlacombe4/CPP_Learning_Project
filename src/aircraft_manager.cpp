#include "aircraft_manager.hpp"

void AircraftManager::init()
{
    aircraft_factory.init_aircraft_types();
}

void AircraftManager::add(std::unique_ptr<Aircraft> aircraft)
{
    aircrafts.emplace_back(std::move(aircraft));
}

bool AircraftManager::update()
{
    std::sort(aircrafts.begin(), aircrafts.end(), [](std::unique_ptr<Aircraft> &a, std::unique_ptr<Aircraft> &b){
    if(a->is_at_terminal()&& !b -> is_at_terminal()){
    return true;
    }

    if (!a->is_at_terminal() && b->is_at_terminal())
    return false;

    return a -> get_fuel() < b -> get_fuel();
    });

    aircrafts.erase(std::remove_if(aircrafts.begin(), aircrafts.end(), [this](std::unique_ptr<Aircraft> &a) {
        try{
            return !a->update();
        }catch (const AircraftCrash& e){
            crashed_aircrafts++;
            return true;
        }
    }), aircrafts.end());
    return true;
}

int AircraftManager::count(int line)
{
    return std::count_if(aircrafts.begin(), aircrafts.end(),
        [line, this](std::unique_ptr<Aircraft> &a) {
            return a->get_flight_num().substr(0,2) == aircraft_factory.get_airline(line);
        });
}

void AircraftManager::print_count_aircrafts_on_line(int line)
{
    auto airline = aircraft_factory.get_airline(line);
    std::cout << "Nombre d'avion de classe " << airline << " : " << count(line) << std::endl;
}

int AircraftManager::get_crashed_aircrafts() const{
    return crashed_aircrafts;
}
