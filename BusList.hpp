#pragma once
#include "Bus.hpp"

namespace InfSystBusStation {

    public ref class BusList {
    private:
        System::Collections::Generic::List<Bus^>^ buses;

    public:
        BusList() {
            buses = gcnew System::Collections::Generic::List<Bus^>();
        }

        ~BusList() {
            buses->Clear();
        }

        // === ОСНОВНЫЕ МЕТОДЫ ===

        // Добавление автобуса
        void AddBus(Bus^ bus) {
            if (bus == nullptr) {
                throw gcnew System::ArgumentNullException("Нельзя добавить пустую ссылку на автобус!");
            }

            // Проверка на уникальность кода
            for each (Bus ^ existingBus in buses) {
                if (existingBus->GetCode() == bus->GetCode()) {
                    throw gcnew System::InvalidOperationException(
                        "Автобус с кодом '" + bus->GetFormattedCode() + "' уже существует!");
                }
            }

            buses->Add(bus);
            System::Console::WriteLine("[BusList] Автобус {0} добавлен в список", bus->GetFormattedCode());
        }

        // Удаление автобуса по коду
        bool RemoveBus(String^ code) {
            for (int i = 0; i < buses->Count; i++) {
                if (buses[i]->GetCode() == code) {
                    buses->RemoveAt(i);
                    System::Console::WriteLine("[BusList] Автобус {0} удален",
                        buses[i]->GetFormattedCode());
                    return true;
                }
            }

            System::Console::WriteLine("[BusList] Автобус с кодом {0} не найден", code);
            return false;
        }

        // Поиск автобуса по коду
        Bus^ FindBusByCode(String^ code) {
            for each (Bus ^ bus in buses) {
                if (bus->GetCode() == code) {
                    return bus;
                }
            }
            return nullptr;
        }

        // Получение доступных автобусов
        System::Collections::Generic::List<Bus^>^ GetAvailableBuses() {
            auto result = gcnew System::Collections::Generic::List<Bus^>();
            for each (Bus ^ bus in buses) {
                if (bus->GetAvailability() && !bus->IsInCriticalCondition()) {
                    result->Add(bus);
                }
            }
            return result;
        }

        // Получение автобусов, требующих ТО
        System::Collections::Generic::List<Bus^>^ GetBusesNeedingMaintenance() {
            auto result = gcnew System::Collections::Generic::List<Bus^>();
            for each (Bus ^ bus in buses) {
                if (bus->NeedsMaintenance() || bus->IsInCriticalCondition()) {
                    result->Add(bus);
                }
            }
            return result;
        }

        // Вывод всех автобусов
        void DisplayAllBuses() {
            System::Console::WriteLine("=== Список автобусов ({0}) ===", buses->Count);

            if (buses->Count == 0) {
                System::Console::WriteLine("Список автобусов пуст");
            }
            else {
                for each (Bus ^ bus in buses) {
                    System::Console::WriteLine("[{0}] {1} {2} ({3} мест) - {4}",
                        bus->GetFormattedCode(),
                        bus->GetBrand(),
                        bus->GetModel(),
                        bus->GetPlaceCount(),
                        bus->GetAvailability() ? "Доступен" : "Не доступен");
                }
            }
            System::Console::WriteLine("==========================");
        }

        // === СВОЙСТВА ===

        property System::Collections::Generic::List<Bus^>^ AllBuses {
            System::Collections::Generic::List<Bus^>^ get() { return buses; }
        }

        property int Count {
            int get() { return buses->Count; }
        }

        property int AvailableCount {
            int get() {
                int count = 0;
                for each (Bus ^ bus in buses) {
                    if (bus->GetAvailability() && !bus->IsInCriticalCondition()) {
                        count++;
                    }
                }
                return count;
            }
        }
    };
}