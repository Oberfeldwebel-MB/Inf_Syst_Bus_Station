#pragma once
#include <string>
#include <iostream>
#include <memory>

class People {
protected:
    std::string Surname;
    std::string Name;
    std::string FatName;
    std::string PsprtSer;
    std::string PsprtNum;
    std::string Email;

public:
    // Конструктор
    People(const std::string& surname = "",
        const std::string& name = "",
        const std::string& fatName = "",
        const std::string& psprtser = "",
        const std::string& psprtnum = "",
        const std::string& email = "");

    // Конструктор копирования
    People(const People& other);

    // Виртуальный деструктор
    virtual ~People() = default;

    // перегрузка оператора вывода
    friend std::ostream& operator<<(std::ostream& os, const People& person);

    // Публичные методы класса
    void PrintInfo() const;

    // Геттеры
    std::string GetSurname() const { return Surname; }
    std::string GetName() const { return Name; }
    std::string GetFatName() const { return FatName; }
    std::string GetPassportSeries() const { return PsprtSer; }
    std::string GetPassportNumber() const { return PsprtNum; }
    std::string GetEmail() const { return Email; }
    std::string GetFullName() const;

    // Сеттеры
    void SetSurname(const std::string& surname) { Surname = surname; }
    void SetName(const std::string& name) { Name = name; }
    void SetFatName(const std::string& fatName) { FatName = fatName; }
    void SetPassport(const std::string& series, const std::string& number) {
        PsprtSer = series;
        PsprtNum = number;
    }
    void SetEmail(const std::string& email) { Email = email; }
};