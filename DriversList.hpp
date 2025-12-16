// DriversList.h
#pragma once
#include "Driver.hpp"

namespace InfSystBusStation {

    public ref class DriversList {
    private:
        System::Collections::Generic::List<Driver^>^ drivers;

    public:
        DriversList();
        ~DriversList();

    public:
        List<Driver^>^ GetAvailableDrivers();
        List<String^>^ GetAvailableDriverNames();

        // Старые методы
        void AddDriver(Driver^ driver);
        void AddDriver(String^ fullName, int salary, String^ gender,
            String^ license, String^ passportSeries,
            String^ passportNumber);
        Driver^ FindDriverByName(String^ fullName);
        bool RemoveDriver(String^ fullName);
        void DisplayAllDrivers();

        // Свойства
        property System::Collections::Generic::List<Driver^>^ AllDrivers {
            System::Collections::Generic::List<Driver^>^ get();
        }

        property int Count {
            int get();
        }
    };
}