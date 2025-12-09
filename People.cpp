// People.cpp
#include "People.hpp"
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <algorithm>

// Реализация интерфейса

std::string People::getId() const {
    return PsprtSer + "-" + PsprtNum;  
}

std::string People::getName() const {
    return GetFullName();
}

std::string People::getType() const {
    return "Person";
}

void People::displayInfo() const {
    PrintInfo();
}

double People::getSortValue() const {
    // Для сортировки: приоритет по длине ФИО + наличие email
    double value = GetFullName().length() * 10.0;
    if (!Email.empty()) value += 50.0;
    // Добавляем вес по персональным данным
    value += personalData[0] * 0.5 + personalData[1] * 0.3;
    return value;
}

bool People::containsText(const std::string& text) const {
    // Ищем в ФИО, паспорте, email (без учета регистра)
    std::string searchLower = toLower(text);

    // Приводим все поля к нижнему регистру для поиска
    std::string fullNameLower = toLower(GetFullName());
    std::string passportLower = toLower(PsprtSer + PsprtNum);
    std::string emailLower = toLower(Email);

    return fullNameLower.find(searchLower) != std::string::npos ||
        passportLower.find(searchLower) != std::string::npos ||
        emailLower.find(searchLower) != std::string::npos;
}

bool People::isMarkedForRemoval() const {
    // Помечаем для удаления, если паспортные данные недействительны
    // или email содержит "deleted"
    return PsprtSer.empty() || PsprtNum.empty() ||
        Email.find("deleted") != std::string::npos;
}

// === СУЩЕСТВУЮЩИЕ МЕТОДЫ People ===

void People::PrintInfo() const {
    std::cout << "=== Информация о человеке ===" << std::endl;
    std::cout << "ФИО: " << Surname << " " << Name << " " << FatName << std::endl;
    std::cout << "Паспорт: " << PsprtSer << " " << PsprtNum << std::endl;
    if (!Email.empty()) {
        std::cout << "Email: " << Email << std::endl;
    }
    std::cout << "Personal Data: [" << personalData[0] << ", " << personalData[1] << "]" << std::endl;
}

std::string People::GetFullInfo() const {
    return Surname + " " + Name + " " + FatName + " (" + PsprtSer + " " + PsprtNum + ")";
}

std::string People::GetFullName() const {
    return Surname + " " + Name + " " + FatName;
}

void People::DisplayAllInfo() {
    std::cout << "=== Полная информация ===" << std::endl;
    PrintInfo();
    std::cout << "Скидка: " << CalculateDiscount() * 100 << "%" << std::endl;
    std::cout << "=========================" << std::endl;
}

// Перегруженные методы SetPersonalData
void People::SetPersonalData(int data) {
    personalData[0] = data;
    std::cout << "Установлены персональные данные: " << data << std::endl;
}

void People::SetPersonalData(int data1, int data2) {
    personalData[0] = data1;
    personalData[1] = data2;
    std::cout << "Установлены персональные данные: " << data1 << ", " << data2 << std::endl;
}

void People::SetPassport(const std::string& series, const std::string& number) {
    PsprtSer = series;
    PsprtNum = number;
    std::cout << "Паспортные данные обновлены: " << series << " " << number << std::endl;
}

bool People::operator<(const People& other) const {
    // Сортируем по фамилии, затем по имени
    if (Surname != other.Surname) {
        return Surname < other.Surname;
    }
    return Name < other.Name;
}

// Перегрузка оператора для вывода
std::ostream& operator<<(std::ostream& os, const People& person) {
    os << person.Surname << " " << person.Name << " " << person.FatName;

    if (!person.PsprtSer.empty() && !person.PsprtNum.empty()) {
        os << " [" << person.PsprtSer << " " << person.PsprtNum << "]";
    }

    if (!person.Email.empty()) {
        os << " <" << person.Email << ">";
    }

    return os;
}