#pragma once
#include <vector>
#include "Ticket.hpp"
#include "TicketChose.hpp"

class Search;

class Order {
private:
    std::vector<Ticket> TicketList;
    std::string PayStatus;
    double TotalPrice;
    TicketChose* ticketchose = nullptr;
    Search* search;

public:
    Order(TicketChose* chose) : ticketchose(chose) {}

private:
    void CalculateTotalPrice();

public:
    void PrintOrderInfo() const;
    void AddTicket(const Ticket& ticket);
    bool RemoveTicket(const Ticket& ticket);
    void PayOrder();
    void CancelOrder();
    

    // Геттеры
    const std::vector<Ticket>& GetTicketList() const { return TicketList; }
    std::string GetPayStatus() const { return PayStatus; }
    double GetTotalPrice() const { return TotalPrice; }
    bool IsEmpty() const { return TicketList.empty(); }
};
