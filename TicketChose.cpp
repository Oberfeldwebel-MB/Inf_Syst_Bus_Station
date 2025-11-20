#include "TicketChose.hpp"
#include <iostream>
#include <stdexcept>
#include <algorithm>


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

bool TicketChose::IsSeatAvailable(int seatNumber) const {
    try {
        if (seatNumber <= 0) {
            throw std::invalid_argument("Номер места должен быть положительным!");
        }

        return std::find(availableSeats.begin(), availableSeats.end(), seatNumber) != availableSeats.end();
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка проверки места: " << e.what() << "\n";
        return false;
    }
}

bool TicketChose::ReserveSeat(int seatNumber) {
    try {
        if (seatNumber <= 0) {
            throw std::invalid_argument("Номер места должен быть положительным!");
        }

        auto it = std::find(availableSeats.begin(), availableSeats.end(), seatNumber);
        if (it == availableSeats.end()) {
            std::cout << "[TicketChose] Место " << seatNumber << " уже занято!\n";
            return false;  // Место уже занято
        }

        availableSeats.erase(it);
        std::cout << "[TicketChose] Место " << seatNumber << " успешно забронировано\n";
        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка резервирования места: " << e.what() << "\n";
        return false;
    }
}

void TicketChose::ReleaseSeat(int seatNumber) {
    try {
        if (seatNumber <= 0) {
            throw std::invalid_argument("Номер места должен быть положительным!");
        }

        // Добавляем место обратно, если его еще нет в списке
        if (!IsSeatAvailable(seatNumber)) {
            availableSeats.push_back(seatNumber);
            std::sort(availableSeats.begin(), availableSeats.end());
            std::cout << "[TicketChose] Место " << seatNumber << " освобождено\n";
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка освобождения места: " << e.what() << "\n";
        throw;
    }
}

void TicketChose::ShowAvailableSeats() const {
    std::cout << "=== Доступные места ===\n";

    if (!currentTrip) {
        std::cout << "Ошибка: поездка не установлена!\n";
        return;
    }

    std::shared_ptr<Bus> bus = currentTrip->GetBus();
    if (bus) {
        std::cout << "Автобус: " << bus->GetBrand()
            << " [" << bus->GetCode() << "]\n";
        std::cout << "Маршрут: " << currentTrip->GetRoute() << "\n";
        std::cout << "Всего мест: " << bus->GetPlaces()
            << ", свободно: " << availableSeats.size() << "\n\n";
    }

    if (availableSeats.empty()) {
        std::cout << "Нет свободных мест!\n";
    }
    else {
        std::cout << "Свободные места: ";
        for (size_t i = 0; i < availableSeats.size(); ++i) {
            std::cout << availableSeats[i];
            if (i < availableSeats.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "\n";
    }
    std::cout << "========================\n";
}

void TicketChose::TicketToOrder(std::shared_ptr<Order> order, int seatNumber,
    const Passenger& passenger, Ticket::TicketType ticketType) {
    try {
        if (!order) {
            throw std::invalid_argument("Заказ не может быть пустым!");
        }

        if (seatNumber <= 0) {
            throw std::invalid_argument("Номер места должен быть положительным!");
        }

        if (!currentTrip) {
            throw std::runtime_error("Поездка не установлена в TicketChose!");
        }

        // Проверяем доступность места
        auto it = std::find(availableSeats.begin(), availableSeats.end(), seatNumber);
        if (it == availableSeats.end()) {
            throw std::runtime_error("Место " + std::to_string(seatNumber) + " уже занято или не существует!");
        }

        // Резервируем место
        availableSeats.erase(it);

        // Создаем билет (используем разыменованный unique_ptr)
        Ticket newTicket(seatNumber, *currentTrip, passenger, ticketType);

        // Добавляем билет в Order
        order->AddTicket(newTicket);

        std::cout << "   Билет успешно забронирован!\n";
        std::cout << "   Место: " << seatNumber << "\n";
        std::cout << "   Тип: " << newTicket.GetTicketTypeName() << "\n";
        std::cout << "   Цена: " << newTicket.GetFinalPrice() << " руб.\n";
        std::cout << "   Пассажир: " << passenger.GetFullName() << "\n";
        std::cout << "   Маршрут: " << currentTrip->GetRoute() << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка бронирования билета: " << e.what() << "\n";
        throw;
    }
}

void TicketChose::PrintTicketChoseInfo() const {
    std::cout << "=== Информация о выборе мест ===\n";
    if (currentTrip) {
        std::cout << "Поездка: " << currentTrip->GetRoute() << "\n";
        std::cout << "Статус: " << currentTrip->GetStatus() << "\n";
    }
    else {
        std::cout << "Поездка: не установлена\n";
    }
    std::cout << "Доступно мест: " << availableSeats.size() << "\n";
    std::cout << "===============================\n";
}