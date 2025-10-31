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
    Trip* ChoseTrip();
    void AddTrip(const Trip& trip);
    void DisplayAllTrips() const;
    void DisplayActiveTrips() const;      // Только активные поездки
    void DisplayCompletedTrips() const;   // Только завершенные
    void DisplayPlannedTrips() const;     // Только запланированные


    std::vector<Trip>& GetTripList() { return tripList; }
    const std::vector<Trip>& GetTripList() const { return tripList; }
};
