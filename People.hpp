// People.h (управляемый)
#pragma once

using namespace System;

namespace InfSystBusStation {

    public ref class People abstract {
    protected:
        String^ fullName;          // Полное ФИО (например: "Иванов И.И.")
        String^ gender;            // Пол
        String^ passportSeries;    // Серия паспорта
        String^ passportNumber;    // Номер паспорта
        String^ email;             // Email

    public:
        // Конструктор
        People(String^ fullName, String^ gender,
            String^ passportSeries, String^ passportNumber,
            String^ email)
            : fullName(fullName), gender(gender),
            passportSeries(passportSeries),
            passportNumber(passportNumber),
            email(email) {
        }

        virtual ~People() {}

        // === ТРАДИЦИОННЫЕ ГЕТТЕРЫ И СЕТТЕРЫ ===

        // ФИО
        String^ GetFullName() { return fullName; }
        void SetFullName(String^ value) { fullName = value; }

        // Паспортные данные
        String^ GetPassportSeries() { return passportSeries; }
        void SetPassportSeries(String^ value) { passportSeries = value; }

        String^ GetPassportNumber() { return passportNumber; }
        void SetPassportNumber(String^ value) { passportNumber = value; }

        void SetPassport(String^ series, String^ number) {
            passportSeries = series;
            passportNumber = number;
        }

        // Пол
        String^ GetGender() { return gender; }
        void SetGender(String^ value) { gender = value; }

        // Email
        String^ GetEmail() { return email; }
        void SetEmail(String^ value) { email = value; }

        // === ВИРТУАЛЬНЫЕ МЕТОДЫ ===
        virtual void PrintInfo();
        virtual String^ GetFullInfo();
        virtual double CalculateDiscount() abstract;
    };
}