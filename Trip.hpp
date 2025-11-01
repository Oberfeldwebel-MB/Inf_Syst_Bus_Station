#pragma once

#include <string>
#include "Bus.hpp"
#include "Driver.hpp"
#include "Admin.hpp"
#include "DriversList.hpp"
#include "BusList.hpp"

class Trip {
private:
    std::string StartPoint;
    std::string FinishPoint;
    std::string StatusTrip;
    int PriceTicket = 0;
    Bus* BusData;
    Driver* DriverData;

public:
    // Конструктор
    Trip(const std::string& start = "",
        const std::string& finish = "",
        int price = 0,
        Bus* bus = nullptr,
        Driver* driver = nullptr)
        : StartPoint(start), FinishPoint(finish), PriceTicket(price),
        BusData(bus), DriverData(driver) {
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
    std::string GetRoute() const { return StartPoint + " - " + FinishPoint; }
    std::string GetStatus() const { return StatusTrip; }
    int GetPrice() const { return PriceTicket; }
    const Bus* GetBus() const { return BusData; }
    const Driver* GetDriver() const { return DriverData; }
};