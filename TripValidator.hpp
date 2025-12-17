// TripValidator.h
#pragma once
#include "BaseValidator.hpp"
#include "Trip.hpp"
#include "TripList.hpp"

namespace InfSystBusStation {

    public ref class TripValidator sealed : public BaseValidator {
    public:
        // Обязательные методы
        virtual bool Validate(System::Object^ item) override;
        virtual bool ValidateForAddition(System::Object^ item, System::Object^ container) override;

        // Специфичные методы
        virtual bool ValidateStartPoint(System::String^ startPoint, [System::Runtime::InteropServices::Out] System::String^% errorMessage) override;
        virtual bool ValidateFinishPoint(System::String^ finishPoint, [System::Runtime::InteropServices::Out] System::String^% errorMessage) override;
        virtual bool ValidatePrice(int price, [System::Runtime::InteropServices::Out] System::String^% errorMessage) override;
        virtual bool ValidateDateTime(System::DateTime dateTime, System::String^ time, [System::Runtime::InteropServices::Out] System::String^% errorMessage) override;
        virtual bool ValidateDepartureDate(System::DateTime departureDate, [System::Runtime::InteropServices::Out] System::String^% errorMessage) override;
        virtual bool ValidateTrip(Trip^ trip, [System::Runtime::InteropServices::Out] System::String^% errorMessage) override;

        // Дополнительные методы
        bool CheckDuplicateTrip(TripList^ tripList, System::String^ startPoint,
            System::String^ finishPoint, System::DateTime date, [System::Runtime::InteropServices::Out] System::String^% errorMessage);
        bool CheckBusAvailability(Bus^ bus, TripList^ tripList, System::DateTime date, [System::Runtime::InteropServices::Out] System::String^% errorMessage);
        bool CheckDriverAvailability(Driver^ driver, TripList^ tripList, System::DateTime date, [System::Runtime::InteropServices::Out] System::String^% errorMessage);

        // Статические методы
        static bool ValidateStartPointStatic(System::String^ startPoint, [System::Runtime::InteropServices::Out] System::String^% errorMessage);
        static bool ValidateFinishPointStatic(System::String^ finishPoint, [System::Runtime::InteropServices::Out] System::String^% errorMessage);
        static bool ValidatePriceStatic(int price, [System::Runtime::InteropServices::Out] System::String^% errorMessage);
        static bool ValidateDateTimeStatic(System::DateTime dateTime, System::String^ time, [System::Runtime::InteropServices::Out] System::String^% errorMessage);
        static bool ValidateDepartureDateStatic(System::DateTime departureDate, [System::Runtime::InteropServices::Out] System::String^% errorMessage);
        static bool ValidateTripStatic(Trip^ trip, [System::Runtime::InteropServices::Out] System::String^% errorMessage);
        static bool ValidateNewTripStatic(System::String^ startPoint, System::String^ finishPoint,
            int price, Bus^ bus, Driver^ driver,
            System::DateTime departureDate, System::String^ time,
            TripList^ tripList, [System::Runtime::InteropServices::Out] System::String^% errorMessage);
    };
}