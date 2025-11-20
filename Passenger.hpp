#pragma once
#include <string>
#include <iostream>
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
        : People(surname, name, fatName),// вызов конструктора базового класса
        PsprtSer(psprtser), PsprtNum(psprtnum), Email(email) {
    }

    // Конструктор копирования
    Passenger(const Passenger& other);

    // перегрузка оператора для вывода
    friend std::ostream& operator<<(std::ostream& os, const Passenger& passenger);

    // Геттеры
    std::string GetPassportSeries() const { return PsprtSer; }
    std::string GetPassportNumber() const { return PsprtNum; }
    std::string GetEmail() const { return Email; }

    void PrintPassengerInfo() const;
};