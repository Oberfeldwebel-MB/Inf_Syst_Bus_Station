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
    Workers(const std::string& fio,
        int salary,
        bool available)
        : People(fio, "", "", ""),
        Salary(salary), Availability(available) {

        if (salary < 0) {
            throw std::invalid_argument("Зарплата не может быть отрицательной!");
        }

        std::cout << "Workers constructor called for: " << GetFullName() << std::endl;
    }


    // Виртуальный деструктор
    ~Workers() {
        std::cout << "Workers destructor called for: " << GetFullName() << std::endl;
    }

    // Запрет конструктора копирования
    Workers(const Workers&) = delete;

    Workers& operator=(const Workers& other);

    // Переопределение виртуальных функций базового класса
    void PrintInfo() const override;
    std::string GetFullInfo() const override;
    double CalculateDiscount() const override;

    // ВИРТУАЛЬНЫЕ ФУНКЦИИ для изменения статуса
    virtual void SetAvailable();
    virtual void SetUnavailable(const std::string& reason = "Занят");

    //функция, которая вызывает виртуальные
    void ChangeWorkAvailability(bool available, const std::string& reason = "") {
        std::cout << "=== Изменение статуса работника ===" << std::endl;
        if (available) {
            SetAvailable();  // Вызов виртуальной функции
        }
        else {
            SetUnavailable(reason);  // Вызов виртуальной функции
        }
        std::cout << "Текущий статус: " << (Availability ? "Доступен" : "Не доступен") << std::endl;
        std::cout << "==================================" << std::endl;
    }

    // Перегрузка методов
    void SetPersonalData(int data) override;

    // Для клонирования - глубокое клонирование
    People* Clone() const override;

    // Геттеры
    int GetSalary() const { return Salary; }
    bool GetAvailability() const { return Availability; }

    // Сеттеры
    void SetSalary(int salary);
    void change_work_avail(bool avail) {
        ChangeWorkAvailability(avail);
    }
};