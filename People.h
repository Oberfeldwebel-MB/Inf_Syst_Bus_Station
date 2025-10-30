#pragma once
#include <string>

class People {
protected:
    // Защищенные переменные доступные для наследников
    std::string Surname;
    std::string Name;
    std::string Fat_name;
    std::string Psprt_ser;
    std::string Psprt_num;
    std::string Email;

public:
    // Конструктор
    People(const std::string& surname = "",
        const std::string& name = "",
        const std::string& fatName = "",
        const std::string& psprt_ser = "",
        const std::string& psprt_num = "",
        const std::string& email = "")
        : Surname(surname), Name(name), Fat_name(fatName), Psprt_ser(psprt_ser), Psprt_num(psprt_num),
            Email(email){}
    
    //деконструктор
    ~People() = default;

    // Публичные Методы класса
    void PrintInfo() const;
    //геттеры
    std::string GetSurname() const { return Surname; }
    std::string GetName() const { return Name; }
    std::string GetFatName() const { return Fat_name; }
    std::string GetPassportSeries() const { return Psprt_ser; }
    std::string GetPassportNumber() const { return Psprt_num; }
    std::string GetEmail() const { return Email; }
    std::string GetFullName() const;
};