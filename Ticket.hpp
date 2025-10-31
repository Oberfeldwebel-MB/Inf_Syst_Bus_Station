#pragma once
#include "Trip.hpp"
#include "Passenger.hpp"
#include <iostream>
#include <map>
#include <string>

class Ticket {
   
public:
    enum class TicketType {
        ADULT,      // Взрослый
        CHILD,      // Детский  
        LUGGAGE     // Багажный
    };

private:
    int PlaceNumber;
    Trip TripData;
    Passenger PassengerData;
    bool TicketAvail;
    std::string TicketStatus;
    double FinalPrice;
    TicketType Type;
    
        

public:

    Ticket(int placeNumber, const Trip& trip, const Passenger& passenger, TicketType type)
        : PlaceNumber(placeNumber), TripData(trip), PassengerData(passenger),
        Type(type), TicketAvail(true), TicketStatus("Забронирован") {
        CalculateFinalPrice();
    }

    void PrintTicketInfo() const;
    void CalculateFinalPrice();
    void Ticked_paid() {
        TicketStatus = "Оплачен";
        std::cout << "Билет оплачен\n";
    }

    // Геттеры
    int GetPlaceNumber() const { return PlaceNumber; }
    const Trip& GetTrip() const { return TripData; }
    
    const Passenger& GetPassenger() const { return PassengerData; }
    
    TicketType GetTicketType() const { return Type; }
    std::string GetTicketTypeName() const;

    bool IsAvailable() const { return TicketAvail; }
    std::string GetStatus() const { return TicketStatus; }
    double GetFinalPrice() const { return FinalPrice; }


};
