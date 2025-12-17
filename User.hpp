#pragma once

#include "People.hpp"
#include "Order.hpp"  
#include "Ticket.hpp" 

namespace InfSystBusStation {

    public ref class User : public People {
    private:
        String^ phoneNumber;           // Номер телефона
        Order^ shoppingCart;           // Корзина покупок (единственный Order)
        DateTime registrationDate;     // Дата регистрации
        bool isRegistered;             // Зарегистрирован в системе

    public:
        // === КОНСТРУКТОРЫ ===

        // Основной конструктор со ВСЕМИ параметрами
        User(String^ fioFormatted, String^ gender, String^ passportSeries,
            String^ passportNumber, String^ email, String^ phone);

        // Деструктор
        ~User();

        // === СТАТИЧЕСКИЕ МЕТОДЫ ===
        static User^ CreateFromRegistrationForm(
            String^ fioFormatted,      // В формате "А.А.Рогатин"
            String^ gender,            // "М" или "Ж"
            String^ passportSeries,    // "1234"
            String^ passportNumber,    // "567890"
            String^ email,             // email@example.com
            String^ phone);            // +71234567890

        // === РАБОТА С КОРЗИНОЙ (Order) ===
        void AddTicketToCart(Ticket^ ticket);
        void RemoveTicketFromCart(Ticket^ ticket);
        void RemoveTicketFromCart(int placeNumber);
        void ClearCart();
        void CheckoutCart();           // Оформление покупки
        bool HasTicketsInCart();

        // === ИНФОРМАЦИЯ О КОРЗИНЕ ===
        String^ GetCartSummary();
        int GetCartTicketCount();
        double GetCartTotalPrice();
        List<Ticket^>^ GetCartTickets();

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

        property bool IsRegistered {
            bool get() { return isRegistered; }
            void set(bool value) { isRegistered = value; }
        }

        property bool HasItemsInCart {
            bool get() {
                return shoppingCart != nullptr &&
                    !shoppingCart->IsEmpty;
            }
        }

        property Order^ ShoppingCart {
            Order^ get() {
                if (shoppingCart == nullptr) {
                    shoppingCart = gcnew Order();
                }
                return shoppingCart;
            }
        }

        // === ВСПОМОГАТЕЛЬНЫЕ МЕТОДЫ ===
        bool ValidateUserData();
        String^ GetShortInfo();
    };
}