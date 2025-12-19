// Passenger.cpp
#include "Passenger.hpp"

namespace InfSystBusStation {

    Passenger::Passenger(System::String^ fullName, System::String^ gender,
        System::String^ passportSeries, System::String^ passportNumber,
        System::String^ email, System::String^ phone)
        : People(fullName, gender, passportSeries, passportNumber, email),
        phoneNumber(phone) {
    }

    void Passenger::PrintInfo() {
        People::PrintInfo(); // Вызов базового метода
        System::Console::WriteLine("Телефон: {0}", phoneNumber);
    }

    System::String^ Passenger::GetFullInfo() {
        return "Пассажир: " + GetFullName() +
            " | Паспорт: " + GetPassportSeries() + " " + GetPassportNumber() +
            " | Телефон: " + phoneNumber;
    }

    double Passenger::CalculateDiscount() {
        return 0.0; // Базовая скидка
    }
}