#pragma once

#include "People.hpp"

namespace InfSystBusStation {
    ref class Order;

    public ref class User : public People {
    private:
        String^ phoneNumber;
        DateTime registrationDate;
        Order^ currentOrder;

    public:
        // Конструктор - вызывает конструктор People
        User(String^ fullName, String^ gender, String^ passportSeries,
            String^ passportNumber, String^ email, String^ phone);

        ~User();

        // Статический метод создания
        static User^ CreateFromRegistrationForm(
            String^ fullName, String^ gender, String^ passportSeries,
            String^ passportNumber, String^ email, String^ phone);

        // === РЕАЛИЗАЦИЯ АБСТРАКТНОГО МЕТОДА ===
        virtual double CalculateDiscount() override;  // Обязательно!

        // === НОВЫЕ МЕТОДЫ ===
        virtual String^ GetFullInfo() override;  // Переопределяем
        bool ValidateUserData();
        String^ GetShortInfo();

        // === СВОЙСТВА ===
        property String^ PhoneNumber {
            String^ get() { return phoneNumber; }
            void set(String^ value) { phoneNumber = value; }
        }

        property DateTime RegistrationDate {
            DateTime get() { return registrationDate; }
        }

        property Order^ CurrentOrder {
            Order^ get() { return currentOrder; }
            void set(Order^ value) { currentOrder = value; }
        }
    };
}