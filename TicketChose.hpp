#pragma once
#include "Trip.hpp"
#include "Passenger.hpp"
#include "Ticket.hpp"
#include "Order.hpp"
#include <vector>
#include <memory>

class TicketChose {
private:
    std::unique_ptr<Trip> currentTrip;  
    std::vector<int> availableSeats;

public:
    // Конструктор
    TicketChose::TicketChose(std::unique_ptr<Trip> trip)
        : currentTrip(std::move(trip)) {

        try {
            if (!currentTrip) {
                throw std::invalid_argument("Нельзя создать TicketChose с пустой поездкой!");
            }

            std::shared_ptr<Bus> bus = currentTrip->GetBus();
            if (!bus) {
                throw std::invalid_argument("Не указан автобус для поездки!");
            }

            int totalSeats = bus->GetPlaces();
            if (totalSeats <= 0) {
                throw std::invalid_argument("Количество мест в автобусе должно быть положительным!");
            }

            // Заполняем доступные места (от 1 до количества мест в автобусе)
            for (int i = 1; i <= totalSeats; i++) {
                availableSeats.push_back(i);
            }

            std::cout << "Создан выбор мест для поездки: "
                << currentTrip->GetRoute() << " (мест: " << totalSeats << ")\n";
        }
        catch (const std::exception& e) {
            std::cerr << "Ошибка создания TicketChose: " << e.what() << "\n";
            throw;
        }
    }

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