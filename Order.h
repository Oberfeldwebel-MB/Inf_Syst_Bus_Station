#pragma once
#include <vector>
#include "Ticket.h"
#include "TicketChose.h"

class Search;

class Order {
private:
    std::vector<Ticket> TicketList;
    std::string Pay_status;
    double Total_price;
    TicketChose* ticket_chose = nullptr;
    Search* search;

public:
    Order(TicketChose* chose) : ticket_chose(chose) {}

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
    std::string GetPayStatus() const { return Pay_status; }
    double GetTotalPrice() const { return Total_price; }
    bool IsEmpty() const { return TicketList.empty(); }
};
