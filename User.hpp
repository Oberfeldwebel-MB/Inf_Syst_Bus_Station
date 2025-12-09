#pragma once
#include "People.hpp"
#include "Order.hpp"
#include "Search.hpp"
#include "Timing.hpp"
#include "TicketChose.hpp"
#include <memory>

class User : public People {
private:
    std::shared_ptr<Order> userOrder;    
    Search search;
    std::shared_ptr<Timing> timing;    

public:
    // Конструктор
    User::User(const std::string& surname,
        const std::string& name,
        const std::string& fatName,
        const std::string& psprtSer,
        const std::string& psprtNum,
        const std::string& email,
        std::shared_ptr<Timing> timingPtr)
        : People(surname, name, fatName, psprtSer, psprtNum, email),
        timing(timingPtr) {
    }

    // Конструктор копирования
    User::User(const User& other)
        : People(other), search(other.search), timing(other.timing) {

        if (other.userOrder) {
            userOrder = std::make_shared<Order>(*other.userOrder);
        }

    }

    ~User() = default;

    void SearchAndBookTicket();
    void ViewMyOrder() const;
    void InitializeOrder(std::shared_ptr<TicketChose> ticketChose);

    std::shared_ptr<Order> GetOrder() const { return userOrder; }
    void SetTiming(std::shared_ptr<Timing> timingPtr) { timing = timingPtr; }
};