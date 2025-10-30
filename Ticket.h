#pragma once
#include "Trip.h"
#include "Passenger.h"
#include <iostream>
#include <map>
#include <string>

class Ticket {
    

private:
    int Place_number;
    Trip Trip_data;
    Passenger Passenger_data;
    bool Ticket_avail;
    std::string Ticket_status;
    double Final_price;
    int Ticket_type_index;
    std::map<int, std::string> Ticket_types = {
    {0, "Взрослый"},
    {1, "Детский"},
    {2, "Багажный"}
    };
        

public:
    Ticket(int place_number, const Trip& trip, const Passenger& passenger, int type_index)
        : Place_number(place_number), Trip_data(trip), Passenger_data(passenger),
        Ticket_type_index(type_index), Ticket_avail(true), Ticket_status("Забронирован") {
        CalculateFinalPrice();
    }

    void Print_ticket_info() const;
    void CalculateFinalPrice();
    void Ticked_paid() {
        Ticket_status = "Оплачен";
        std::cout << "Билет оплачен\n";
    }

    // Геттеры
    int GetPlaceNumber() const { return Place_number; }
    const Trip& GetTrip() const { return Trip_data; }
    
    const Passenger& GetPassenger() const { return Passenger_data; }
    
    int GetTicketTypeIndex() const { return Ticket_type_index; };
    std::string GetTicketTypeName() const { return Ticket_types.at(Ticket_type_index);}

    bool IsAvailable() const { return Ticket_avail; }
    std::string GetStatus() const { return Ticket_status; }
    double GetFinalPrice() const { return Final_price; }


};
