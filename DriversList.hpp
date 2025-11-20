#pragma once
#include <vector>
#include <memory>
#include "Driver.hpp"

class DriverList {
private:
    std::vector<std::shared_ptr<Driver>> drivers;  

public:
    DriverList() = default;
    ~DriverList() = default;

    // Конструктор копирования
    DriverList(const DriverList& other);

    // Возвращаем константную и неконстантную ссылки
    const std::vector<std::shared_ptr<Driver>>& GetDrivers() const { return drivers; }
    std::vector<std::shared_ptr<Driver>>& GetDrivers() { return drivers; }

    // Основные методы с умными указателями
    void AddDriver(std::shared_ptr<Driver> driver);
    std::shared_ptr<Driver> FindDriverByName(const std::string& fullName);
    bool RemoveDriver(const std::string& fullName);
    void DisplayAllDrivers() const;

    // Перегрузка операторов
    friend std::ostream& operator<<(std::ostream& os, const DriverList& driverList);

    // Дружественная функция для поиска по критериям
    friend std::vector<std::shared_ptr<Driver>> FindAvailableDrivers(const DriverList& list);
};