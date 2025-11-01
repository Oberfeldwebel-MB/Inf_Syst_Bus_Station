#pragma once
#include <string>
#include "People.hpp"

class Passenger : public People {
private:
    std::string PsprtSer;
    std::string PsprtNum;
    std::string Email;

public:
    Passenger(const std::string& surname = "",
        const std::string& name = "",
        const std::string& fatName = "",
        const std::string& psprtser = "",
        const std::string& psprtnum = "",
        const std::string& email = "")
        : People(surname, name, fatName),
        PsprtSer(psprtser), PsprtNum(psprtnum), Email(email) {
    }

    // Геттеры для данных пассажира
    std::string GetPassportSeries() const { return PsprtSer; }
    std::string GetPassportNumber() const { return PsprtNum; }
    std::string GetEmail() const { return Email; }

    void PrintPassengerInfo() const;
};