#include "Trip.hpp"

using namespace InfSystBusStation;
using namespace System;
using namespace System::Collections::Generic;

// Конструктор 1
Trip::Trip(System::String^ start, System::String^ finish, int price, Bus^ bus, Driver^ driver)
    : startPoint(start), finishPoint(finish), priceTicket(price),
    bus(bus), driver(driver), tripDate(DateTime::Now) {

    if (System::String::IsNullOrEmpty(start)) {
        throw gcnew System::ArgumentException("Пункт отправления не может быть пустым!");
    }
    if (System::String::IsNullOrEmpty(finish)) {
        throw gcnew System::ArgumentException("Пункт назначения не может быть пустым!");
    }
    if (price <= 0) {
        throw gcnew System::ArgumentException("Цена должна быть больше 0!");
    }
    if (bus == nullptr) {
        throw gcnew System::ArgumentNullException("Автобус не может быть null!");
    }
    if (driver == nullptr) {
        throw gcnew System::ArgumentNullException("Водитель не может быть null!");
    }

    status = "Запланирована";
    tripTime = "10:00"; // Время по умолчанию
    totalTrips++;

    // Инициализируем списки мест
    occupiedSeats = gcnew List<int>();
    availableSeats = gcnew List<int>();

    // Занимаем автобус и водителя
    bus->ChangeAvailability(false);

    // Инициализируем места
    InitializeSeats();
}

// Конструктор 2 (с датой и временем)
Trip::Trip(System::String^ start, System::String^ finish, int price, Bus^ bus, Driver^ driver,
    System::DateTime date, System::String^ time)
    : Trip(start, finish, price, bus, driver) {
    tripDate = date;
    tripTime = time;
}

// Деструктор
Trip::~Trip() {
    // Освобождаем автобус при удалении поездки
    if (bus != nullptr && (status == "Запланирована" || status == "В пути")) {
        bus->ChangeAvailability(true);
    }
}

// === МЕТОДЫ ДЛЯ РАБОТЫ С МЕСТАМИ ===

// Инициализировать места при создании поездки
void Trip::InitializeSeats() {
    if (occupiedSeats == nullptr) occupiedSeats = gcnew List<int>();
    if (availableSeats == nullptr) availableSeats = gcnew List<int>();

    occupiedSeats->Clear();
    availableSeats->Clear();

    if (bus == nullptr) {
        return;
    }

    int totalSeats = bus->GetSeatCount();

    // Все места изначально свободны
    for (int i = 1; i <= totalSeats; i++) {
        availableSeats->Add(i);
    }
}

// Забронировать место
bool Trip::BookSeat(int seatNumber) {
    if (!IsSeatAvailable(seatNumber)) {
        return false;
    }

    // Перемещаем место из свободных в занятые
    if (availableSeats->Remove(seatNumber)) {
        occupiedSeats->Add(seatNumber);
        occupiedSeats->Sort();
        System::Console::WriteLine("[Trip] Место {0} забронировано на поездку {1}",
            seatNumber, GetRoute());
        return true;
    }

    return false;
}

// Отменить бронирование места
bool Trip::CancelSeatBooking(int seatNumber) {
    if (!IsSeatOccupied(seatNumber)) {
        return false;
    }

    // Перемещаем место из занятых в свободные
    if (occupiedSeats->Remove(seatNumber)) {
        availableSeats->Add(seatNumber);
        availableSeats->Sort();
        System::Console::WriteLine("[Trip] Бронирование места {0} отменено для поездки {1}",
            seatNumber, GetRoute());
        return true;
    }

    return false;
}

// Проверить свободно ли место
bool Trip::IsSeatAvailable(int seatNumber) {
    if (availableSeats == nullptr) return false;
    return availableSeats->Contains(seatNumber);
}

// Проверить занято ли место
bool Trip::IsSeatOccupied(int seatNumber) {
    if (occupiedSeats == nullptr) return false;
    return occupiedSeats->Contains(seatNumber);
}

// Получить список свободных мест
System::Collections::Generic::List<int>^ Trip::GetAvailableSeats() {
    // Возвращаем копию списка
    List<int>^ result = gcnew List<int>();
    if (availableSeats != nullptr) {
        for each (int seat in availableSeats) {
            result->Add(seat);
        }
    }
    return result;
}

// Получить список занятых мест
System::Collections::Generic::List<int>^ Trip::GetOccupiedSeats() {
    // Возвращаем копию списка
    List<int>^ result = gcnew List<int>();
    if (occupiedSeats != nullptr) {
        for each (int seat in occupiedSeats) {
            result->Add(seat);
        }
    }
    return result;
}

// Всего мест в автобусе
int Trip::GetTotalSeatsCount() {
    if (bus == nullptr) {
        return 0;
    }
    return bus->GetSeatCount();
}

// Количество свободных мест
int Trip::GetAvailableSeatsCount() {
    if (availableSeats == nullptr) return 0;
    return availableSeats->Count;
}

// Количество занятых мест
int Trip::GetOccupiedSeatsCount() {
    if (occupiedSeats == nullptr) return 0;
    return occupiedSeats->Count;
}

// Получить информацию о местах
System::String^ Trip::GetSeatsInfo() {
    return System::String::Format("Места: {0}/{1} свободно",
        GetAvailableSeatsCount(), GetTotalSeatsCount());
}

// === ПРОВЕРКИ ===

bool Trip::IsAvailableForChanges() {
    return IsPlanned(); // Изменять можно только запланированные поездки
}

bool Trip::IsCompleted() {
    return status == "Завершена";
}

bool Trip::IsInProgress() {
    return status == "В пути";
}

bool Trip::IsPlanned() {
    return status == "Запланирована";
}

bool Trip::IsCancelled() {
    return status == "Отменена";
}

// === МЕТОДЫ УПРАВЛЕНИЯ СТАТУСОМ ===

void Trip::StartTrip() {
    if (!IsPlanned()) {
        throw gcnew System::InvalidOperationException(
            "Можно начать только запланированную поездку!");
    }

    if (bus == nullptr) {
        throw gcnew System::InvalidOperationException("Не назначен автобус!");
    }
    if (driver == nullptr) {
        throw gcnew System::InvalidOperationException("Не назначен водитель!");
    }

    status = "В пути";
    System::Console::WriteLine("Поездка началась: {0} → {1}", startPoint, finishPoint);
}

void Trip::CompleteTrip() {
    if (!IsInProgress()) {
        throw gcnew System::InvalidOperationException(
            "Можно завершить только поездку в пути!");
    }

    status = "Завершена";

    // Освобождаем автобус
    if (bus != nullptr) {
        bus->ChangeAvailability(true);
    }

    System::Console::WriteLine("Поездка завершена: {0} → {1}", startPoint, finishPoint);
}

void Trip::CancelTrip() {
    if (IsCompleted()) {
        throw gcnew System::InvalidOperationException(
            "Нельзя отменить завершенную поездку!");
    }

    status = "Отменена";

    // Освобождаем автобус
    if (bus != nullptr) {
        bus->ChangeAvailability(true);
    }

    System::Console::WriteLine("Поездка отменена: {0} → {1}", startPoint, finishPoint);
}

// === МЕТОДЫ ИЗМЕНЕНИЯ ===

void Trip::ChangeDriver(Driver^ newDriver) {
    if (newDriver == nullptr) {
        throw gcnew System::ArgumentNullException("Новый водитель не может быть null!");
    }

    if (!newDriver->GetAvailability()) {
        throw gcnew System::InvalidOperationException("Водитель недоступен!");
    }

    driver = newDriver;
    System::Console::WriteLine("Водитель изменен на: {0}", driver->GetFullName());
}

void Trip::ChangeBus(Bus^ newBus) {
    if (newBus == nullptr) {
        throw gcnew System::ArgumentNullException("Новый автобус не может быть null!");
    }

    if (!newBus->GetAvailability()) {
        throw gcnew System::InvalidOperationException("Автобус недоступен!");
    }

    // Освобождаем старый автобус
    if (bus != nullptr) {
        bus->ChangeAvailability(true);
    }

    // Занимаем новый автобус
    bus = newBus;
    bus->ChangeAvailability(false);

    System::Console::WriteLine("Автобус изменен на: {0} [{1}]",
        bus->GetBrand(), bus->GetFormattedCode());

    // Переинициализируем места для нового автобуса
    InitializeSeats();
}

void Trip::ChangeRoute(System::String^ newStart, System::String^ newFinish) {
    if (IsInProgress() || IsCompleted()) {
        throw gcnew System::InvalidOperationException(
            "Нельзя изменить маршрут поездки в процессе или завершенной!");
    }

    startPoint = newStart;
    finishPoint = newFinish;
    System::Console::WriteLine("Маршрут изменен на: {0} → {1}", newStart, newFinish);
}

void Trip::ChangePrice(int newPrice) {
    if (newPrice <= 0) {
        throw gcnew System::ArgumentException("Цена должна быть больше 0!");
    }

    priceTicket = newPrice;
    System::Console::WriteLine("Цена изменена на: {0} руб.", newPrice);
}

// === ИНФОРМАЦИОННЫЕ МЕТОДЫ ===

void Trip::PrintInfo() {
    System::Console::WriteLine("=== Информация о поездке ===");
    System::Console::WriteLine("Маршрут: {0} → {1}", startPoint, finishPoint);
    System::Console::WriteLine("Дата: {0:dd.MM.yyyy}", tripDate);
    System::Console::WriteLine("Время: {0}", tripTime);
    System::Console::WriteLine("Статус: {0}", status);
    System::Console::WriteLine("Цена билета: {0} руб.", priceTicket);
    System::Console::WriteLine("Места: {0}/{1} свободно",
        GetAvailableSeatsCount(), GetTotalSeatsCount());

    if (bus != nullptr) {
        System::Console::WriteLine("Автобус: {0} [{1}]",
            bus->GetBrand(), bus->GetFormattedCode());
    }

    if (driver != nullptr) {
        System::Console::WriteLine("Водитель: {0}", driver->GetFullName());
    }
    System::Console::WriteLine("=============================");
}

System::String^ Trip::GetFullInfo() {
    return System::String::Format(
        "Поездка: {0} → {1} ({2:dd.MM.yyyy} {3})\nСтатус: {4}\nЦена: {5} руб.\n{6}\nАвтобус: {7}\nВодитель: {8}",
        startPoint, finishPoint, tripDate, tripTime, status, priceTicket,
        GetSeatsInfo(),
        bus != nullptr ? bus->GetFullName() : "Не назначен",
        driver != nullptr ? driver->GetFullName() : "Не назначен"
    );
}

System::String^ Trip::GetShortInfo() {
    return System::String::Format("{0} → {1} ({2:dd.MM} {3}) - {4} руб.",
        startPoint, finishPoint, tripDate, tripTime, priceTicket);
}

// === СТАТИЧЕСКИЕ МЕТОДЫ ===

System::String^ Trip::GetStatusDescription(System::String^ status) {
    if (status == "Запланирована") return "Поездка запланирована";
    if (status == "В пути") return "Поездка в процессе";
    if (status == "Завершена") return "Поездка завершена";
    if (status == "Отменена") return "Поездка отменена";
    return "Неизвестный статус";
}