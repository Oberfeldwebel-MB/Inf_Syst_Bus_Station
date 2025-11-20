#pragma once
#include "Workers.hpp"
#include "Timing.hpp"
#include "Bus.hpp"
#include "Driver.hpp"
#include <memory>

class Admin : public Workers {
private:
    std::shared_ptr<Timing> currentTiming;

public:
    Admin(const std::string& surname = "",
        const std::string& name = "",
        const std::string& fatName = "",
        int salary = 0,
        int level = 1) : Workers(surname, name, fatName, salary){
    };

    ~Admin() = default;


    void ChangeBusTiming(std::shared_ptr<Timing> timing);
    std::shared_ptr<Bus> ChoseBus();
    std::shared_ptr<Driver> ChoseDriver();
};