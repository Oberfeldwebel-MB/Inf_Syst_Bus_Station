#pragma once
#include "Trip.h"
#include "Passenger.h"
#include "Ticket.h"
#include <vector>
#include <iostream>

class Order;

class TicketChose {
private:
    Trip current_trip;
    std::vector<int> available_seats;  //номера свободных мест

public:
    TicketChose(const Trip& trip);

    // Основные методы
    bool IsSeatAvailable(int seat_number) const;
    void ShowAvailableSeats() const;
    void Ticket_to_order(Order& order, int seat_number, const Passenger& passenger, int type_index);
    bool ReserveSeat(int seat_number);      // Резервирование места
    void ReleaseSeat(int seat_number);      // Освобождение места

    // Информационные методы
    const std::vector<int>& GetAvailableSeats() const { return available_seats; }
    const Trip& GetCurrentTrip() const { return current_trip; }

};