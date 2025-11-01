#pragma once
#include <string>

class People {
protected:
    // Защищенные переменные доступные для наследников
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
        const std::string& email = "")
        : Surname(surname), Name(name), FatName(fatName), PsprtSer(psprtser), PsprtNum(psprtnum),
            Email(email){}
    
    //деконструктор
    ~People() = default;

    // Публичные Методы класса
    void PrintInfo() const;
    //геттеры
    std::string GetSurname() const { return Surname; }
    std::string GetName() const { return Name; }
    std::string GetFatName() const { return FatName; }
    std::string GetPassportSeries() const { return PsprtSer; }
    std::string GetPassportNumber() const { return PsprtNum; }
    std::string GetEmail() const { return Email; }
    std::string GetFullName() const;
};