#pragma once

#include <string>
#include "Bus.h"
#include "Driver.h"
#include "Admin.h"
#include "DriversList.h"
#include "BusList.h"

class Trip {
private:
    std::string Start_point;
    std::string Finish_point;
    std::string Status_tr;
    int Price_tick = 0;
    Bus* Bus_data;
    Driver* Driver_data;

public:
    // Конструктор
    Trip(const std::string& start = "",
        const std::string& finish = "",
        int price = 0,
        Bus* bus = nullptr,
        Driver* driver = nullptr)
        : Start_point(start), Finish_point(finish), Price_tick(price),
        Bus_data(bus), Driver_data(driver) {
    }

    // Публичные методы 
    void Change_driver(DriverList& driverList);
    void Change_bus(BusList& busList);
    void Buy_ticket();
    // методы статуса поездки
    void Start_trip();
    void Complete_trip();
    void Cancel_trip();
    void Print_trip_info() const;
    
    // геттеры
    std::string GetRoute() const { return Start_point + " - " + Finish_point; }
    std::string GetStatus() const { return Status_tr; }
    int GetPrice() const { return Price_tick; }
    const Bus* GetBus() const { return Bus_data; }
    const Driver* GetDriver() const { return Driver_data; }
};