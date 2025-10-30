#pragma once
#include <vector>
#include <iostream>

class Trip;

class Timing {
private:
    std::vector<Trip> tripList;

public:
    Timing() = default;
    ~Timing() = default;

    // Управление расписанием
    Trip* Chose_trip();
    void Add_trip(const Trip& trip);
    void Display_all_trips() const;
    void Display_active_trips() const;      // Только активные поездки
    void Display_completed_trips() const;   // Только завершенные
    void Display_planned_trips() const;     // Только запланированные


    std::vector<Trip>& GetTripList() { return tripList; }
    const std::vector<Trip>& GetTripList() const { return tripList; }
};
