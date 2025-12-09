#pragma once
#include "People.hpp"
#include <iostream>

class Passenger : public People {
private:
    std::string PsprtSer;
    std::string PsprtNum;
    std::string Email;
    int* loyaltyPoints; // Для глубокого клонирования

public:
    // Конструктор с вызовом конструктора базового класса
    Passenger(const std::string& surname,
        const std::string& name,
        const std::string& fatName,
        const std::string& psprtser,
        const std::string& psprtnum,
        const std::string& email)
        : People(surname, name, fatName, psprtser, psprtnum, email), // Вызов базового
        PsprtSer(psprtser), PsprtNum(psprtnum), Email(email) {

        loyaltyPoints = new int[2] {0, 100}; // Бонусные баллы
        std::cout << "Passenger constructor called for: " << GetFullName() << std::endl;
    }

    // Конструктор копирования
    Passenger::Passenger(const Passenger& other)
        : People(other.GetSurname(), other.GetName(), other.GetFatName(),
            other.GetPassportSeries(), other.GetPassportNumber(), other.GetEmail()),
        PsprtSer(other.PsprtSer), PsprtNum(other.PsprtNum), Email(other.Email) {

        // Глубокое копирование массива
        loyaltyPoints = new int[2];
        loyaltyPoints[0] = other.loyaltyPoints[0];
        loyaltyPoints[1] = other.loyaltyPoints[1];
        std::cout << "Passenger copy constructor called (deep copy)" << std::endl;
    }
    // Виртуальный деструктор
    ~Passenger() {
        delete[] loyaltyPoints;
        std::cout << "Passenger destructor called for: " << GetFullName() << std::endl;
    }

    // Переопределение виртуальных функций из People
    void PrintInfo() const override; // Перегрузка с вызовом базового
    std::string GetFullInfo() const override; // Перегрузка без вызова
    double CalculateDiscount() const override;

    // Перегрузка методов
    void SetPersonalData(int data) override; // С вызовом базового
    void SetPersonalData(int points, bool add); // Перегрузка

    // Для клонирования - глубокое клонирование
    People* Clone() const override;

    // Геттеры
    std::string GetPassportSeries() const { return PsprtSer; }
    std::string GetPassportNumber() const { return PsprtNum; }
    std::string GetEmail() const { return Email; }

    void PrintPassengerInfo() const;

    friend std::ostream& operator<<(std::ostream& os, const Passenger& passenger);
};