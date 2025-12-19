#pragma once

#include "Bus.hpp"
#include "Driver.hpp"

namespace InfSystBusStation {

    public ref class Trip {
    private:
        System::String^ startPoint;
        System::String^ finishPoint;
        System::String^ status;
        int priceTicket;
        Bus^ bus;
        Driver^ driver;
        System::DateTime tripDate;
        System::String^ tripTime;

        // Управление местами
        System::Collections::Generic::List<int>^ occupiedSeats;   // Занятые места
        System::Collections::Generic::List<int>^ availableSeats;  // Свободные места

        static int totalTrips = 0;

    public:
        // Конструкторы
        Trip(System::String^ start, System::String^ finish, int price, Bus^ bus, Driver^ driver);
        Trip(System::String^ start, System::String^ finish, int price, Bus^ bus, Driver^ driver,
            System::DateTime date, System::String^ time);
        ~Trip();

        // === МЕТОДЫ УПРАВЛЕНИЯ СТАТУСОМ ===
        void StartTrip();
        void CompleteTrip();
        void CancelTrip();

        // === МЕТОДЫ ИЗМЕНЕНИЯ ===
        void ChangeDriver(Driver^ newDriver);
        void ChangeBus(Bus^ newBus);
        void ChangeRoute(System::String^ newStart, System::String^ newFinish);
        void ChangePrice(int newPrice);

        // === МЕТОДЫ ДЛЯ РАБОТЫ С МЕСТАМИ ===
        bool BookSeat(int seatNumber);                     // Забронировать место
        bool CancelSeatBooking(int seatNumber);            // Отменить бронирование
        bool IsSeatAvailable(int seatNumber);              // Проверить свободно ли место
        bool IsSeatOccupied(int seatNumber);               // Проверить занято ли место
        System::Collections::Generic::List<int>^ GetAvailableSeats();  // Получить свободные места
        System::Collections::Generic::List<int>^ GetOccupiedSeats();   // Получить занятые места
        int GetTotalSeatsCount();                          // Всего мест в автобусе
        int GetAvailableSeatsCount();                      // Количество свободных мест
        int GetOccupiedSeatsCount();                       // Количество занятых мест
        void InitializeSeats();                            // Инициализировать места при создании

        // === ПРОВЕРКИ ===
        bool IsAvailableForChanges();
        bool IsCompleted();
        bool IsInProgress();
        bool IsPlanned();
        bool IsCancelled();

        // === ИНФОРМАЦИОННЫЕ МЕТОДЫ ===
        void PrintInfo();
        System::String^ GetFullInfo();
        System::String^ GetShortInfo();
        System::String^ GetSeatsInfo();  // Информация о местах

        // === ГЕТТЕРЫ ===
        System::String^ GetStartPoint() { return startPoint; }
        System::String^ GetFinishPoint() { return finishPoint; }
        System::String^ GetRoute() { return startPoint + " → " + finishPoint; }
        System::String^ GetStatus() { return status; }
        int GetPrice() { return priceTicket; }
        Bus^ GetBus() { return bus; }
        Driver^ GetDriver() { return driver; }
        System::DateTime GetTripDate() { return tripDate; }
        System::String^ GetTripTime() { return tripTime; }

        // === СЕТТЕРЫ ===
        void SetStartPoint(System::String^ value) { startPoint = value; }
        void SetFinishPoint(System::String^ value) { finishPoint = value; }
        void SetPrice(int value) {
            if (value > 0) priceTicket = value;
        }
        void SetBus(Bus^ value) {
            bus = value;
            // При смене автобуса переинициализируем места
            if (bus != nullptr && IsPlanned()) {
                InitializeSeats();
            }
        }
        void SetDriver(Driver^ value) { driver = value; }
        void SetTripDate(System::DateTime value) { tripDate = value; }
        void SetTripTime(System::String^ value) { tripTime = value; }

        // === СТАТИЧЕСКИЕ МЕТОДЫ ===
        static property int TotalTrips {
            int get() { return totalTrips; }
        }

        static System::String^ GetStatusDescription(System::String^ status);

        // === СВОЙСТВА ===
        property System::String^ Route {
            System::String^ get() { return GetRoute(); }
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

        // СВОЙСТВА ДЛЯ МЕСТ
        property int AvailableSeats {
            int get() { return GetAvailableSeatsCount(); }
        }

        property int OccupiedSeats {
            int get() { return GetOccupiedSeatsCount(); }
        }

        property int TotalSeats {
            int get() { return GetTotalSeatsCount(); }
        }
    };
}