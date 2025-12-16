#pragma once

#include "Ticket.hpp"

namespace InfSystBusStation {

    using namespace System;
    using namespace System::Collections::Generic;

    public ref class Order {
    private:
        List<Ticket^>^ tickets;           // Список билетов в заказе
        String^ orderId;
        String^ status;                   // "Создан", "Оплачен", "Отменен"
        double totalPrice;
        DateTime orderDate;
        String^ passengerName;            // Имя пассажира для заказа

    public:
        // === КОНСТРУКТОРЫ ===
        Order();
        Order(String^ passengerName);
        Order(String^ orderId, String^ passengerName);
        ~Order();

        // === ОСНОВНЫЕ МЕТОДЫ УПРАВЛЕНИЯ БИЛЕТАМИ ===
        void AddTicket(Ticket^ ticket);
        bool RemoveTicket(Ticket^ ticket);
        bool RemoveTicketByIndex(int index);
        bool RemoveTicketByPlaceNumber(int placeNumber);
        void Clear();

        // === ПОИСК БИЛЕТОВ В ЗАКАЗЕ ===
        Ticket^ FindTicketByPlaceNumber(int placeNumber);
        Ticket^ FindTicketByPassenger(String^ passengerName);
        List<Ticket^>^ FindTicketsByType(TicketType type);

        // === ОПЕРАЦИИ С ЗАКАЗОМ ===
        bool PayOrder();  // Изменено на bool для проверки успешности
        void CancelOrder();
        void CalculateTotalPrice();
        bool ApplyDiscount(double discountPercent);  // Изменено на bool

        // === ОТОБРАЖЕНИЕ ===
        void PrintOrderInfo();
        String^ GetOrderSummary();
        String^ GetReceipt();
        void DisplayTickets();

        // === СТАТИСТИКА ПО ЗАКАЗУ ===
        int GetTicketCountByType(TicketType type);
        double GetTotalPriceByType(TicketType type);
        Dictionary<TicketType, int>^ GetTicketsStatistics();

        // === ОПЕРАТОРЫ ===
        static Order^ operator+(Order^ order, Ticket^ ticket);
        static Order^ operator-(Order^ order, Ticket^ ticket);

        // === ГЕТТЕРЫ ===
        property List<Ticket^>^ Tickets {
            List<Ticket^>^ get() { return tickets; }
        }

        property String^ OrderId {
            String^ get() { return orderId; }
        }

        property String^ Status {
            String^ get() { return status; }
        }

        property double TotalPrice {
            double get() {
                CalculateTotalPrice(); // Всегда актуальная сумма
                return totalPrice;
            }
        }

        property bool IsEmpty {
            bool get() { return tickets->Count == 0; }
        }

        property DateTime OrderDate {
            DateTime get() { return orderDate; }
        }

        property int TicketCount {
            int get() { return tickets->Count; }
        }

        property String^ PassengerName {
            String^ get() { return passengerName; }
            void set(String^ value) { passengerName = value; }
        }

        // === ПРОВЕРКИ ===
        bool CanBePaid();  // Можно ли оплатить заказ
        bool HasTickets(); // Есть ли билеты в заказе

        // === СТАТИЧЕСКИЕ МЕТОДЫ ===
        static String^ GenerateOrderId();
    };
}