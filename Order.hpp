#pragma once

#include "Ticket.hpp"        // Должен быть управляемым
#include "TicketChose.hpp"   // Должен быть управляемым
#include "Search.hpp"        // Должен быть управляемым
#include <vector>

namespace InfSystBusStation {

    public ref class Order {
    private:
        System::Collections::Generic::List<Ticket^>^ ticketList;  // Управляемая коллекция
        System::String^ payStatus;
        double totalPrice;
        TicketChose^ ticketchose;      // Управляемый указатель
        Search^ search;                // Управляемый указатель
        System::String^ orderId;
        System::DateTime orderDate;

    public:
        // === КОНСТРУКТОРЫ ===

        // Основной конструктор
        Order(TicketChose^ chose);

        // Конструктор с дополнительными параметрами
        Order(TicketChose^ chose, System::String^ id);

        // Конструктор копирования
        Order(Order^ other);

        // Деструктор
        ~Order();

        // === ОСНОВНЫЕ МЕТОДЫ ===
        void PrintOrderInfo();
        void AddTicket(Ticket^ ticket);
        bool RemoveTicket(Ticket^ ticket);
        void PayOrder();
        void CancelOrder();
        void CalculateTotalPrice();
        void ClearOrder();

        // === ПЕРЕГРУЗКА ОПЕРАТОРОВ ===
        // В C++/CLI перегрузка операторов работает иначе
        // Вместо оператора += используем метод Add
        // Но можно перегрузить если нужно:
        static Order^ operator+(Order^ order, Ticket^ ticket);

        // === СВОЙСТВА ===
        property System::Collections::Generic::List<Ticket^>^ TicketList {
            System::Collections::Generic::List<Ticket^>^ get() { return ticketList; }
        }

        property System::String^ PayStatus {
            System::String^ get() { return payStatus; }
        }

        property double TotalPrice {
            double get() { return totalPrice; }
        }

        property bool IsEmpty {
            bool get() { return ticketList->Count == 0; }
        }

        property System::String^ OrderId {
            System::String^ get() { return orderId; }
        }

        property System::DateTime OrderDate {
            System::DateTime get() { return orderDate; }
        }

        property TicketChose^ TicketChooser {
            TicketChose^ get() { return ticketchose; }
            void set(TicketChose^ value) { ticketchose = value; }
        }

        property Search^ OrderSearch {
            Search^ get() { return search; }
            void set(Search^ value) { search = value; }
        }

        property int TicketCount {
            int get() { return ticketList->Count; }
        }

        // === ВСПОМОГАТЕЛЬНЫЕ МЕТОДЫ ===
        System::String^ GetOrderSummary();
        bool ContainsTicket(Ticket^ ticket);
        double CalculateDiscount();
        void ApplyDiscount(double discountPercent);

        // === СТАТИЧЕСКИЕ МЕТОДЫ ===
        static System::String^ GenerateOrderId();
        static System::String^ GenerateReceipt(Order^ order);
    };
}