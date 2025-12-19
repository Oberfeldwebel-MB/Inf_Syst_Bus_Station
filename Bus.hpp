#pragma once

using namespace System;

namespace InfSystBusStation {

    public ref class Bus {
    private:
        String^ brand;               // Марка
        String^ model;               // Модель
        int placeCount;              // Количество мест
        bool isAvailable;            // Доступность
        String^ code;                // Код автобуса (формат: А888АА)
        String^ techCondition;       // Техническое состояние
        String^ lastMaintenance;     // Последнее ТО

    public:
        // Конструктор
        Bus(String^ brand, String^ model, int placeCount,
            String^ code, String^ techCondition,
            String^ lastMaintenance)
            : brand(brand), model(model), placeCount(placeCount),
            isAvailable(true), code(code), techCondition(techCondition),
            lastMaintenance(lastMaintenance) {

            if (placeCount <= 0) {
                throw gcnew ArgumentException("Количество мест должно быть больше 0!");
            }
        }

        virtual ~Bus() {}

        // === ГЕТТЕРЫ ===
        String^ GetBrand() { return brand; }
        String^ GetModel() { return model; }
        int GetSeatCount() { return placeCount; }
        bool GetAvailability() { return isAvailable; }
        String^ GetCode() { return code; }
        String^ GetTechCondition() { return techCondition; }
        String^ GetLastMaintenance() { return lastMaintenance; }

        // Форматированный код (А/888/АА)
        String^ GetFormattedCode() {
            if (code->Length == 6) {
                return code->Insert(1, "/")->Insert(5, "/");
            }
            return code;
        }

        String^ GetFullName() {
            return brand + " " + model + " [" + GetFormattedCode() + "]";
        }

        // === СЕТТЕРЫ ===
        void SetBrand(String^ value) { brand = value; }
        void SetModel(String^ value) { model = value; }

        void SetPlaceCount(int value) {
            if (value <= 0) {
                throw gcnew ArgumentException("Количество мест должно быть больше 0!");
            }
            placeCount = value;
        }

        void SetCode(String^ value) { code = value; }
        void SetTechCondition(String^ value) { techCondition = value; }
        void SetLastMaintenance(String^ value) { lastMaintenance = value; }

        // === ОСНОВНЫЕ МЕТОДЫ ===
        bool CheckAvailability();
        void ChangeAvailability(bool state);
        void AssignToTrip();
        void SendToMaintenance(String^ date);
        void ChangeTechCondition(String^ newState);
        void PrintInfo();

    };
}