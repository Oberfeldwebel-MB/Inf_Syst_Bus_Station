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
    static const std::map<TicketType, double> DISCOUNT_COEFFICIENTS; // статическое поле

private:
    int PlaceNumber;
    Trip TripData;
    Passenger PassengerData;
    bool TicketAvail;
    std::string TicketStatus;
    double FinalPrice;
    TicketType Type;

public:
    Ticket(int placeNumber, const Trip& trip, const Passenger& passenger, TicketType type);

    // Конструктор копирования
    Ticket(const Ticket& other);

    ~Ticket() = default;

    void PrintTicketInfo() const;
    void CalculateFinalPrice();
    void Ticked_paid() {
        TicketStatus = "Оплачен";
        std::cout << "Билет оплачен\n";
    }

    // статическая функция
    static double CalculatePrice(double basePrice, TicketType type) {
        return basePrice * DISCOUNT_COEFFICIENTS.at(type);
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