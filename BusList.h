#pragma once
#pragma once
#include <vector>
#include "Bus.h"

class BusList {
private:
    std::vector<Bus> buses;

public:

    BusList() = default;
    ~BusList() = default;
    std::vector<Bus>& GetBuses(){ return buses; }

    void Add_Bus(const Bus& bus);
    bool Remove_Bus(const std::string& code);
    Bus* Find_Bus_By_Code(const std::string& code);
    void Display_All_Buses();

};
