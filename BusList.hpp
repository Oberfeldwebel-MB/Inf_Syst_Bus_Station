#pragma once
#pragma once
#include <vector>
#include "Bus.hpp"

class BusList {
private:
    std::vector<Bus> buses;

public:

    BusList() = default;
    ~BusList() = default;
    std::vector<Bus>& GetBuses(){ return buses; }

    void AddBus(const Bus& bus);
    bool RemoveBus(const std::string& code);
    Bus* FindBusByCode(const std::string& code);
    void DisplayAllBuses();

};
