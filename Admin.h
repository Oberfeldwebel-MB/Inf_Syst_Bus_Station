#pragma once
#include "Workers.h"
#include "Timing.h"
#include "Bus.h"
#include "Driver.h"

class Admin : public Workers {
public:
    Admin(const std::string& surname = "",
        const std::string& name = "",
        const std::string& fatName = "",
        int salary = 0) : Workers(surname, name, fatName, salary) {};

     ~Admin() = default;

    void Change_bus_timing(Timing& timing);
    Bus* Chose_bus();
    Driver* Chose_driver();
};