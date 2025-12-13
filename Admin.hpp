// Admin.hpp
#pragma once

#include "DriversList.hpp"
#include "BusList.hpp"
#include "TripList.hpp"

namespace InfSystBusStation {

    public ref class Admin {
    private:
        DriversList^ driversList;
        BusList^ busList;
        TripList^ tripList;

    public:
        Admin();
        ~Admin();

        // === хмхжхюкхгюжхъ ===
        void Initialize();

        // === лерндш дкъ бндхрекеи ===
        bool AddDriver(String^ fio, String^ gender, String^ passportSeries,
            String^ passportNumber, int salary, String^ license);
        bool RemoveDriver(String^ fio);
        bool EditDriver(String^ oldFio, String^ newFio, String^ newGender,
            String^ newPassportSeries, String^ newPassportNumber,
            int newSalary, String^ newLicense);
        Driver^ FindDriver(String^ fio);
        bool IsDriverAvailable(String^ fio);

        // === лерндш дкъ юбрнасянб ===
        bool AddBus(String^ brand, String^ model, int placeCount,
            String^ code, String^ techCondition, String^ lastMaintenance);
        bool RemoveBus(String^ code);
        bool EditBus(String^ oldCode, String^ newBrand, String^ newModel,
            int newPlaceCount, String^ newTechCondition, String^ newLastMaintenance);
        Bus^ FindBus(String^ code);
        bool IsBusAvailable(String^ code);

        // === лерндш дкъ онегднй ===
        bool AddTrip(String^ startPoint, String^ finishPoint, int price,
            String^ busCode, String^ driverFio,
            DateTime depDate, String^ depTime);
        bool RemoveTrip(String^ route);
        bool EditTrip(String^ oldRoute, String^ newStartPoint, String^ newFinishPoint,
            int newPrice, String^ newBusCode, String^ newDriverFio,
            DateTime newDepDate, String^ newDepTime);
        Trip^ FindTrip(String^ route);
        bool StartTrip(String^ route);
        bool CompleteTrip(String^ route);
        bool CancelTrip(String^ route);

        // === онксвемхе дюммшу ===
        System::Collections::Generic::List<Driver^>^ GetAllDrivers();
        System::Collections::Generic::List<Bus^>^ GetAllBuses();
        System::Collections::Generic::List<Trip^>^ GetAllTrips();

        System::Collections::Generic::List<Driver^>^ GetAvailableDrivers();
        System::Collections::Generic::List<Bus^>^ GetAvailableBuses();
        System::Collections::Generic::List<Trip^>^ GetPlannedTrips();
        System::Collections::Generic::List<Trip^>^ GetActiveTrips();

        // === тнплш ===
        void ShowDriversListForm(Form^ owner);
        void ShowAddDriverForm(Form^ owner);
        void ShowDeleteDriverForm(Form^ owner);

        void ShowBusListForm(Form^ owner);
        void ShowAddBusForm(Form^ owner);
        void ShowDeleteBusForm(Form^ owner);

        void ShowTripListForm(Form^ owner);
        void ShowAddTripForm(Form^ owner);
        void ShowDeleteTripForm(Form^ owner);
        void ShowEditTripForm(Form^ owner);

        // === ярюрхярхйю ===
        String^ GetSystemStatistics();
        int GetTotalDrivers();
        int GetTotalBuses();
        int GetTotalTrips();
        int GetActiveTripsCount();
        int GetAvailableBusesCount();
        int GetAvailableDriversCount();

        // === ябниярбю ===
        property DriversList^ DriverSystem {
            DriversList^ get() { return driversList; }
        }

        property BusList^ BusSystem {
            BusList^ get() { return busList; }
        }

        property TripList^ TripSystem {
            TripList^ get() { return tripList; }
        }
    };
}