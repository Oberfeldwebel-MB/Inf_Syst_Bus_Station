#include "Ticket.h"

void Ticket::CalculateFinalPrice() {
    // Цена для разных типов билетов
    std::map<int, double> discounts = {
        {0, 1.0},  // Взрослый - 100%
        {1, 0.5},  // Детский - 50%
        {2, 0.3}   // Багажный - 30%
    };

    double base_price = Trip_data.GetPrice();
    double discount_multiplier = discounts[Ticket_type_index];
    Final_price = base_price * discount_multiplier;
}

void Ticket::Print_ticket_info() const {
    std::cout << "=== Информация о билете ===\n";
    std::cout << "Место: " << Place_number << "\n";
    std::cout << "Тип: " << GetTicketTypeName() << "\n";
    std::cout << "Маршрут: " << Trip_data.GetRoute() << "\n";
    std::cout << "Цена: " << Final_price << " руб.\n";  
    std::cout << "Пассажир: " << Passenger_data.GetFullName() << "\n";
    std::cout << "Статус билета: " << Ticket_status << "\n";

    // информация об автобусе и водителе
    if (Trip_data.GetBus()) {
        std::cout << "Автобус: " << Trip_data.GetBus()->GetBrand()  
            << " [" << Trip_data.GetBus()->GetCode() << "]\n";      
    }
    else {
        std::cout << "Автобус: не назначен\n";
    }

    if (Trip_data.GetDriver()) {
        std::cout << "Водитель: " << Trip_data.GetDriver()->GetFullName() << "\n";  // -> вместо .
    }
    else {
        std::cout << "Водитель: не назначен\n";
    }

    std::cout << "============================\n";
}


