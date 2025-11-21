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
    Workers::Workers(const std::string& surname = "",
        const std::string& name = "",
        const std::string& fatName = "",
        int salary = 0,
        bool available = true)
        : People(surname, name, fatName, "", "", ""),  // Вызов конструктора базового класса
        Salary(salary), Availability(available) {

        // Валидация параметров
        if (salary < 0) {
            throw std::invalid_argument("Зарплата не может быть отрицательной!");
        }
    }

    // Конструктор копирования
    Workers::Workers(const Workers& other)
        : People(other), Salary(other.Salary), Availability(other.Availability) {
        ;
    }

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