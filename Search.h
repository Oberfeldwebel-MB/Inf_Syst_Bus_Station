#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include "Trip.h"
#include "Ticket.h"
#include "Order.h"
#include "Timing.h" 

class Search {
private:
    std::string Search_otp;
    std::string Search_pr;
    std::string Search_date;

public:
    Search(const std::string& otp = "",
        const std::string& pr = "",
        const std::string& date = "")
        : Search_otp(otp), Search_pr(pr), Search_date(date) {
    }

    // Поиск в расписании (Timing)
    std::vector<Trip*> SearchTripsByDate(const Timing& timing, const std::string& date);
    std::vector<Trip*> SearchTripsByRoute(const Timing& timing, const std::string& start, const std::string& finish);
    std::vector<Trip*> SearchTripsByDriver(const Timing& timing, const std::string& driver_name);
    std::vector<Trip*> SearchTripsByBus(const Timing& timing, const std::string& bus_code);
    std::vector<Trip*> SearchTripsCombined(const Timing& timing,
        const std::string& start = "",
        const std::string& finish = "",
        const std::string& date = "");

    // Поиск в заказах (Order)
    std::vector<Ticket*> SearchTicketsByPassenger(const Order& order, const std::string& passenger_name);
    std::vector<Ticket*> SearchTicketsByRoute(const Order& order, const std::string& route);
    std::vector<Ticket*> SearchTicketsByType(const Order& order, int type_index);
    std::vector<Ticket*> SearchTicketsBySeat(const Order& order, int seat_number);
    std::vector<Ticket*> SearchTickets(const Order& order,
        const std::string& passenger_name,
        const std::string& route,
        int seat_number,
        int type_index);
};
