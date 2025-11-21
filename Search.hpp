#pragma once
#include <string>
#include <vector>
#include <memory>
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
    // конструктор
    Search(const std::string& otp = "",
        const std::string& pr = "",
        const std::string& date = "")
        : SearchOtp(otp), SearchPr(pr), SearchDate(date) {
    }

    // ѕоиск в расписании (Timing) 
    std::vector<std::shared_ptr<Trip>> SearchTripsByDate(const Timing& timing, const std::string& date);
    std::vector<std::shared_ptr<Trip>> SearchTripsByRoute(const Timing& timing, const std::string& start, const std::string& finish);
    std::vector<std::shared_ptr<Trip>> SearchTripsByDriver(const Timing& timing, const std::string& driverName);
    std::vector<std::shared_ptr<Trip>> SearchTripsByBus(const Timing& timing, const std::string& busCode);
    std::vector<std::shared_ptr<Trip>> SearchTripsCombined(const Timing& timing,
        const std::string& start = "",
        const std::string& finish = "",
        const std::string& date = "");

    // ѕоиск в заказах (Order)
    std::vector<std::shared_ptr<Ticket>> SearchTickets(const Order& order,
        const std::string& passengerName,
        const std::string& route,
        int seatNumber,
        Ticket::TicketType ticketType);
    std::vector<std::shared_ptr<Ticket>> SearchTicketsByRoute(const Order& order, const std::string& route);
    std::vector<std::shared_ptr<Ticket>> SearchTicketsByType(const Order& order, Ticket::TicketType ticketType);
    std::vector<std::shared_ptr<Ticket>> SearchTicketsBySeat(const Order& order, int seatNumber);

    //перегрузка оператора вывода
    friend std::ostream& operator<<(std::ostream& os, const Search& search);
};