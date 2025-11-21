#pragma once
#include "Workers.hpp"
#include <string>
#include <memory>
#include <iostream>

class Driver : public Workers {
private:
    std::string DriverLicense;
    std::string LastMed;
    std::string CurrentDriverTrip;

public:
    // Конструктор
    Driver::Driver(const std::string& surname,
        const std::string& name,
        const std::string& fatName,
        int salary,
        const std::string& license,
        const std::string& lastMed,
        const std::string& currentDriverTrip)
        : Workers(surname, name, fatName, salary), // вызов базового конструктора
        DriverLicense(license), LastMed(lastMed),
        CurrentDriverTrip(currentDriverTrip) {
    }

    // Конструктор копирования
    Driver::Driver(const Driver& other)
        : Workers(other),  // Вызов конструктора базового класса
        DriverLicense(other.DriverLicense),
        LastMed(other.LastMed),
        CurrentDriverTrip(other.CurrentDriverTrip) {
    }

    ~Driver() = default;

    // Основные методы
    bool CheckNeedMed(const std::string& current_date);
    void SetTrip(const std::string& trip);
    void PrintDriverInfo() const;

    // перегрузка оператора вывода
    friend std::ostream& operator<<(std::ostream& os, const Driver& driver);

    // Геттеры
    std::string GetLicense() const { return DriverLicense; }
    std::string GetLastMedical() const { return LastMed; }
    std::string GetDriverCurrentTrip() const { return CurrentDriverTrip; }

    // Сеттеры
    void SetLicense(const std::string& license) { DriverLicense = license; }
    void SetLastMedical(const std::string& date) { LastMed = date; }
};