#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include "Trip.hpp"

class Timing {
private:
    std::vector<std::shared_ptr<Trip>> tripList;  // Заменяем на умные указатели

public:
    Timing() = default;
    ~Timing() = default;

    // Конструктор копирования
    Timing(const Timing& other);

    // Управление расписанием
    std::shared_ptr<Trip> ChoseTrip();  
    void AddTrip(std::shared_ptr<Trip> trip); 
    bool RemoveTrip(const std::string& route);
    void DisplayAllTrips() const;
    void DisplayActiveTrips() const;
    void DisplayCompletedTrips() const;
    void DisplayPlannedTrips() const;

    // Геттеры
    std::vector<std::shared_ptr<Trip>>& GetTripList() { return tripList; }
    const std::vector<std::shared_ptr<Trip>>& GetTripList() const { return tripList; }
};