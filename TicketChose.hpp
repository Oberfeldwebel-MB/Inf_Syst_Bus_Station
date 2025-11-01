#pragma once
#include "Trip.hpp"
#include "Passenger.hpp"
#include "Ticket.hpp"
#include <vector>
#include <iostream>

class Order;

class TicketChose {
private:
    Trip currentTrip;
    std::vector<int> availableSeats;  //номера свободных мест

public:
    TicketChose(const Trip& trip);

    // Основные методы
    bool IsSeatAvailable(int seatNumber) const;
    void ShowAvailableSeats() const;
    void TicketToOrder(Order& order, int seatNumber, const Passenger& passenger, Ticket::TicketType ticketType);
    bool ReserveSeat(int seatNumber);      // Резервирование места
    void ReleaseSeat(int seatNumber);      // Освобождение места

    // Информационные методы
    const std::vector<int>& GetAvailableSeats() const { return availableSeats; }
    const Trip& GetCurrentTrip() const { return currentTrip; }

};