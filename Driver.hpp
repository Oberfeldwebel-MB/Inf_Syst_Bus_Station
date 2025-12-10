// Driver.h
#pragma once
#include "Workers.hpp"

namespace InfSystBusStation {

    public ref class Driver : public Workers {
    private:
        String^ driverLicense;         // Водительские права
        String^ currentDriverTrip;     // Текущий рейс

    public:
        // Основной конструктор
        Driver(String^ fullName, String^ gender,
            String^ passportSeries, String^ passportNumber,
            int salary, String^ license)
            : Workers(fullName, gender, passportSeries,
                passportNumber, salary),  // Базовый конструктор Workers
            driverLicense(license),
            currentDriverTrip("") {
        }


        virtual ~Driver() {}

        // === ГЕТТЕРЫ И СЕТТЕРЫ ===
        String^ GetLicense() { return driverLicense; }
        void SetLicense(String^ value) { driverLicense = value; }

        String^ GetCurrentTrip() { return currentDriverTrip; }
        void SetCurrentTrip(String^ value) {
            currentDriverTrip = value;
            if (!String::IsNullOrEmpty(value)) {
                SetUnavailable("На рейсе: " + value);
            }
        }

        // === ПЕРЕОПРЕДЕЛЕНИЕ ВИРТУАЛЬНЫХ МЕТОДОВ ===
        virtual void PrintInfo() override;
        virtual String^ GetFullInfo() override;
        virtual double CalculateDiscount() override;
    };
}