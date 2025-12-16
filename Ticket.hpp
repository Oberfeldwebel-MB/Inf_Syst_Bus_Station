#pragma once
#include "Trip.hpp"
#include "Passenger.hpp"

namespace InfSystBusStation {

    public enum class TicketType {
        ADULT,      // Взрослый
        CHILD,      // Детский  
        LUGGAGE     // Багажный
    };

    public ref class Ticket {
    private:
        int placeNumber;
        Trip^ tripData;
        Passenger^ passengerData;
        bool ticketAvail;
        System::String^ ticketStatus;
        double finalPrice;
        TicketType type;

    public:
        // Конструктор
        Ticket(int placeNumber, Trip^ trip, Passenger^ passenger, TicketType type);

        // Деструктор
        ~Ticket() {}

        void PrintTicketInfo();
        void CalculateFinalPrice();
        void MarkAsPaid() {
            ticketStatus = "Оплачен";
            System::Console::WriteLine("Билет оплачен");
        }

        // Статический метод расчета цены
        static double CalculatePrice(double basePrice, TicketType type) {
            switch (type) {
            case TicketType::ADULT:
                return basePrice * 1.0;
            case TicketType::CHILD:
                return basePrice * 0.5;
            case TicketType::LUGGAGE:
                return basePrice * 0.3;
            default:
                return basePrice;
            }
        }

        // Свойство для имени типа билета
        property System::String^ TicketTypeName {
            System::String^ get() {
                switch (type) {
                case TicketType::ADULT: return "Взрослый";
                case TicketType::CHILD: return "Детский";
                case TicketType::LUGGAGE: return "Багажный";
                default: return "Неизвестный";
                }
            }
        }

        // Геттеры (свойства)
        property int PlaceNumber {
            int get() { return placeNumber; }
        }

        property Trip^ TripData {
            Trip^ get() { return tripData; }
        }

        property Passenger^ PassengerData {
            Passenger^ get() { return passengerData; }
        }

        property TicketType Type {
            TicketType get() { return type; }
        }

        property bool IsAvailable {
            bool get() { return ticketAvail; }
        }

        property System::String^ Status {
            System::String^ get() { return ticketStatus; }
        }

        property double FinalPrice {
            double get() { return finalPrice; }
            void set(double value) { finalPrice = value; }
        }
    };
}