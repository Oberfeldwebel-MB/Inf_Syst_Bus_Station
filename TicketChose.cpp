#include "TicketChose.hpp"
#include "Order.hpp"
#include <algorithm>

TicketChose::TicketChose(const Trip& trip) : currentTrip(trip) {
    
    // Заполняем доступные места (от 1 до количества мест в автобусе)
    int totalSeats = trip.GetBus()->GetPlaces();
    for (int i = 1; i <= totalSeats; i++) {
        availableSeats.push_back(i);
    }
}

void TicketChose::ShowAvailableSeats() const {
    std::cout << "=== Доступные места ===\n";
    std::cout << "Автобус: " << currentTrip.GetBus()->GetBrand() 
        << " [" << currentTrip.GetBus()->GetCode() << "]\n";      
    std::cout << "Всего мест: " << currentTrip.GetBus()->GetPlaces()  
        << ", свободно: " << availableSeats.size() << "\n\n";

    if (availableSeats.empty()) {
        std::cout << "Нет свободных мест!\n";
    }
    else {
        for (int seat : availableSeats) {
            std::cout << "Место " << seat << "Свободно\n";
        }
    }
    std::cout << "========================\n";
}

bool TicketChose::IsSeatAvailable(int seatNumber) const {
    return std::find(availableSeats.begin(), availableSeats.end(), seatNumber) != availableSeats.end();
}

bool TicketChose::ReserveSeat(int seatNumber) {
    auto it = std::find(availableSeats.begin(), availableSeats.end(), seatNumber);
    if (it == availableSeats.end()) {
        return false;  // Место уже занято
    }
    availableSeats.erase(it);
    return true;
}

void TicketChose::ReleaseSeat(int seatNumber) {
    if (!IsSeatAvailable(seatNumber)) {
        availableSeats.push_back(seatNumber);
        std::sort(availableSeats.begin(), availableSeats.end());
    }
}

void TicketChose::TicketToOrder(Order& order, int seatNumber, const Passenger& passenger, Ticket::TicketType ticketType) {
    // Проверяем доступность места
    auto it = std::find(availableSeats.begin(), availableSeats.end(), seatNumber);
    if (it == availableSeats.end()) {
        std::cout << "Место " << seatNumber << " уже занято или не существует!\n";
        return;
    }

    // Убираем место из доступных
    availableSeats.erase(it);

    // Создаем забронированный билет (используем ticketType вместо typeIndex)
    Ticket newTicket(seatNumber, currentTrip, passenger, ticketType);

    // Добавляем билет в Order
    order.AddTicket(newTicket);

    std::cout << "Билет забронирован!\n";
    std::cout << "Место: " << seatNumber << "\n";
    std::cout << "Тип: " << newTicket.GetTicketTypeName() << "\n";
    std::cout << "Цена: " << newTicket.GetFinalPrice() << " руб.\n";
    std::cout << "Статус: " << newTicket.GetStatus() << "\n";
}


