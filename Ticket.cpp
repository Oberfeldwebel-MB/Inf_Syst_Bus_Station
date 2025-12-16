#include "Ticket.hpp"

using namespace InfSystBusStation;

// Конструктор
Ticket::Ticket(int placeNumber, Trip^ trip, Passenger^ passenger, TicketType type)
    : placeNumber(placeNumber), tripData(trip), passengerData(passenger),
    type(type), ticketAvail(true), ticketStatus("Забронирован"), finalPrice(0.0) {

    if (placeNumber <= 0) {
        throw gcnew System::ArgumentException("Номер места должен быть положительным!");
    }

    CalculateFinalPrice();
}

// Расчет конечной цены
void Ticket::CalculateFinalPrice() {
    if (tripData == nullptr) {
        finalPrice = 0.0;
        return;
    }

    double basePrice = tripData->GetPrice();
    finalPrice = CalculatePrice(basePrice, type);
}

// Вывод информации о билете
void Ticket::PrintTicketInfo() {
    System::Console::WriteLine("=== Информация о билете ===");
    System::Console::WriteLine("Номер места: {0}", placeNumber);
    System::Console::WriteLine("Тип билета: {0}", TicketTypeName);

    if (tripData != nullptr) {
        System::Console::WriteLine("Маршрут: {0}", tripData->GetRoute());
        System::Console::WriteLine("Цена поездки: {0} руб.", tripData->GetPrice());
    }

    if (passengerData != nullptr) {
        System::Console::WriteLine("Пассажир: {0}", passengerData->GetFullName());
    }

    System::Console::WriteLine("Конечная цена: {0:F2} руб.", finalPrice);
    System::Console::WriteLine("Статус: {0}", ticketStatus);
    System::Console::WriteLine("==========================");
}