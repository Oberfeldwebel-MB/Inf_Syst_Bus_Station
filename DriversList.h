#pragma once

#include <vector>
#include "Driver.h"

class DriverList {
private:
    std::vector<Driver> drivers;

public:
    DriverList() = default;
    ~DriverList() = default;

    std::vector<Driver>& GetDrivers() { return drivers; }


    void AddDriver(const Driver& driver);
    Driver* FindDriverByName(const std::string& fullName);
    bool RemoveDriver(const std::string& fullName);
    void DisplayAllDrivers();
};
