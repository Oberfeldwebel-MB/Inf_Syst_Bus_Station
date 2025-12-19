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
        System::Collections::Generic::List<Driver^>^ GetAvailableDrivers();
        System::Collections::Generic::List<System::String^>^ GetAvailableDriverNames();

        // Старые методы
        void AddDriver(Driver^ driver);
        void AddDriver(System::String^ fullName, int salary, System::String^ gender,
            System::String^ license, System::String^ passportSeries,
            System::String^ passportNumber);
        Driver^ FindDriverByName(System::String^ fullName);
        bool RemoveDriver(System::String^ fullName);
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