#include "Ticket.hpp"

void Ticket::CalculateFinalPrice() {
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
    }

    FinalPrice = basePrice * discountMultiplier;
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

    // информация об автобусе и водителе
    if (TripData.GetBus()) {
        std::cout << "Автобус: " << TripData.GetBus()->GetBrand()  
            << " [" << TripData.GetBus()->GetCode() << "]\n";      
    }
    else {
        std::cout << "Автобус: не назначен\n";
    }

    if (TripData.GetDriver()) {
        std::cout << "Водитель: " << TripData.GetDriver()->GetFullName() << "\n";  // -> вместо .
    }
    else {
        std::cout << "Водитель: не назначен\n";
    }

    std::cout << "============================\n";
}


