#include "Ticket.hpp"
#include "Trip.hpp"
#include "User.hpp"

using namespace InfSystBusStation;

// Конструктор
Ticket::Ticket(int placeNumber, Trip^ trip, User^ passenger, TicketType type)
    : placeNumber(placeNumber),
    tripData(trip),
    passengerData(passenger),
    type(type),
    ticketAvail(true),
    ticketStatus("Забронирован"),
    finalPrice(0.0)
{
    if (placeNumber <= 0) {
        throw gcnew System::ArgumentException("Номер места должен быть положительным!");
    }

    if (passenger == nullptr) {
        throw gcnew System::ArgumentNullException("Пассажир не может быть null!");
    }

    if (trip == nullptr) {
        throw gcnew System::ArgumentNullException("Поездка не может быть null!");
    }

    CalculateFinalPrice();
    System::Console::WriteLine("[Ticket] Создан билет на место №{0} для {1}",
        placeNumber, passenger->GetFullName());
}

// Расчет конечной цены
void Ticket::CalculateFinalPrice() {
    if (tripData == nullptr) {
        finalPrice = 0.0;
        return;
    }

    double basePrice = tripData->GetPrice();
    finalPrice = CalculatePrice(basePrice, type);

    // Если есть пользователь, применить его скидку
    if (passengerData != nullptr) {
        double discount = passengerData->CalculateDiscount();
        if (discount > 0) {
            double originalPrice = finalPrice;
            finalPrice = finalPrice * (1.0 - discount / 100.0);
            System::Console::WriteLine("[Ticket] Применена скидка {0}%: {1:F2} руб. → {2:F2} руб.",
                discount, originalPrice, finalPrice);
        }
    }
}

// Вывод информации о билете
void Ticket::PrintTicketInfo() {
    System::Console::WriteLine("=== ИНФОРМАЦИЯ О БИЛЕТЕ ===");
    System::Console::WriteLine("Номер места: {0}", placeNumber);
    System::Console::WriteLine("Тип билета: {0}", TicketTypeName);

    if (tripData != nullptr) {
        System::Console::WriteLine("Маршрут: {0}", tripData->GetRoute());

        // Используем существующие методы Trip для получения даты и времени
        System::Console::WriteLine("Дата: {0:dd.MM.yyyy}", tripData->GetTripDate());
        System::Console::WriteLine("Время: {0}", tripData->GetTripTime());

        System::Console::WriteLine("Цена поездки: {0:F2} руб.", tripData->GetPrice());
    }

    if (passengerData != nullptr) {
        System::Console::WriteLine("Пассажир: {0}", passengerData->GetFullName());
        System::Console::WriteLine("Email: {0}", passengerData->GetEmail());
        System::Console::WriteLine("Телефон: {0}", passengerData->PhoneNumber);

        // Если есть паспортные данные
        System::String^ passportSeries = passengerData->GetPassportSeries();
        System::String^ passportNumber = passengerData->GetPassportNumber();
        if (!System::String::IsNullOrEmpty(passportSeries) &&
            !System::String::IsNullOrEmpty(passportNumber)) {
            System::Console::WriteLine("Паспорт: {0} {1}", passportSeries, passportNumber);
        }
    }

    System::Console::WriteLine("Базовая цена: {0:F2} руб.",
        tripData != nullptr ? tripData->GetPrice() : 0.0);
    System::Console::WriteLine("Конечная цена: {0:F2} руб.", finalPrice);
    System::Console::WriteLine("Статус: {0}", ticketStatus);
    System::Console::WriteLine("==========================");
}