#pragma once
#include "People.hpp"
#include <iostream>
#include <memory>

class Workers : public People {
protected:
    int Salary;
    bool Availability;

public:
    // Конструктор
    Workers(const std::string& surname = "",
        const std::string& name = "",
        const std::string& fatName = "",
        int salary = 0,
        bool available = true);

    // Конструктор копирования
    Workers(const Workers& other);

    ~Workers() = default;

    // методы для наследников
protected:
    void MakeSalary(int newSalary);

public:
    bool GetAvailability() const;
    void change_work_avail(bool avail);

    // Геттеры
    int GetSalary() const { return Salary; }

    // Сеттеры
    void SetSalary(int salary) { Salary = salary; }
    void SetAvailability(bool available) { Availability = available; }
};