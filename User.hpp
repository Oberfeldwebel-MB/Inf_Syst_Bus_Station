#pragma once
#include "People.hpp"
#include "Order.hpp"
#include "Search.hpp"
#include "Timing.hpp"
#include "TicketChose.hpp"

class User : public People {
private:
    Order* userOrder;    // Обычный указатель на заказ
    Search search;       // Объект для поиска
    Timing* timing;      // Указатель на расписание

public:
    User(const std::string& surname = "",
        const std::string& name = "",
        const std::string& fatName = "",
        const std::string& psprt_ser = "",
        const std::string& psprt_num = "",
        const std::string& email = "",
        Timing* timingPtr = nullptr);

    ~User() = default;  

    
    void SearchAndBookTicket();  // Поиск и бронирование билета
    void ViewMyOrder() const;    // Просмотр своего заказа
    void InitializeOrder(TicketChose* ticketChose);
    Order* GetOrder() const { return userOrder; }
};