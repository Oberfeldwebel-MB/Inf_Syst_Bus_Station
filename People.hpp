// People.hpp
#pragma once
#include "ISystemObject.hpp"  // ДОБАВИЛИ
#include <string>
#include <iostream>
#include <memory>
#include <array>

class People : public ISystemObject {
protected:
    std::string FIO;
    std::string Gender;
    std::string PsprtSer;
    std::string PsprtNum;
    std::string Email;
    std::array<int, 2> personalData;  // ЗАМЕНИЛИ сырой указатель на std::array

public:
    // Конструктор
    People(const std::string& fio,
        const std::string& gender,
        const std::string& psprtser,
        const std::string& psprtnum,
        const std::string& email) : FIO(fio), Gender(gender),
        PsprtSer(psprtser), PsprtNum(psprtnum), Email(email),
        personalData({ 0, 0 }) {  // Инициализация std::array
        std::cout << "People constructor called for: " << GetFullName() << std::endl;
    }

    // Конструктор копирования
    People(const People& other) = default;

    // Виртуальный деструктор
    virtual People* Clone() const = 0;

    // === РЕАЛИЗАЦИЯ ИНТЕРФЕЙСА ISystemObject ===
    std::string getId() const override;
    std::string getName() const override;
    std::string getType() const override;
    void displayInfo() const override;
    double getSortValue() const override;
    bool containsText(const std::string& text) const override;
    bool isMarkedForRemoval() const override;

    // === СУЩЕСТВУЮЩИЕ МЕТОДЫ People (без изменений) ===
    virtual void PrintInfo() const;
    virtual std::string GetFullInfo() const;

    // Абстрактная функция
    virtual double CalculateDiscount() const = 0;

    void DisplayAllInfo();

    // Перегруженные методы
    virtual void SetPersonalData(int data);
    virtual void SetPersonalData(int data1, int data2);

    // Геттеры
    std::string GetSurname() const { return Surname; }
    std::string GetName() const { return Name; }
    std::string GetFatName() const { return FatName; }
    std::string GetPassportSeries() const { return PsprtSer; }
    std::string GetPassportNumber() const { return PsprtNum; }
    std::string GetEmail() const { return Email; }
    std::string GetFullName() const;

    // Сеттеры
    virtual void SetSurname(const std::string& surname) { Surname = surname; }
    virtual void SetName(const std::string& name) { Name = name; }
    virtual void SetFatName(const std::string& fatName) { FatName = fatName; }
    virtual void SetPassport(const std::string& series, const std::string& number);
    virtual void SetEmail(const std::string& email) { Email = email; }

    // Перегрузка оператора вывода
    friend std::ostream& operator<<(std::ostream& os, const People& person);

    // Для STL алгоритмов сортировки
    bool operator<(const People& other) const;
};