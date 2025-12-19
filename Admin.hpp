#pragma once

#include "Workers.hpp"     
#include "DriversList.hpp"
#include "BusList.hpp"
#include "TripList.hpp"
#include "Search.hpp"

namespace InfSystBusStation {

    public ref class Admin : public Workers {
    private:
        DriversList^ driversList;
        BusList^ busList;
        TripList^ tripList;

        // Данные администратора 
        String^ adminPassword;
        DateTime hireDate;

    public:
        // Конструктор Admin 
        Admin(String^ password, String^ fullName,
            String^ passportSeries, String^ passportNumber,
            int salary, String^ email);

        ~Admin();

        // === СИСТЕМНЫЕ МЕТОДЫ ===
        void InitializeSystem();
        bool Authenticate(String^ email, String^ password); // Используем email вместо логина
        void ChangePassword(String^ oldPassword, String^ newPassword);



        // Автобусы (делегирует BusList)
        void ShowBusManagementForm(Form^ owner);

        // Водители (делегирует DriversList)
        void ShowDriverManagementForm(Form^ owner);

        // Поездки (делегирует TripList)
        void ShowTripManagementForm(Form^ owner);

        List<Driver^>^ FindAvailableDrivers();

        // === СТАТИСТИКА ===
        String^ GetSystemStatistics();
        void GenerateReport(String^ reportType);

        // === ПЕРЕОПРЕДЕЛЕНИЕ ВИРТУАЛЬНЫХ МЕТОДОВ ===
        virtual void PrintInfo() override;
        virtual String^ GetFullInfo() override;
        virtual double CalculateDiscount() override;

        // === СВОЙСТВА ===
        property DateTime HireDate {
            DateTime get() { return hireDate; }
        }

        property bool IsSystemInitialized {
            bool get() {
                return driversList != nullptr &&
                    busList != nullptr &&
                    tripList != nullptr;
            }
        }

        // Свойства для доступа к подсистема
        property DriversList^ DriverSystem {
            DriversList^ get() { return driversList; }
        }

        property BusList^ BusSystem {
            BusList^ get() { return busList; }
        }

        property TripList^ TripSystem {
            TripList^ get() { return tripList; }
        }

        // Свойство для пароля 
        property String^ Password {
            String^ get() { return adminPassword; }
        }

    public:
        void SetPassword(String^ newPassword) {
            adminPassword = newPassword;
        }
    };
}