#include "Passenger.hpp"
#include <iostream>

// Перегрузка метода с вызовом базового класса
void Passenger::PrintInfo() const {
    People::PrintInfo(); // Вызов базового метода
    std::cout << "Статус: Пассажир" << std::endl;
    std::cout << "Бонусные баллы: " << loyaltyPoints[0] << "/" << loyaltyPoints[1] << std::endl;
}

// Перегрузка метода без вызова базового класса
std::string Passenger::GetFullInfo() const {
    return "Пассажир: " + GetFullName() +
        " | Паспорт: " + PsprtSer + " " + PsprtNum +
        " | Баллы: " + std::to_string(loyaltyPoints[0]);
}

// Реализация абстрактного метода из People
double Passenger::CalculateDiscount() const {
    // Скидка зависит от бонусных баллов
    double discount = loyaltyPoints[0] * 0.001; // 0.1% за каждый балл
    return discount > 0.2 ? 0.2 : discount; // Максимум 20%
}

// Перегрузка метода с вызовом базового класса
void Passenger::SetPersonalData(int data) {
    People::SetPersonalData(data); // Вызов базового метода
    std::cout << "Данные пассажира обновлены" << std::endl;
}

// Перегрузка метода
void Passenger::SetPersonalData(int points, bool add) {
    if (add) {
        loyaltyPoints[0] += points;
        std::cout << "Начислено " << points << " бонусных баллов" << std::endl;
    }
    else {
        loyaltyPoints[0] = points;
        std::cout << "Установлено " << points << " бонусных баллов" << std::endl;
    }
}

// Глубокое клонирование
People* Passenger::Clone() const {
    std::cout << "Создание глубокой копии пассажира: " << GetFullName() << std::endl;
    return new Passenger(*this);
}

void Passenger::PrintPassengerInfo() const {
    std::cout << "=== Информация о пассажире ===\n";
    std::cout << "ФИО: " << GetFullName() << "\n";
    std::cout << "Паспорт: " << PsprtSer << " " << PsprtNum << "\n";
    std::cout << "Email: " << Email << "\n";
    std::cout << "Бонусные баллы: " << loyaltyPoints[0] << "\n";
    std::cout << "Скидка: " << (CalculateDiscount() * 100) << "%\n";
    std::cout << "==============================\n";
}

// Перегрузка оператора вывода
std::ostream& operator<<(std::ostream& os, const Passenger& passenger) {
    os << "Пассажир: " << passenger.GetFullName();

    if (!passenger.PsprtSer.empty() && !passenger.PsprtNum.empty()) {
        os << " (паспорт: " << passenger.PsprtSer << " " << passenger.PsprtNum << ")";
    }

    if (!passenger.Email.empty()) {
        os << " <" << passenger.Email << ">";
    }

    return os;
}