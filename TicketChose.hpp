#pragma once

#include "Trip.hpp"
#include "Order.hpp"
#include <vector>

namespace InfSystBusStation {

    public ref class TicketChose {
    private:
        Trip^ selectedTrip;           // Выбранная поездка
        Order^ currentOrder;         // Текущий заказ пользователя
        List<int>^ availableSeats;   // Свободные места
        List<int>^ selectedSeats;    // Выбранные пользователем места
        int totalSeats;              // Всего мест в автобусе

    public:
        // Конструктор
        TicketChose(Trip^ trip, Order^ order);

        // === МЕТОДЫ УПРАВЛЕНИЯ МЕСТАМИ ===
        void LoadAvailableSeats();                     // Загрузить свободные места
        bool IsSeatAvailable(int seatNumber);         // Проверить свободно ли место
        bool SelectSeat(int seatNumber);              // Выбрать место
        bool DeselectSeat(int seatNumber);            // Отменить выбор места
        void ClearSelection();                        // Очистить выбор

        // === РАБОТА С БИЛЕТАМИ ===
        bool AddSelectedTicketsToOrder();             // Добавить выбранные билеты в заказ
        bool RemoveTicketFromOrder(int seatNumber);   // Удалить билет из заказа
        void ReturnSeatToAvailable(int seatNumber);   // Вернуть место в доступные

        // === ИНФОРМАЦИОННЫЕ МЕТОДЫ ===
        String^ GetTripInfo();                        // Получить инфо о поездке
        List<int>^ GetAvailableSeats();               // Получить список свободных мест
        List<int>^ GetSelectedSeats();                // Получить выбранные места
        int GetSelectedSeatsCount();                  // Количество выбранных мест
        Decimal GetTotalPrice();                      // Общая стоимость выбранных мест

        // === ПРОВЕРКИ ===
        bool HasAvailableSeats();                     // Есть ли свободные места
        bool HasSelectedSeats();                      // Выбраны ли места
        bool CanAddToOrder();                         // Можно ли добавить в заказ

        // === СВОЙСТВА ===
        property Trip^ SelectedTrip {
            Trip^ get() { return selectedTrip; }
        }

        property Order^ CurrentOrder {
            Order^ get() { return currentOrder; }
            void set(Order^ value) { currentOrder = value; }
        }

        property int TotalSeats {
            int get() { return totalSeats; }
        }

        property int AvailableSeatsCount {
            int get() { return availableSeats->Count; }
        }

        property Decimal TotalSelectedPrice {
            Decimal get() { return GetTotalPrice(); }
        }
    };
}