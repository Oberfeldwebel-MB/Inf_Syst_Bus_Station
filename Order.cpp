#include "Order.hpp"
#include "Search.hpp"
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <ctime>

void Order::PrintOrderInfo() const {
    std::cout << "=== Информация о заказе ===\n";
    std::cout << "ID заказа: " << orderId << "\n";
    std::cout << "Статус оплаты: " << PayStatus << "\n";
    std::cout << "Общая стоимость: " << TotalPrice << " руб.\n";
    std::cout << "Количество билетов: " << TicketList.size() << "\n\n";

    if (TicketList.empty()) {
        std::cout << "Заказ пуст\n";
    }
    else {
        for (const auto& ticket : TicketList) {
            ticket.PrintTicketInfo();
            std::cout << "\n";
        }
    }
    std::cout << "===========================\n";
}

void Order::CalculateTotalPrice() {
    TotalPrice = 0;
    for (const auto& ticket : TicketList) {
        TotalPrice += ticket.GetFinalPrice();
    }
}

void Order::AddTicket(const Ticket& ticket) {
    try {
        // Проверяем, нет ли уже билета с таким номером места
        for (const auto& existing_ticket : TicketList) {
            if (existing_ticket.GetPlaceNumber() == ticket.GetPlaceNumber()) {
                throw std::runtime_error("Билет на место " +
                    std::to_string(ticket.GetPlaceNumber()) + " уже есть в заказе!");
            }
        }

        if (!ticket.IsAvailable()) {
            throw std::runtime_error("Билет на место " +
                std::to_string(ticket.GetPlaceNumber()) + " недоступен!");
        }

        TicketList.push_back(ticket);
        CalculateTotalPrice();

        std::cout << "Билет добавлен в заказ:\n";
        std::cout << "   Место: " << ticket.GetPlaceNumber() << "\n";
        std::cout << "   Пассажир: " << ticket.GetPassenger().GetFullName() << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка добавления билета: " << e.what() << "\n";
        throw;
    }
}

bool Order::RemoveTicket(const Ticket& ticket) {
    try {
        int seatNumber = ticket.GetPlaceNumber();

        for (auto it = TicketList.begin(); it != TicketList.end(); ++it) {
            if (it->GetPlaceNumber() == seatNumber) {
                if (ticketchose != nullptr) {
                    ticketchose->ReleaseSeat(seatNumber);
                }

                TicketList.erase(it);
                CalculateTotalPrice();

                std::cout << "Билет удален из заказа. Место: " << seatNumber << "\n";
                return true;
            }
        }

        throw std::runtime_error("Билет не найден в заказе! Место: " +
            std::to_string(ticket.GetPlaceNumber()));
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка удаления билета: " << e.what() << "\n";
        return false;
    }
}

void Order::PayOrder() {
    try {
        if (TicketList.empty()) {
            throw std::runtime_error("Нельзя оплатить пустой заказ!");
        }

        if (PayStatus == "Оплачен") {
            throw std::runtime_error("Заказ уже оплачен!");
        }

        PayStatus = "Оплачен";
        std::cout << "Заказ " << orderId << " оплачен! Сумма: " << TotalPrice << " руб.\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка оплаты заказа: " << e.what() << "\n";
        throw;
    }
}

void Order::CancelOrder() {
    try {
        if (TicketList.empty()) {
            throw std::runtime_error("Заказ уже пуст!");
        }

        if (ticketchose != nullptr) {
            for (const auto& ticket : TicketList) {
                ticketchose->ReleaseSeat(ticket.GetPlaceNumber());
            }
        }

        TicketList.clear();
        TotalPrice = 0;
        PayStatus = "Отменен";

        std::cout << "Заказ " << orderId << " отменен.\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка отмены заказа: " << e.what() << "\n";
        throw;
    }
}

// ерегрузка оператора
Order& Order::operator+=(const Ticket& ticket) {
    AddTicket(ticket);
    return *this;
}

// дружественная функция 
std::string GenerateOrderReceipt(const Order& order) {
    std::stringstream receipt;

    receipt << "=== КВИТАНЦИЯ ===\n";
    receipt << "Заказ: " << order.orderId << "\n";
    receipt << "Статус: " << order.PayStatus << "\n";
    receipt << "Билетов: " << order.TicketList.size() << "\n";
    receipt << "Итого: " << order.TotalPrice << " руб.\n";

    if (!order.TicketList.empty()) {
        receipt << "----------------\n";
        for (const auto& ticket : order.TicketList) {
            receipt << ticket.GetPlaceNumber() << " | "
                << ticket.GetPassenger().GetFullName() << " | "
                << ticket.GetFinalPrice() << " руб.\n";
        }
    }

    receipt << "=================\n";
    return receipt.str();
}