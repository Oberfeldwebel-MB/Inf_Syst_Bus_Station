#pragma once
#include "Trip.hpp"
#include "Passenger.hpp"
#include "Ticket.hpp"
#include "Order.hpp"
#include <vector>
#include <memory>

class TicketChose {
private:
    std::unique_ptr<Trip> currentTrip;  // Уникальное владение поездкой
    std::vector<int> availableSeats;

public:
    // Конструктор принимает unique_ptr (передает владение)
    TicketChose(std::unique_ptr<Trip> trip);

    // ЗАПРЕЩАЕМ копирование - это опасно для состояния выбора мест!
    TicketChose(const TicketChose&) = delete;
    TicketChose& operator=(const TicketChose&) = delete;

    // Разрешаем перемещение 
    TicketChose(TicketChose&&) = default;
    TicketChose& operator=(TicketChose&&) = default;

    ~TicketChose() = default;

    // Основные методы
    bool IsSeatAvailable(int seatNumber) const;
    void ShowAvailableSeats() const;
    void TicketToOrder(std::shared_ptr<Order> order, int seatNumber,
        const Passenger& passenger, Ticket::TicketType ticketType);
    bool ReserveSeat(int seatNumber);
    void ReleaseSeat(int seatNumber);

    // Геттеры
    const std::vector<int>& GetAvailableSeats() const { return availableSeats; }
    const Trip* GetCurrentTrip() const { return currentTrip.get(); }  // Возвращаем указатель
    bool HasTrip() const { return currentTrip != nullptr; }

    // Информационные методы
    void PrintTicketChoseInfo() const;
};