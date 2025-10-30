#pragma once
#include <string>
#include "People.h"

class Passenger : public People {
private:
    std::string Psprt_ser;
    std::string Psprt_num;
    std::string Email;

public:
    Passenger(const std::string& surname = "",
        const std::string& name = "",
        const std::string& fatName = "",
        const std::string& psprt_ser = "",
        const std::string& psprt_num = "",
        const std::string& email = "")
        : People(surname, name, fatName),
        Psprt_ser(psprt_ser), Psprt_num(psprt_num), Email(email) {
    }

    // Геттеры для данных пассажира
    std::string GetPassportSeries() const { return Psprt_ser; }
    std::string GetPassportNumber() const { return Psprt_num; }
    std::string GetEmail() const { return Email; }

    void PrintPassengerInfo() const;
};