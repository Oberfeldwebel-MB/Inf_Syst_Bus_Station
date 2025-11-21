#pragma once
#include <string>
#include <memory>
#include <iostream>
#include "Bus.hpp"
#include "Driver.hpp"
#include "DriversList.hpp" 
#include "BusList.hpp"

class Trip {
private:
    std::string StartPoint;
    std::string FinishPoint;
    std::string StatusTrip;
    int PriceTicket = 0;
    std::shared_ptr<Bus> BusData;
    std::shared_ptr<Driver> DriverData;

public:
    // Конструктор
    Trip::Trip(const std::string& start,
        const std::string& finish,
        int price,
        std::shared_ptr<Bus> bus,
        std::shared_ptr<Driver> driver)
        : StartPoint(start), FinishPoint(finish), PriceTicket(price),
        BusData(bus), DriverData(driver) {

        StatusTrip = "Запланирована";
        totalTrips++;
    }

    // Конструктор копирования
    Trip::Trip(const Trip& other)
        : StartPoint(other.StartPoint), FinishPoint(other.FinishPoint),
        StatusTrip(other.StatusTrip), PriceTicket(other.PriceTicket),
        BusData(other.BusData), DriverData(other.DriverData) {
        totalTrips++;
    }

    ~Trip() = default;

    // Публичные методы 
    void Change_driver(DriverList& driverList);
    void Change_bus(BusList& busList);

    // методы статуса поездки
    void Start_trip();
    void Complete_trip();
    void Cancel_trip();
    void Print_trip_info() const;

    // Статические поля и методы
    static int totalTrips;
    static int GetTotalTrips() { return totalTrips; }

    // геттеры
    std::string GetRoute() const { return StartPoint + " - " + FinishPoint; }
    std::string GetStatus() const { return StatusTrip; }
    int GetPrice() const { return PriceTicket; }
    std::shared_ptr<Bus> GetBus() const { return BusData; }
    std::shared_ptr<Driver> GetDriver() const { return DriverData; }

    // сеттеры
    void SetStartPoint(const std::string& start) { StartPoint = start; }
    void SetFinishPoint(const std::string& finish) { FinishPoint = finish; }
    void SetPrice(int price) { PriceTicket = price; }
    void SetBus(std::shared_ptr<Bus> bus) { BusData = bus; }
    void SetDriver(std::shared_ptr<Driver> driver) { DriverData = driver; }
};