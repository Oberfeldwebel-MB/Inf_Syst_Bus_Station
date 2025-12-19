#include "TicketChose.hpp"
#include "Trip.hpp"
#include "Order.hpp"

using namespace InfSystBusStation;
using namespace System;
using namespace System::Collections::Generic;

// Конструктор
TicketChose::TicketChose(Trip^ trip, Order^ order)
    : selectedTrip(trip), currentOrder(order) {

    if (trip == nullptr) {
        throw gcnew ArgumentNullException("Поездка не может быть null!");
    }

    if (order == nullptr) {
        throw gcnew ArgumentNullException("Заказ не может быть null!");
    }

    availableSeats = gcnew List<int>();
    selectedSeats = gcnew List<int>();

    // Получаем количество мест из автобуса
    if (trip->GetBus() != nullptr) {
        totalSeats = trip->GetBus()->GetSeatCount(); // Нужно добавить метод GetSeatCount() в Bus
    }
    else {
        totalSeats = 40; // Значение по умолчанию
    }

    LoadAvailableSeats();
}

// Загрузить свободные места
void TicketChose::LoadAvailableSeats() {
    availableSeats->Clear();

    // 1. Все места от 1 до totalSeats
    for (int i = 1; i <= totalSeats; i++) {
        availableSeats->Add(i);
    }

    // 2. Удалить уже занятые места (нужно получить из Order или базы данных)
    // Это заглушка - нужно будет реализовать проверку занятых мест
    // Например: if (IsSeatOccupied(i)) availableSeats->Remove(i);

    // 3. Сортировка
    availableSeats->Sort();
}

// Проверить свободно ли место
bool TicketChose::IsSeatAvailable(int seatNumber) {
    return availableSeats->Contains(seatNumber);
}

// Выбрать место
bool TicketChose::SelectSeat(int seatNumber) {
    if (!IsSeatAvailable(seatNumber)) {
        return false;
    }

    if (selectedSeats->Contains(seatNumber)) {
        return false; // Уже выбрано
    }

    availableSeats->Remove(seatNumber);
    selectedSeats->Add(seatNumber);
    selectedSeats->Sort();

    return true;
}

// Отменить выбор места
bool TicketChose::DeselectSeat(int seatNumber) {
    if (!selectedSeats->Contains(seatNumber)) {
        return false;
    }

    selectedSeats->Remove(seatNumber);
    availableSeats->Add(seatNumber);
    availableSeats->Sort();

    return true;
}

// Очистить выбор
void TicketChose::ClearSelection() {
    // Возвращаем все выбранные места в доступные
    for each (int seat in selectedSeats) {
        availableSeats->Add(seat);
    }
    availableSeats->Sort();
    selectedSeats->Clear();
}

// Добавить выбранные билеты в заказ
bool TicketChose::AddSelectedTicketsToOrder() {
    if (!HasSelectedSeats()) {
        return false;
    }

    // Для каждого выбранного места создаем билет
    for each (int seat in selectedSeats) {
        // Создаем билет (нужен класс Ticket)
        // Ticket^ ticket = gcnew Ticket(selectedTrip, seat, selectedTrip->GetPrice());
        // currentOrder->AddTicket(ticket);
    }

    // Очищаем выбор после добавления
    selectedSeats->Clear();

    return true;
}

// Получить информацию о поездке
String^ TicketChose::GetTripInfo() {
    if (selectedTrip == nullptr) {
        return "Поездка не выбрана";
    }

    return String::Format(
        "МАРШРУТ: {0}\n"
        "ДАТА: {1:dd.MM.yyyy}\n"
        "ВРЕМЯ: {2}\n"
        "АВТОБУС: {3}\n"
        "ВОДИТЕЛЬ: {4}\n"
        "ЦЕНА БИЛЕТА: {5} руб.",
        selectedTrip->GetRoute(),
        selectedTrip->GetTripDate(),
        selectedTrip->GetTripTime(),
        selectedTrip->GetBus() != nullptr ?
        selectedTrip->GetBus()->GetBrand() + " " + selectedTrip->GetBus()->GetModel() : "Не указан",
        selectedTrip->GetDriver() != nullptr ?
        selectedTrip->GetDriver()->GetFullName() : "Не назначен",
        selectedTrip->GetPrice()
    );
}

// Вспомогательные методы
bool TicketChose::HasAvailableSeats() {
    return availableSeats->Count > 0;
}

bool TicketChose::HasSelectedSeats() {
    return selectedSeats->Count > 0;
}

bool TicketChose::CanAddToOrder() {
    return HasSelectedSeats() && currentOrder != nullptr;
}

int TicketChose::GetSelectedSeatsCount() {
    return selectedSeats->Count;
}

Decimal TicketChose::GetTotalPrice() {
    if (selectedTrip == nullptr) return 0;
    return selectedTrip->GetPrice() * selectedSeats->Count;
}