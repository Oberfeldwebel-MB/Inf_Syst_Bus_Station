// Trip.hpp
#pragma once

#include "Bus.hpp"
#include "Driver.hpp"

namespace InfSystBusStation {

    public ref class Trip {
    private:
        String^ startPoint;
        String^ finishPoint;
        String^ status;
        int priceTicket;
        Bus^ bus;
        Driver^ driver;
        DateTime tripDate;
        String^ tripTime;

        static int totalTrips = 0;

    public:
        // Конструкторы
        Trip(String^ start, String^ finish, int price, Bus^ bus, Driver^ driver);
        Trip(String^ start, String^ finish, int price, Bus^ bus, Driver^ driver,
            DateTime date, String^ time);
        ~Trip();

        // === МЕТОДЫ УПРАВЛЕНИЯ СТАТУСОМ ===
        void StartTrip();
        void CompleteTrip();
        void CancelTrip();

        // === МЕТОДЫ ИЗМЕНЕНИЯ ===
        void ChangeDriver(Driver^ newDriver);
        void ChangeBus(Bus^ newBus);
        void ChangeRoute(String^ newStart, String^ newFinish);
        void ChangePrice(int newPrice);

        // === ПРОВЕРКИ ===
        bool IsAvailableForChanges();
        bool IsCompleted();
        bool IsInProgress();
        bool IsPlanned();
        bool IsCancelled();

        // === ИНФОРМАЦИОННЫЕ МЕТОДЫ ===
        void PrintInfo();
        String^ GetFullInfo();
        String^ GetShortInfo();

        // === ГЕТТЕРЫ ===
        String^ GetStartPoint() { return startPoint; }
        String^ GetFinishPoint() { return finishPoint; }
        String^ GetRoute() { return startPoint + " → " + finishPoint; }
        String^ GetStatus() { return status; }
        int GetPrice() { return priceTicket; }
        Bus^ GetBus() { return bus; }
        Driver^ GetDriver() { return driver; }
        DateTime GetTripDate() { return tripDate; }
        String^ GetTripTime() { return tripTime; }

        // === СЕТТЕРЫ ===
        void SetStartPoint(String^ value) { startPoint = value; }
        void SetFinishPoint(String^ value) { finishPoint = value; }
        void SetPrice(int value) {
            if (value > 0) priceTicket = value;
        }
        void SetBus(Bus^ value) { bus = value; }
        void SetDriver(Driver^ value) { driver = value; }
        void SetTripDate(DateTime value) { tripDate = value; }
        void SetTripTime(String^ value) { tripTime = value; }

        // === СТАТИЧЕСКИЕ МЕТОДЫ ===
        static property int TotalTrips {
            int get() { return totalTrips; }
        }

        static String^ GetStatusDescription(String^ status);

        // === СВОЙСТВА ===
        property String^ Route {
            String^ get() { return GetRoute(); }
        }

        property bool CanBeStarted {
            bool get() { return IsPlanned(); }
        }

        property bool CanBeCompleted {
            bool get() { return IsInProgress(); }
        }

        property bool CanBeCancelled {
            bool get() { return IsPlanned() || IsInProgress(); }
        }
    };
}