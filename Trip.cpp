// Trip.cpp
#include "Trip.hpp"

using namespace InfSystBusStation;
using namespace System;

// Конструктор 1
Trip::Trip(String^ start, String^ finish, int price, Bus^ bus, Driver^ driver)
    : startPoint(start), finishPoint(finish), priceTicket(price),
    bus(bus), driver(driver), tripDate(DateTime::Now) {

    if (String::IsNullOrEmpty(start)) {
        throw gcnew ArgumentException("Пункт отправления не может быть пустым!");
    }
    if (String::IsNullOrEmpty(finish)) {
        throw gcnew ArgumentException("Пункт назначения не может быть пустым!");
    }
    if (price <= 0) {
        throw gcnew ArgumentException("Цена должна быть больше 0!");
    }
    if (bus == nullptr) {
        throw gcnew ArgumentNullException("Автобус не может быть null!");
    }
    if (driver == nullptr) {
        throw gcnew ArgumentNullException("Водитель не может быть null!");
    }

    status = "Запланирована";
    tripTime = "10:00"; // Время по умолчанию
    totalTrips++;

    // Занимаем автобус и водителя
    bus->ChangeAvailability(false);
}

// Конструктор 2 (с датой и временем)
Trip::Trip(String^ start, String^ finish, int price, Bus^ bus, Driver^ driver,
    DateTime date, String^ time)
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

// === МЕТОДЫ УПРАВЛЕНИЯ СТАТУСОМ ===

void Trip::StartTrip() {
    if (!IsPlanned()) {
        throw gcnew InvalidOperationException(
            "Можно начать только запланированную поездку!");
    }

    if (bus == nullptr) {
        throw gcnew InvalidOperationException("Не назначен автобус!");
    }
    if (driver == nullptr) {
        throw gcnew InvalidOperationException("Не назначен водитель!");
    }

    status = "В пути";
    Console::WriteLine("Поездка началась: {0} → {1}", startPoint, finishPoint);
}

void Trip::CompleteTrip() {
    if (!IsInProgress()) {
        throw gcnew InvalidOperationException(
            "Можно завершить только поездку в пути!");
    }

    status = "Завершена";

    // Освобождаем автобус
    if (bus != nullptr) {
        bus->ChangeAvailability(true);
    }

    Console::WriteLine("Поездка завершена: {0} → {1}", startPoint, finishPoint);
}

void Trip::CancelTrip() {
    if (IsCompleted()) {
        throw gcnew InvalidOperationException(
            "Нельзя отменить завершенную поездку!");
    }

    status = "Отменена";

    // Освобождаем автобус
    if (bus != nullptr) {
        bus->ChangeAvailability(true);
    }

    Console::WriteLine("Поездка отменена: {0} → {1}", startPoint, finishPoint);
}

// === МЕТОДЫ ИЗМЕНЕНИЯ ===

void Trip::ChangeDriver(Driver^ newDriver) {
    if (newDriver == nullptr) {
        throw gcnew ArgumentNullException("Новый водитель не может быть null!");
    }

    if (!newDriver->GetAvailability()) {
        throw gcnew InvalidOperationException("Водитель недоступен!");
    }

    driver = newDriver;
    Console::WriteLine("Водитель изменен на: {0}", driver->GetFullName());
}

void Trip::ChangeBus(Bus^ newBus) {
    if (newBus == nullptr) {
        throw gcnew ArgumentNullException("Новый автобус не может быть null!");
    }

    if (!newBus->GetAvailability()) {
        throw gcnew InvalidOperationException("Автобус недоступен!");
    }

    // Освобождаем старый автобус
    if (bus != nullptr) {
        bus->ChangeAvailability(true);
    }

    // Занимаем новый автобус
    bus = newBus;
    bus->ChangeAvailability(false);

    Console::WriteLine("Автобус изменен на: {0} [{1}]",
        bus->GetBrand(), bus->GetFormattedCode());
}

void Trip::ChangeRoute(String^ newStart, String^ newFinish) {
    if (IsInProgress() || IsCompleted()) {
        throw gcnew InvalidOperationException(
            "Нельзя изменить маршрут поездки в процессе или завершенной!");
    }

    startPoint = newStart;
    finishPoint = newFinish;
    Console::WriteLine("Маршрут изменен на: {0} → {1}", newStart, newFinish);
}

void Trip::ChangePrice(int newPrice) {
    if (newPrice <= 0) {
        throw gcnew ArgumentException("Цена должна быть больше 0!");
    }

    priceTicket = newPrice;
    Console::WriteLine("Цена изменена на: {0} руб.", newPrice);
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

// === ИНФОРМАЦИОННЫЕ МЕТОДЫ ===

void Trip::PrintInfo() {
    Console::WriteLine("=== Информация о поездке ===");
    Console::WriteLine("Маршрут: {0} → {1}", startPoint, finishPoint);
    Console::WriteLine("Дата: {0:dd.MM.yyyy}", tripDate);
    Console::WriteLine("Время: {0}", tripTime);
    Console::WriteLine("Статус: {0}", status);
    Console::WriteLine("Цена билета: {0} руб.", priceTicket);

    if (bus != nullptr) {
        Console::WriteLine("Автобус: {0} [{1}]",
            bus->GetBrand(), bus->GetFormattedCode());
    }

    if (driver != nullptr) {
        Console::WriteLine("Водитель: {0}", driver->GetFullName());
    }
    Console::WriteLine("=============================");
}

String^ Trip::GetFullInfo() {
    return String::Format(
        "Поездка: {0} → {1} ({2:dd.MM.yyyy} {3})\nСтатус: {4}\nЦена: {5} руб.\nАвтобус: {6}\nВодитель: {7}",
        startPoint, finishPoint, tripDate, tripTime, status, priceTicket,
        bus != nullptr ? bus->GetFullName() : "Не назначен",
        driver != nullptr ? driver->GetFullName() : "Не назначен"
    );
}

String^ Trip::GetShortInfo() {
    return String::Format("{0} → {1} ({2:dd.MM} {3}) - {4} руб.",
        startPoint, finishPoint, tripDate, tripTime, priceTicket);
}

// === СТАТИЧЕСКИЕ МЕТОДЫ ===

String^ Trip::GetStatusDescription(String^ status) {
    if (status == "Запланирована") return "Поездка запланирована";
    if (status == "В пути") return "Поездка в процессе";
    if (status == "Завершена") return "Поездка завершена";
    if (status == "Отменена") return "Поездка отменена";
    return "Неизвестный статус";
}