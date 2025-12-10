#include "Bus.hpp"

using namespace InfSystBusStation;
using namespace System;

bool Bus::CheckAvailability() {
    return isAvailable &&
        techCondition != "Аварийное" &&
        techCondition != "На обслуживании";
}

void Bus::ChangeAvailability(bool state) {
    isAvailable = state;
    if (state) {
        Console::WriteLine("Автобус {0} теперь доступен", GetFormattedCode());
    }
    else {
        Console::WriteLine("Автобус {0} теперь недоступен", GetFormattedCode());
    }
}

void Bus::AssignToTrip() {
    if (!CheckAvailability()) {
        throw gcnew InvalidOperationException(
            String::Format("Автобус {0} недоступен для рейса!", GetFormattedCode()));
    }

    Console::WriteLine("Автобус {0} назначен на рейс", GetFullName());
}

void Bus::SendToMaintenance(String^ date) {
    if (String::IsNullOrEmpty(date)) {
        throw gcnew ArgumentException("Дата ТО не может быть пустой!");
    }

    lastMaintenance = date;
    techCondition = "На обслуживании";
    isAvailable = false;

    Console::WriteLine("Автобус {0} отправлен на ТО: {1}", GetFormattedCode(), date);
}

void Bus::ChangeTechCondition(String^ newState) {
    if (String::IsNullOrEmpty(newState)) {
        throw gcnew ArgumentException("Техническое состояние не может быть пустым!");
    }

    techCondition = newState;

    // Если состояние критическое - автобус недоступен
    if (newState == "Аварийное" || newState == "На обслуживании") {
        isAvailable = false;
    }

    Console::WriteLine("Автобус {0}: техническое состояние изменено на {1}",
        GetFormattedCode(), newState);
}

void Bus::PrintInfo() {
    Console::WriteLine("=== Данные автобуса ===");
    Console::WriteLine("Марка: {0}", brand);
    Console::WriteLine("Модель: {0}", model);
    Console::WriteLine("Количество мест: {0}", placeCount);
    Console::WriteLine("Код автобуса: {0}", GetFormattedCode());
    Console::WriteLine("Техническое состояние: {0}", techCondition);
    Console::WriteLine("Последнее ТО: {0}", lastMaintenance);
    Console::WriteLine("Статус: {0}", isAvailable ? "Доступен" : "Не доступен");
    Console::WriteLine("=======================");
}

bool Bus::NeedsMaintenance() {
    // Если ТО было больше 3 лет назад
    if (String::IsNullOrEmpty(lastMaintenance)) {
        return true; // Никогда не было ТО
    }

    try {
        // Разбираем дату формата "DD/MM/YYYY"
        array<String^>^ parts = lastMaintenance->Split('/');
        if (parts->Length >= 3) {
            int lastMaintenanceYear = Int32::Parse(parts[2]);
            int currentYear = DateTime::Now.Year;

            return (currentYear - lastMaintenanceYear) >= 3;
        }
    }
    catch (...) {
        // Если не удалось распарсить дату
    }

    return true; // Неизвестная дата - требуется ТО
}

bool Bus::IsInCriticalCondition() {
    return techCondition == "Аварийное" ||
        techCondition == "Неудовлетворительное" ||
        techCondition == "На обслуживании";
}