#pragma once
#include "Workers.hpp"
#include "Timing.hpp"
#include "Bus.hpp"
#include "Driver.hpp"

class Admin : public Workers {
public:
    Admin(const std::string& surname = "",
        const std::string& name = "",
        const std::string& fatName = "",
        int salary = 0) : Workers(surname, name, fatName, salary) {};

     ~Admin() = default;

    void ChangeBusTiming(Timing& timing);
    Bus* ChoseBus();
    Driver* ChoseDriver();
};