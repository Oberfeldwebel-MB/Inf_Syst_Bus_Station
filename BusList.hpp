#pragma once
#include <vector>
#include <memory>
#include "Bus.hpp"

class BusList {
private:
    std::vector<std::shared_ptr<Bus>> buses;  

public:
    BusList() = default;
    ~BusList() = default;

   

    std::vector<std::shared_ptr<Bus>>& GetBuses() { return buses; }

    //  методы с умными указателями
    void AddBus(std::shared_ptr<Bus> bus);
    bool RemoveBus(const std::string& code);
    std::shared_ptr<Bus> FindBusByCode(const std::string& code);  

    // Перегрузка операторов 
    friend std::ostream& operator<<(std::ostream& os, const BusList& busList);

    void DisplayAllBuses() const;
};