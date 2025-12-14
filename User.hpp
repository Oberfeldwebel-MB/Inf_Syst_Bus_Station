#pragma once

#include "People.hpp"
#include "Order.hpp"        // Только если Order действительно нужен
#include "Search.hpp"       // Только если Search нужен в классе

namespace InfSystBusStation {

    public ref class User : public People {
    private:
        Order^ userOrder;         // Управляемый указатель на заказ
        String^ phoneNumber;      // Номер телефона
        DateTime registrationDate; // Дата регистрации
        // УБИРАЕМ Timing^ timing!
        // УБИРАЕМ Search^ search! (если не нужен)

    public:
        // === КОНСТРУКТОРЫ ===

        // Основной конструктор (БЕЗ Timing!)
        User(String^ fullName, String^ gender,
            String^ passportSeries, String^ passportNumber,
            String^ email, String^ phone);

        // Конструктор для формы (ФИО в формате А.А.Рогатин)
        User(String^ surname, String^ name, String^ patronymic,
            String^ gender, String^ passportSeries, String^ passportNumber,
            String^ email, String^ phone);

        // Деструктор
        ~User();

        // === СТАТИЧЕСКИЕ МЕТОДЫ СОЗДАНИЯ ===

        // Создание User из данных формы
        static User^ CreateFromFormData(
            String^ fio,                // В формате "А.А.Рогатин"
            String^ gender,
            String^ passportSeries,
            String^ passportNumber,
            String^ email,
            String^ phone);

        // === ОСНОВНЫЕ МЕТОДЫ ===

        // Работа с заказом (если нужна)
        void CreateOrder(/* параметры заказа */);
        void ViewMyOrder();
        void CancelOrder();

        // === ВИРТУАЛЬНЫЕ МЕТОДЫ ===
        virtual void PrintInfo() override;
        virtual String^ GetFullInfo() override;
        virtual double CalculateDiscount() override;

        // === СВОЙСТВА ===
        property String^ PhoneNumber {
            String^ get() { return phoneNumber; }
            void set(String^ value) { phoneNumber = value; }
        }

        property DateTime RegistrationDate {
            DateTime get() { return registrationDate; }
        }

        property bool HasActiveOrder {
            bool get() { return userOrder != nullptr && !userOrder->IsEmpty(); }
        }

        property Order^ CurrentOrder {
            Order^ get() { return userOrder; }
        }

        // === ВСПОМОГАТЕЛЬНЫЕ МЕТОДЫ ===
        bool ValidateUserData();
        String^ GetShortInfo();
        bool UpdateEmail(String^ newEmail);
        bool UpdatePhone(String^ newPhone);
    };
}