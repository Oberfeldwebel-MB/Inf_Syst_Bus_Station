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
    Driver(const std::string& surname = "",
        const std::string& name = "",
        const std::string& fatName = "",
        int salary = 0,
        const std::string& license = "",
        const std::string& lastMed = "",
        const std::string& currentDriverTrip = "");

    // Конструктор копирования
    Driver(const Driver& other);

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