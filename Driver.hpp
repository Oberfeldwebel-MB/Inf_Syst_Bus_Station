#pragma once
#include "Workers.hpp"
#include <string>

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
        const std::string& currentDriverTrip = "") : Workers(surname, name, fatName, salary),
        DriverLicense(license),
        LastMed(lastMed),
        CurrentDriverTrip(currentDriverTrip) {
    };

    ~Driver() = default;


    bool CheckNeedMed(const std::string& last_med);

    // методы для изменения переменных
    void SetTrip(const std::string& trip);

    // Методы для получения данных из переменных
    std::string GetLicense() const { return DriverLicense; }
    std::string GetLastMedical() const { return LastMed; }
    std::string GetDriverCurrentTrip() const { return CurrentDriverTrip; }
};