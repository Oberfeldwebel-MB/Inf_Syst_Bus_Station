// Passenger.h
#pragma once
#include "People.hpp"

namespace InfSystBusStation {

    public ref class Passenger : public People {
    private:
        System::String^ phoneNumber;

    public:
        // Конструктор
        Passenger(System::String^ fullName, System::String^ gender,
            System::String^ passportSeries, System::String^ passportNumber,
            System::String^ email, System::String^ phone);

        // Свойства
        property System::String^ PhoneNumber {
            System::String^ get() { return phoneNumber; }
            void set(System::String^ value) { phoneNumber = value; }
        }

        // Переопределение виртуальных методов
        virtual void PrintInfo() override;
        virtual System::String^ GetFullInfo() override;
        virtual double CalculateDiscount() override;
    };
}