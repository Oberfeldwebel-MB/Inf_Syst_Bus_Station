#pragma once
#include <vector>
#include <memory>
#include "Bus.hpp"

class BusList {
private:
    std::vector<std::shared_ptr<Bus>> buses;  

public:
    BusList() = default;

    // Конструктор копирования 
    BusList::BusList(const BusList& other) {
        for (const auto& bus : other.buses) {
            // Создаем новые копии автобусов
            buses.push_back(std::make_shared<Bus>(*bus));
        }
    }
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