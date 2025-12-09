#pragma once
#include "Workers.hpp"
#include <string>
#include <memory>
#include <iostream>

class Driver : public Workers {
private:
    std::string DriverLicense;
    std::string CurrentDriverTrip;
    int* drivenRoutes; // Для глубокого клонирования

public:
    // Конструктор с вызовом конструктора базового класса
    Driver::Driver(const std::string&  fio,
        int salary,
        const std::string& license,
        const std::string& gender,
        const std::string& currentDriverTrip)
        : Workers(fio, gender, salary, true), // Вызов конструктора базового класса
        DriverLicense(license), CurrentDriverTrip(currentDriverTrip) {
    }

    // Перегрузка оператора присваивания
    Driver& operator=(const Driver& other);

    // ПЕРЕОПРЕДЕЛЕНИЕ ВИРТУАЛЬНЫХ ФУНКЦИЙ
    void SetAvailable() override; // Перегрузка с вызовом базового класса
    void SetUnavailable(const std::string& reason = "Занят") override; // Перегрузка с вызовом базового класса

    // Перегрузка методов базового класса
    void PrintInfo() const override; // Перегрузка с вызовом базового класса
    std::string GetFullInfo() const override; // Перегрузка без вызова базового класса
    double CalculateDiscount() const override;

    // Виртуальные функции
    virtual void DriveBus();
    virtual void PerformMaintenance();

    // Не виртуальная функция, которая вызывает виртуальные
    void WorkShift() {
        std::cout << "=== Смена водителя ===" << std::endl;
        DriveBus();           // Вызов виртуальной функции
        PerformMaintenance(); // Вызов виртуальной функции
        std::cout << "=====================" << std::endl;
    }

    // Перегрузка методов
    void SetPersonalData(int data) override; // Перегрузка без вызова базового класса

    // Для клонирования - глубокое клонирование
    People* Clone() const override;

    // Основные методы (из оригинального класса)
    bool CheckNeedMed(const std::string& current_date);
    void SetTrip(const std::string& trip);
    void PrintDriverInfo() const;

    // Геттеры
    std::string GetLicense() const { return DriverLicense; }
    std::string GetLastGender() const { return Gender; }
    std::string GetDriverCurrentTrip() const { return CurrentDriverTrip; }
    const int* GetDrivenRoutes() const { return drivenRoutes; }

    // Сеттеры
    void SetLicense(const std::string& license) { DriverLicense = license; }

    // Перегрузка оператора вывода
    friend std::ostream& operator<<(std::ostream& os, const Driver& driver);
};