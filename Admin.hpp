#pragma once
#include "Workers.hpp"
#include "Timing.hpp"
#include "Bus.hpp"
#include "Driver.hpp"
#include <memory>
#include <vector>
#include <string>
#include <array>

class Admin : public Workers {
private:
    std::shared_ptr<Timing> currentTiming;
    std::array<std::string, 3> adminLogs;  // ЗАМЕНА сырого указателя

public:
    // Конструктор с вызовом конструктора базового класса
    Admin(const std::string& surname,
        const std::string& name,
        const std::string& fatName,
        int salary) : Workers(surname, name, fatName, salary, true), // Вызываем конструктор Workers
        currentTiming(nullptr),                        // Инициализируем умный указатель
        adminLogs({ "Создан аккаунт", "Готов к работе", "" }) // Инициализируем array
    {
        std::cout << "Admin constructor called for: " << GetFullName()
            << " (Salary: " << salary << ")" << std::endl;
    }

    // Виртуальный деструктор
    virtual ~Admin();

    // Запрет конструктора копирования по умолчанию
    Admin(const Admin&) = delete;

    // Перегрузка оператора присваивания
    Admin& operator=(const Workers& other);

    // переопределение виртуальных функций
    void SetAvailable() override;
    void SetUnavailable(const std::string& reason = "Занят") override;

    // Перегрузка методов базового класса
    void PrintInfo() const override;
    std::string GetFullInfo() const override;
    double CalculateDiscount() const override;

    // Виртуальные функции
    virtual void ManageSchedule();

    // Перегрузка методов
    void SetPersonalData(int data) override;

    // Клонирование - ИСПРАВЛЕНО
    People* Clone() const override;

    // Оригинальные методы класса Admin
    void ChangeBusTiming(std::shared_ptr<Timing> timing);
    std::shared_ptr<Bus> ChoseBus();
    std::shared_ptr<Driver> ChoseDriver();

    // Геттеры
    std::shared_ptr<Timing> GetCurrentTiming() const { return currentTiming; }
    const std::array<std::string, 3>& GetAdminLogs() const { return adminLogs; }
};