#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include "Trip.hpp"
#include "Ticket.hpp"
#include "Order.hpp"
#include "Timing.hpp" 

class Search {
private:
    std::string SearchOtp;
    std::string SearchPr;
    std::string SearchDate;

public:
    Search(const std::string& otp = "",
        const std::string& pr = "",
        const std::string& date = "")
        : SearchOtp(otp), SearchPr(pr), SearchDate(date) {
    }

    // Поиск в расписании (Timing)
    std::vector<Trip*> SearchTripsByDate(const Timing& timing, const std::string& date);
    std::vector<Trip*> SearchTripsByRoute(const Timing& timing, const std::string& start, const std::string& finish);
    std::vector<Trip*> SearchTripsByDriver(const Timing& timing, const std::string& driverName);
    std::vector<Trip*> SearchTripsByBus(const Timing& timing, const std::string& busCode);
    std::vector<Trip*> SearchTripsCombined(const Timing& timing,
        const std::string& start = "",
        const std::string& finish = "",
        const std::string& date = "");

    // Поиск в заказах (Order)
    std::vector<Ticket*> SearchTicketsByPassenger(const Order& order, const std::string& passengerName);
    std::vector<Ticket*> SearchTicketsByRoute(const Order& order, const std::string& route);
    std::vector<Ticket*> SearchTicketsByType(const Order& order, Ticket::TicketType ticketType);
    std::vector<Ticket*> SearchTicketsBySeat(const Order& order, int seatNumber);
    std::vector<Ticket*> SearchTickets(const Order& order,
        const std::string& passengerName,
        const std::string& route,
        int seatNumber,
        Ticket::TicketType ticketType);
};
