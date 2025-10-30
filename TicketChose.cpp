#include "TicketChose.h"
#include "Order.h"
#include <algorithm>

TicketChose::TicketChose(const Trip& trip) : current_trip(trip) {
    
    // Заполняем доступные места (от 1 до количества мест в автобусе)
    int total_seats = trip.GetBus()->GetPlaces();
    for (int i = 1; i <= total_seats; i++) {
        available_seats.push_back(i);
    }
}

void TicketChose::ShowAvailableSeats() const {
    std::cout << "=== Доступные места ===\n";
    std::cout << "Автобус: " << current_trip.GetBus()->GetBrand() 
        << " [" << current_trip.GetBus()->GetCode() << "]\n";      
    std::cout << "Всего мест: " << current_trip.GetBus()->GetPlaces()  
        << ", свободно: " << available_seats.size() << "\n\n";

    if (available_seats.empty()) {
        std::cout << "Нет свободных мест!\n";
    }
    else {
        for (int seat : available_seats) {
            std::cout << "Место " << seat << "Свободно\n";
        }
    }
    std::cout << "========================\n";
}

bool TicketChose::IsSeatAvailable(int seat_number) const {
    return std::find(available_seats.begin(), available_seats.end(), seat_number) != available_seats.end();
}

bool TicketChose::ReserveSeat(int seat_number) {
    auto it = std::find(available_seats.begin(), available_seats.end(), seat_number);
    if (it == available_seats.end()) {
        return false;  // Место уже занято
    }
    available_seats.erase(it);
    return true;
}

void TicketChose::ReleaseSeat(int seat_number) {
    if (!IsSeatAvailable(seat_number)) {
        available_seats.push_back(seat_number);
        std::sort(available_seats.begin(), available_seats.end());
    }
}

void TicketChose::Ticket_to_order(Order& order, int seat_number, const Passenger& passenger, int type_index) {
    // Проверяем доступность места
    auto it = std::find(available_seats.begin(), available_seats.end(), seat_number);
    if (it == available_seats.end()) {
        std::cout << "Место " << seat_number << " уже занято или не существует!\n";
        return;
    }

    // Убираем место из доступных
    available_seats.erase(it);

    // Создаем забронированный билет
    Ticket new_ticket(seat_number, current_trip, passenger, type_index);

    // Добавляем билет в Order
    order.AddTicket(new_ticket);

    std::cout << "Билет забронирован!\n";
    std::cout << "Место: " << seat_number << "\n";
    std::cout << "Тип: " << new_ticket.GetTicketTypeName() << "\n";
    std::cout << "Цена: " << new_ticket.GetFinalPrice() << " руб.\n";
    std::cout << "Статус: " << new_ticket.GetStatus() << "\n";

    return;
}


