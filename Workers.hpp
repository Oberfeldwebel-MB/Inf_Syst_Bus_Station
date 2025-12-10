// Workers.h
#pragma once
#include "People.hpp"

namespace InfSystBusStation {

    public ref class Workers : public People {
    protected:
        int salary;
        bool isAvailable;
        String^ status;

    public:
        // Конструктор с доступностью по умолчанию (true)
        Workers(String^ fullName, String^ gender,
            String^ passportSeries, String^ passportNumber,
            int salary)
            : People(fullName, gender, passportSeries,
                passportNumber, ""),  // Пустая строка для email
            salary(salary), isAvailable(true), status("") {

            if (salary < 0) {
                throw gcnew ArgumentException("Зарплата не может быть отрицательной!");
            }
        }

        

        virtual ~Workers() {}

        // === ТРАДИЦИОННЫЕ ГЕТТЕРЫ И СЕТТЕРЫ ===
        int GetSalary() { return salary; }
        void SetSalary(int value);

        bool GetAvailability() { return isAvailable; }
        void SetAvailability(bool value) { isAvailable = value; }

        String^ GetStatus() { return status; }
        void SetStatus(String^ value) { status = value; }

        // === ВИРТУАЛЬНЫЕ МЕТОДЫ ===
        virtual void PrintInfo() override;
        virtual String^ GetFullInfo() override;
        virtual double CalculateDiscount() override;

        // === ДОПОЛНИТЕЛЬНЫЕ МЕТОДЫ ===
        void SetAvailable();
        void SetUnavailable(String^ reason);
        void ChangeWorkAvailability(bool available, String^ reason);
    };
}