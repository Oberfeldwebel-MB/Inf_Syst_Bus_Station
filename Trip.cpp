// Trip.cpp
#include "Trip.hpp"

using namespace InfSystBusStation;
using namespace System;
using namespace System::Collections::Generic;

// Конструктор 1: Без даты и времени (использует текущие)
Trip::Trip(String^ start, String^ finish, int price, Bus^ bus, Driver^ driver)
    : startPoint(start),
    finishPoint(finish),
    priceTicket(price),
    bus(bus),
    driver(driver),
    tripDate(DateTime::Now),
    tripTime("12:00"), // значение по умолчанию
    status("Запланирована")
{
    // Проверки
    if (String::IsNullOrEmpty(start)) {
        throw gcnew ArgumentException("Начальный пункт не может быть пустым!");
    }

    if (String::IsNullOrEmpty(finish)) {
        throw gcnew ArgumentException("Конечный пункт не может быть пустым!");
    }

    if (price <= 0) {
        throw gcnew ArgumentException("Цена должна быть положительной!");
    }

    if (bus == nullptr) {
        throw gcnew ArgumentNullException("Автобус не может быть null!");
    }

    if (driver == nullptr) {
        throw gcnew ArgumentNullException("Водитель не может быть null!");
    }

    // Инициализация списков мест
    occupiedSeats = gcnew List<int>();
    availableSeats = gcnew List<int>();

    // Инициализация мест
    InitializeSeats();

    totalTrips++;

    Console::WriteLine("[Trip] Создана поездка: {0} → {1}", start, finish);
}

// Конструктор 2: С датой и временем
Trip::Trip(String^ start, String^ finish, int price, Bus^ bus, Driver^ driver,
    DateTime date, String^ time)
    : startPoint(start),
    finishPoint(finish),
    priceTicket(price),
    bus(bus),
    driver(driver),
    tripDate(date),
    tripTime(time),
    status("Запланирована")
{
    // Проверки (такие же как в первом конструкторе)
    if (String::IsNullOrEmpty(start)) {
        throw gcnew ArgumentException("Начальный пункт не может быть пустым!");
    }

    if (String::IsNullOrEmpty(finish)) {
        throw gcnew ArgumentException("Конечный пункт не может быть пустым!");
    }

    if (price <= 0) {
        throw gcnew ArgumentException("Цена должна быть положительной!");
    }

    if (bus == nullptr) {
        throw gcnew ArgumentNullException("Автобус не может быть null!");
    }

    if (driver == nullptr) {
        throw gcnew ArgumentNullException("Водитель не может быть null!");
    }

    if (String::IsNullOrEmpty(time)) {
        throw gcnew ArgumentException("Время не может быть пустым!");
    }

    // Инициализация списков мест
    occupiedSeats = gcnew List<int>();
    availableSeats = gcnew List<int>();

    // Инициализация мест
    InitializeSeats();

    totalTrips++;

    Console::WriteLine("[Trip] Создана поездка: {0} → {1} на {2}",
        start, finish, date.ToString("dd.MM.yyyy"));
}

// Деструктор
Trip::~Trip() {
    // Очистка ресурсов
    occupiedSeats = nullptr;
    availableSeats = nullptr;
    bus = nullptr;
    driver = nullptr;
}

// Инициализация мест
void Trip::InitializeSeats() {
    if (bus == nullptr) return;

    int totalSeats = bus->GetSeatCount();

    // Очищаем списки
    occupiedSeats->Clear();
    availableSeats->Clear();

    // Заполняем список доступных мест
    for (int i = 1; i <= totalSeats; i++) {
        availableSeats->Add(i);
    }
}

// Другие методы, которые нужно реализовать минимум:

// Забронировать место
bool Trip::BookSeat(int seatNumber) {
    if (!IsSeatAvailable(seatNumber)) {
        return false;
    }

    availableSeats->Remove(seatNumber);
    occupiedSeats->Add(seatNumber);
    return true;
}

// Отменить бронирование
bool Trip::CancelSeatBooking(int seatNumber) {
    if (!IsSeatOccupied(seatNumber)) {
        return false;
    }

    occupiedSeats->Remove(seatNumber);
    availableSeats->Add(seatNumber);
    return true;
}

// Проверить свободно ли место
bool Trip::IsSeatAvailable(int seatNumber) {
    return availableSeats->Contains(seatNumber);
}

// Проверить занято ли место
bool Trip::IsSeatOccupied(int seatNumber) {
    return occupiedSeats->Contains(seatNumber);
}

// Получить свободные места
List<int>^ Trip::GetAvailableSeats() {
    return availableSeats;
}

// Получить занятые места
List<int>^ Trip::GetOccupiedSeats() {
    return occupiedSeats;
}

// Всего мест в автобусе
int Trip::GetTotalSeatsCount() {
    return (bus != nullptr) ? bus->GetSeatCount() : 0;
}

// Количество свободных мест
int Trip::GetAvailableSeatsCount() {
    return availableSeats->Count;
}

// Количество занятых мест
int Trip::GetOccupiedSeatsCount() {
    return occupiedSeats->Count;
}

// Начать поездку
void Trip::StartTrip() {
    if (status != "Запланирована") {
        throw gcnew InvalidOperationException("Поездка не в состоянии 'Запланирована'!");
    }

    status = "В пути";
    Console::WriteLine("[Trip] Поездка начата: {0}", GetRoute());
}

// Завершить поездку
void Trip::CompleteTrip() {
    if (status != "В пути") {
        throw gcnew InvalidOperationException("Поездка не в состоянии 'В пути'!");
    }

    status = "Завершена";
    Console::WriteLine("[Trip] Поездка завершена: {0}", GetRoute());
}

// Отменить поездку
void Trip::CancelTrip() {
    if (status == "Завершена" || status == "Отменена") {
        throw gcnew InvalidOperationException("Нельзя отменить завершенную или отмененную поездку!");
    }

    status = "Отменена";

    // Освобождаем все забронированные места
    for each (int seat in occupiedSeats) {
        availableSeats->Add(seat);
    }
    occupiedSeats->Clear();

    Console::WriteLine("[Trip] Поездка отменена: {0}", GetRoute());



}


// Trip.cpp - добавьте эти методы:

// Изменить водителя
void Trip::ChangeDriver(Driver^ newDriver) {
    if (newDriver == nullptr) {
        throw gcnew ArgumentNullException("Новый водитель не может быть null!");
    }

    if (!IsAvailableForChanges()) {
        throw gcnew InvalidOperationException("Нельзя изменить водителя в текущем статусе поездки!");
    }

    driver = newDriver;
    Console::WriteLine("[Trip] Водитель изменен на: {0}", newDriver->GetFullName());
}

// Изменить автобус
void Trip::ChangeBus(Bus^ newBus) {
    if (newBus == nullptr) {
        throw gcnew ArgumentNullException("Новый автобус не может быть null!");
    }

    if (!IsAvailableForChanges()) {
        throw gcnew InvalidOperationException("Нельзя изменить автобус в текущем статусе поездки!");
    }

    bus = newBus;

    // Переинициализируем места при смене автобуса
    InitializeSeats();

    Console::WriteLine("[Trip] Автобус изменен на: {0}", newBus->GetFullName());
}

// Изменить маршрут
void Trip::ChangeRoute(String^ newStart, String^ newFinish) {
    if (String::IsNullOrEmpty(newStart) || String::IsNullOrEmpty(newFinish)) {
        throw gcnew ArgumentException("Начальный и конечный пункты не могут быть пустыми!");
    }

    if (!IsAvailableForChanges()) {
        throw gcnew InvalidOperationException("Нельзя изменить маршрут в текущем статусе поездки!");
    }

    startPoint = newStart;
    finishPoint = newFinish;

    Console::WriteLine("[Trip] Маршрут изменен на: {0} → {1}", newStart, newFinish);
}

// Изменить цену
void Trip::ChangePrice(int newPrice) {
    if (newPrice <= 0) {
        throw gcnew ArgumentException("Цена должна быть положительной!");
    }

    if (!IsAvailableForChanges()) {
        throw gcnew InvalidOperationException("Нельзя изменить цену в текущем статусе поездки!");
    }

    priceTicket = newPrice;
    Console::WriteLine("[Trip] Цена изменена на: {0} руб.", newPrice);
}

// Проверки статусов
bool Trip::IsAvailableForChanges() {
    return IsPlanned(); // Только запланированные поездки можно изменять
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

// Информационные методы
void Trip::PrintInfo() {
    Console::WriteLine("=== Информация о поездке ===");
    Console::WriteLine("Маршрут: {0}", GetRoute());
    Console::WriteLine("Статус: {0}", status);
    Console::WriteLine("Цена: {0} руб.", priceTicket);

    if (bus != nullptr) {
        Console::WriteLine("Автобус: {0}", bus->GetFullName());
    }

    if (driver != nullptr) {
        Console::WriteLine("Водитель: {0}", driver->GetFullName());
    }

    Console::WriteLine("Дата: {0}", tripDate.ToString("dd.MM.yyyy"));
    Console::WriteLine("Время: {0}", tripTime);
    Console::WriteLine("Места: свободно {0}/{1}", GetAvailableSeatsCount(), GetTotalSeatsCount());
    Console::WriteLine("==========================");
}

String^ Trip::GetFullInfo() {
    return String::Format(
        "Маршрут: {0}\n"
        "Статус: {1}\n"
        "Цена: {2} руб.\n"
        "Автобус: {3}\n"
        "Водитель: {4}\n"
        "Дата: {5}\n"
        "Время: {6}\n"
        "Места: {7}/{8} свободно",
        GetRoute(),
        status,
        priceTicket,
        bus != nullptr ? bus->GetFullName() : "Не назначен",
        driver != nullptr ? driver->GetFullName() : "Не назначен",
        tripDate.ToString("dd.MM.yyyy"),
        tripTime,
        GetAvailableSeatsCount(),
        GetTotalSeatsCount()
    );
}

String^ Trip::GetShortInfo() {
    return String::Format("{0} - {1} руб. ({2} мест свободно)",
        GetRoute(), priceTicket, GetAvailableSeatsCount());
}

String^ Trip::GetSeatsInfo() {
    return String::Format("Всего мест: {0}\nСвободно: {1}\nЗанято: {2}",
        GetTotalSeatsCount(), GetAvailableSeatsCount(), GetOccupiedSeatsCount());
}

// Статический метод
String^ Trip::GetStatusDescription(String^ status) {
    if (status == "Запланирована") return "Поездка запланирована";
    if (status == "В пути") return "Поездка выполняется";
    if (status == "Завершена") return "Поездка завершена";
    if (status == "Отменена") return "Поездка отменена";
    return "Неизвестный статус";
}