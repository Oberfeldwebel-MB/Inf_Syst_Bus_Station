#pragma once
#include <string>
#include <vector>


#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

// Теперь управляемые заголовки
#include "Workers.hpp"

namespace InfSystBusStation {

    public ref class Driver : public Workers {
    private:
        String^ driverLicense;         
        String^ currentDriverTrip;     

    public:
        // Основной конструктор
        Driver(String^ fullName, String^ gender,
            String^ passportSeries, String^ passportNumber,
            int salary, String^ license)
            : Workers(fullName, gender, passportSeries,
                passportNumber, salary),  
            driverLicense(license),
            currentDriverTrip("") {
        }


        virtual ~Driver() {}

    public:
        bool IsAvailable() {
            return String::IsNullOrEmpty(currentDriverTrip);
        }

        void AssignToTrip(String^ tripRoute) {
            currentDriverTrip = tripRoute;
            // Если в базовом классе Workers есть метод SetUnavailable
            // SetUnavailable("На рейсе: " + tripRoute);
        }

        void ReleaseFromTrip() {
            currentDriverTrip = String::Empty;
        }

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

        String^ GetPassportSeries() {

            return Workers::GetPassportSeries(); 
        }

        String^ GetPassportNumber() {

            return Workers::GetPassportNumber();
        }

        // === ПЕРЕОПРЕДЕЛЕНИЕ ВИРТУАЛЬНЫХ МЕТОДОВ ===
        virtual void PrintInfo() override;
        virtual String^ GetFullInfo() override;
        virtual double CalculateDiscount() override;
    };
}