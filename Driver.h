#pragma once
#include "Workers.h"
#include <string>

class Driver : public Workers {
private:
    std::string Driver_license;
    std::string Last_med;
    std::string Current_trip;

public:
    Driver(const std::string& surname = "",
        const std::string& name = "",
        const std::string& fatName = "",
        int salary = 0,
        const std::string& license = "",
        const std::string& lastMed = "",
        const std::string& currentTrip = "") : Workers(surname, name, fatName, salary),
        Driver_license(license),
        Last_med(lastMed),
        Current_trip(currentTrip) {
    };

    ~Driver() = default;


    bool Check_need_med(const std::string& last_med);

    // методы для изменения переменных
    void Set_trip(const std::string& trip);

    // Методы для получения данных из переменных
    std::string GetLicense() const { return Driver_license; }
    std::string GetLastMedical() const { return Last_med; }
    std::string GetCurrentTrip() const { return Current_trip; }
};