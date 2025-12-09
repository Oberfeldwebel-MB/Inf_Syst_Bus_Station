#include "Workers.hpp"
#include <iostream>
#include <stdexcept>

Workers& Workers::operator=(const Workers& other) {
    if (this != &other) {
        // Копируем данные базового класса
        SetSurname(other.GetSurname());
        SetName(other.GetName());
        SetFatName(other.GetFatName());
        SetPassport(other.GetPassportSeries(), other.GetPassportNumber());
        SetEmail(other.GetEmail());

        // Копируем данные Workers
        Salary = other.Salary;
        Availability = other.Availability;
    }
    return *this;
}

/// Перегрузка метода с вызовом базового класса
void Workers::PrintInfo() const {
    People::PrintInfo(); // Вызов метода базового класса
    std::cout << "Должность: Сотрудник" << std::endl;
    std::cout << "Зарплата: " << Salary << " руб." << std::endl;
    std::cout << "Статус: " << (Availability ? "Доступен" : "Не доступен") << std::endl;
}

// Перегрузка метода без вызова базового класса
std::string Workers::GetFullInfo() const {
    return "Сотрудник: " + GetFullName() + " | Зарплата: " + std::to_string(Salary) +
        " | Статус: " + (Availability ? "Доступен" : "Занят");
}

// Реализация виртуальной функции из People
double Workers::CalculateDiscount() const {
    return 0.1; // 10% скидка для сотрудников
}

// виртуальная функция для изменения статуса
void Workers::SetAvailable() {
    Availability = true;
    std::cout << GetFullName() << " теперь доступен для работы" << std::endl;
}

void Workers::SetUnavailable(const std::string& reason) {
    Availability = false;
    std::cout << GetFullName() << " теперь недоступен";
    if (!reason.empty()) {
        std::cout << " (Причина: " << reason << ")";
    }
    std::cout << std::endl;
}

// Перегрузка метода с вызовом базового класса
void Workers::SetPersonalData(int data) {
    People::SetPersonalData(data);
    std::cout << "Данные сотрудника обновлены" << std::endl;
}

// Глубокое клонирование
People* Workers::Clone() const {
    std::cout << "Создание глубокой копии работника: " << GetFullName() << std::endl;
    return new Workers(*this);
}

void Workers::SetSalary(int salary) {
    if (salary < 0) {
        throw std::invalid_argument("Зарплата не может быть отрицательной!");
    }
    Salary = salary;
}