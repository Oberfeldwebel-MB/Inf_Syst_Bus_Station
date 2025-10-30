#pragma once
#include "People.h"

class Workers : public People {
protected:
    //«ащищенны переменные, доступные дл€ наследников
    int Salary;
    bool Availability;
public:
    //  онструктор
    Workers(const std::string& surname = "",
        const std::string& name = "",
        const std::string& fatName = "",
        int salary = 0,
        bool available = true) : People(surname, name, fatName), Salary(salary), Availability(available) {
    }

    // методы дл€ наследников
protected:
    void Make_Salary(int newSalary);
public:
    bool GetAvailability() const;
    void change_work_avail(bool avail);
};