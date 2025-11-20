#pragma once
#include "People.hpp"
#include "Order.hpp"
#include "Search.hpp"
#include "Timing.hpp"
#include "TicketChose.hpp"
#include <memory>

class User : public People {
private:
    std::shared_ptr<Order> userOrder;    // Заменяем на умный указатель
    Search search;
    std::shared_ptr<Timing> timing;      // Заменяем на умный указатель

public:
    User(const std::string& surname = "",
        const std::string& name = "",
        const std::string& fatName = "",
        const std::string& psprt_ser = "",
        const std::string& psprt_num = "",
        const std::string& email = "",
        std::shared_ptr<Timing> timingPtr = nullptr);

    ~User() = default;

    // Конструктор копирования
    User(const User& other);

    void SearchAndBookTicket();
    void ViewMyOrder() const;
    void InitializeOrder(std::shared_ptr<TicketChose> ticketChose);

    std::shared_ptr<Order> GetOrder() const { return userOrder; }
    void SetTiming(std::shared_ptr<Timing> timingPtr) { timing = timingPtr; }
};