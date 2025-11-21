#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Ticket.hpp"
#include "TicketChose.hpp"

class Search;

class Order {
private:
    std::vector<Ticket> TicketList;
    std::string PayStatus;
    double TotalPrice;
    std::shared_ptr<TicketChose> ticketchose;
    std::shared_ptr<Search> search;
    std::string orderId;

public:
    //конструктор
    Order::Order(std::shared_ptr<TicketChose> chose)
        : ticketchose(chose), PayStatus("Не оплачен"), TotalPrice(0.0) {
    }

    //конструктор копирования
    Order::Order(const Order& other)
        : TicketList(other.TicketList), PayStatus(other.PayStatus),
        TotalPrice(other.TotalPrice), ticketchose(other.ticketchose),
        search(other.search), orderId(other.orderId + "_copy") {
    }

    ~Order() = default;

    void PrintOrderInfo() const;
    void AddTicket(const Ticket& ticket);
    bool RemoveTicket(const Ticket& ticket);
    void PayOrder();
    void CancelOrder();
    void CalculateTotalPrice();

    //перегрузка оператора (добавляем новый билет)
    Order& operator+=(const Ticket& ticket);

    // дружественная функция 
    friend std::string GenerateOrderReceipt(const Order& order);

    // Геттеры
    const std::vector<Ticket>& GetTicketList() const { return TicketList; }
    std::string GetPayStatus() const { return PayStatus; }
    double GetTotalPrice() const { return TotalPrice; }
    bool IsEmpty() const { return TicketList.empty(); }
    std::string GetOrderId() const { return orderId; }

    void SetSearch(std::shared_ptr<Search> searchPtr) { search = searchPtr; }
};