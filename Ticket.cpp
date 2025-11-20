#include "Ticket.hpp"
#include <iostream>
#include <stdexcept>
#include <map>


// Конструктор
Ticket::Ticket(int placeNumber, const Trip& trip, const Passenger& passenger, TicketType type)
    : PlaceNumber(placeNumber), TripData(trip), PassengerData(passenger),
    Type(type), TicketAvail(true), TicketStatus("Забронирован") {

    if (placeNumber <= 0) {
        throw std::invalid_argument("Номер места должен быть положительным!");
    }

    CalculateFinalPrice();
    totalTickets++;
}

// Конструктор копирования
Ticket::Ticket(const Ticket& other)
    : PlaceNumber(other.PlaceNumber), TripData(other.TripData),
    PassengerData(other.PassengerData), TicketAvail(other.TicketAvail),
    TicketStatus(other.TicketStatus), FinalPrice(other.FinalPrice),
    Type(other.Type) {
    totalTickets++;
}

const std::map<Ticket::TicketType, double> Ticket::DISCOUNT_COEFFICIENTS = {
    {Ticket::TicketType::ADULT, 1.0},
    {Ticket::TicketType::CHILD, 0.5},
    {Ticket::TicketType::LUGGAGE, 0.3}
};

// Статический метод по расчету финальной цены
void Ticket::CalculateFinalPrice() {
    try {
        double basePrice = TripData.GetPrice();
        double discountMultiplier = 1.0;

        switch (Type) {
        case TicketType::ADULT:
            discountMultiplier = 1.0;  // 100%
            break;
        case TicketType::CHILD:
            discountMultiplier = 0.5;  // 50%
            break;
        case TicketType::LUGGAGE:
            discountMultiplier = 0.3;  // 30%
            break;
        default:
            throw std::runtime_error("Неизвестный тип билета!");
        }

        if (basePrice < 0) {
            throw std::runtime_error("Базовая цена не может быть отрицательной!");
        }

        FinalPrice = basePrice * discountMultiplier;
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка расчета цены билета: " << e.what() << "\n";
        throw;
    }
}

std::string Ticket::GetTicketTypeName() const {
    switch (Type) {
    case TicketType::ADULT:
        return "Взрослый";
    case TicketType::CHILD:
        return "Детский";
    case TicketType::LUGGAGE:
        return "Багажный";
    default:
        return "Неизвестный";
    }
}

void Ticket::PrintTicketInfo() const {
    std::cout << "=== Информация о билете ===\n";
    std::cout << "Место: " << PlaceNumber << "\n";
    std::cout << "Тип: " << GetTicketTypeName() << "\n";
    std::cout << "Маршрут: " << TripData.GetRoute() << "\n";
    std::cout << "Цена: " << FinalPrice << " руб.\n";
    std::cout << "Пассажир: " << PassengerData.GetFullName() << "\n";
    std::cout << "Статус билета: " << TicketStatus << "\n";

    // Информация об автобусе и водителе
    std::shared_ptr<Bus> bus = TripData.GetBus();
    if (bus) {
        std::cout << "Автобус: " << bus->GetBrand()
            << " [" << bus->GetCode() << "]\n";
    }
    else {
        std::cout << "Автобус: не назначен\n";
    }

    std::shared_ptr<Driver> driver = TripData.GetDriver();
    if (driver) {
        std::cout << "Водитель: " << driver->GetFullName() << "\n";
    }
    else {
        std::cout << "Водитель: не назначен\n";
    }

    std::cout << "============================\n";
}

