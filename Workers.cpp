#include "Workers.hpp"

using namespace InfSystBusStation;
using namespace System;

void Workers::SetSalary(int value) {
    if (value < 0) {
        throw gcnew ArgumentException("Зарплата не может быть отрицательной!");
    }
    salary = value;
}

void Workers::PrintInfo() {
    People::PrintInfo(); // Вызов метода базового класса People
    Console::WriteLine("Должность: Сотрудник");
    Console::WriteLine("Зарплата: {0} руб.", salary);
    Console::WriteLine("Email: {0}", GetEmail()); // Добавляем email
    Console::WriteLine("Статус: {0}", isAvailable ? "Доступен" : "Не доступен");
}

String^ Workers::GetFullInfo() {
    return "Сотрудник: " + GetFullName() +
        " | Email: " + GetEmail() + // Добавляем email
        " | Зарплата: " + salary +
        " руб. | Статус: " + (isAvailable ? "Доступен" : "Занят");
}

double Workers::CalculateDiscount() {
    return 0.1; // 10% скидка
}

void Workers::SetAvailable() {
    isAvailable = true;
    status = "";
    Console::WriteLine("{0} теперь доступен для работы", GetFullName());
}

void Workers::SetUnavailable(String^ reason) {
    isAvailable = false;
    status = reason;
    if (!String::IsNullOrEmpty(reason)) {
        Console::WriteLine("{0} теперь недоступен (Причина: {1})",
            GetFullName(), reason);
    }
    else {
        Console::WriteLine("{0} теперь недоступен", GetFullName());
    }
}

void Workers::ChangeWorkAvailability(bool available, String^ reason) {
    Console::WriteLine("=== Изменение статуса работника ===");
    if (available) {
        SetAvailable();
    }
    else {
        SetUnavailable(reason);
    }
    Console::WriteLine("Текущий статус: {0}",
        isAvailable ? "Доступен" : "Не доступен");
    Console::WriteLine("==================================");
}