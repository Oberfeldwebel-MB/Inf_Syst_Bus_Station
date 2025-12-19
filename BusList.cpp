// BusList.cpp
#include "BusList.hpp"
#include "AddBusForm.h"
#include "DeleteBusForm.h"
#include "BusListForm.h"
#include "BusValidator.hpp"
#include "Search.hpp"

using namespace InfSystBusStation;
using namespace System;
using namespace System::Windows::Forms;
using namespace System::Collections::Generic;

// Конструктор
BusList::BusList() {
    buses = gcnew List<Bus^>();
}

// Деструктор
BusList::~BusList() {
    if (buses != nullptr) {
        buses->Clear();
    }
}

// Внутренний поиск автобуса по коду
Bus^ BusList::FindBusByCodeInternal(String^ code) {
    if (buses == nullptr || String::IsNullOrEmpty(code)) {
        return nullptr;
    }

    for each (Bus ^ bus in buses) {
        if (bus->GetCode() == code) {
            return bus;
        }
    }
    return nullptr;
}

// === ОСНОВНЫЕ МЕТОДЫ ДЛЯ ФОРМ ===

// Добавление автобуса
bool BusList::InternalAddBus(String^ brand, String^ model, int placeCount,
    String^ code, String^ techCondition, String^ lastMaintenance) {

    try {
        // Проверка на уникальность кода
        if (FindBusByCodeInternal(code) != nullptr) {
            MessageBox::Show("Автобус с кодом '" + code + "' уже существует!",
                "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return false;
        }

        // Поэлементная валидация ПЕРЕД созданием объекта
        String^ errorMessage;

        if (!BusValidator::ValidateBrandStatic(brand, errorMessage)) {
            MessageBox::Show("Ошибка в марке: " + errorMessage,
                "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return false;
        }

        if (!BusValidator::ValidateModelStatic(model, errorMessage)) {
            MessageBox::Show("Ошибка в модели: " + errorMessage,
                "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return false;
        }

        if (!BusValidator::ValidatePlaceCountStatic(placeCount, errorMessage)) {
            MessageBox::Show("Ошибка в количестве мест: " + errorMessage,
                "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return false;
        }

        if (!BusValidator::ValidateCodeStatic(code, errorMessage)) {
            MessageBox::Show("Ошибка в коде: " + errorMessage,
                "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return false;
        }

        if (!BusValidator::ValidateTechConditionStatic(techCondition, errorMessage)) {
            MessageBox::Show("Ошибка в техническом состоянии: " + errorMessage,
                "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return false;
        }

        if (!BusValidator::ValidateMaintenanceDateStatic(lastMaintenance, errorMessage)) {
            MessageBox::Show("Ошибка в дате ТО: " + errorMessage,
                "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return false;
        }

        // Создание нового автобуса (проверка на placeCount > 0 уже в конструкторе)
        Bus^ newBus = gcnew Bus(brand, model, placeCount, code, techCondition, lastMaintenance);

        // Дополнительная проверка всего объекта
        if (!BusValidator::ValidateBusStatic(newBus, errorMessage)) {
            MessageBox::Show("Ошибка валидации автобуса: " + errorMessage,
                "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return false;
        }

        // Проверка на уникальность в контейнере
        if (!BusValidator::ValidateForAdditionStatic(newBus, this, errorMessage)) {
            MessageBox::Show("Ошибка добавления: " + errorMessage,
                "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return false;
        }

        buses->Add(newBus);

        MessageBox::Show("Автобус успешно добавлен!\n" + newBus->GetFullName(),
            "Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
        return true;
    }
    catch (ArgumentException^ ex) {
        MessageBox::Show("Ошибка при добавлении автобуса: " + ex->Message,
            "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        return false;
    }
    catch (Exception^ ex) {
        MessageBox::Show("Ошибка при добавлении автобуса: " + ex->Message,
            "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        return false;
    }
}

// Удаление автобуса
bool BusList::InternalRemoveBus(String^ code) {
    try {
        if (buses == nullptr || buses->Count == 0) {
            throw gcnew InvalidOperationException("Список автобусов пуст!");
        }

        Bus^ busToRemove = FindBusByCodeInternal(code);
        if (busToRemove == nullptr) {
            throw gcnew ArgumentException("Автобус с кодом '" + code + "' не найден!");
        }

        // Проверяем, не используется ли автобус в поездках
        // (здесь можно добавить проверку, если есть интеграция с TripList)

        return buses->Remove(busToRemove);
    }
    catch (Exception^ ex) {
        MessageBox::Show("Ошибка при удалении автобуса: " + ex->Message,
            "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        return false;
    }
}

// Удаление автобуса по отформатированному коду
bool BusList::RemoveBusByFormattedCode(String^ formattedCode) {
    try {
        // Убираем форматирование для поиска
        String^ code = formattedCode->Replace("/", "");
        return InternalRemoveBus(code);
    }
    catch (Exception^ ex) {
        MessageBox::Show("Ошибка при удалении автобуса: " + ex->Message,
            "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        return false;
    }
}

// Получение всех отформатированных кодов автобусов
List<String^>^ BusList::GetAllBusFormattedCodes() {
    List<String^>^ codes = gcnew List<String^>();
    if (buses != nullptr) {
        for each (Bus ^ bus in buses) {
            codes->Add(bus->GetFormattedCode());
        }
    }
    return codes;
}

// Получение автобуса по отформатированному коду
Bus^ BusList::GetBusByFormattedCode(String^ formattedCode) {
    // Убираем форматирование для поиска
    String^ code = formattedCode->Replace("/", "");
    return FindBusByCodeInternal(code);
}

// Получение детальной информации об автобусе
String^ BusList::GetBusDetailedInfo(String^ formattedCode) {
    Bus^ bus = GetBusByFormattedCode(formattedCode);
    if (bus == nullptr) {
        return "Автобус с кодом '" + formattedCode + "' не найден.";
    }

    return String::Format(
        "Код: {0}\n"
        "Марка: {1}\n"
        "Модель: {2}\n"
        "Количество мест: {3}\n"
        "Техническое состояние: {4}\n"
        "Последнее ТО: {5}\n"
        "Статус: {6}",
        bus->GetFormattedCode(),
        bus->GetBrand(),
        bus->GetModel(),
        bus->GetSeatCount(),
        bus->GetTechCondition(),
        bus->GetLastMaintenance(),
        bus->GetAvailability() ? "Доступен" : "Не доступен"
    );
}

// === МЕТОДЫ ДЛЯ РАБОТЫ С ФОРМАМИ ===

// Показать форму добавления автобуса
bool BusList::ShowAddBusForm(Form^ owner) {
    try {
        // Создаем форму без параметров
        AddBusForm^ form = gcnew AddBusForm();

        // Устанавливаем BusList через метод SetBusList
        form->SetBusList(this);

        if (form->ShowDialog(owner) == DialogResult::OK) {
            return true;
        }
        return false;
    }
    catch (Exception^ ex) {
        MessageBox::Show("Ошибка при открытии формы добавления: " + ex->Message,
            "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        return false;
    }
}

// Показать форму удаления автобуса
bool BusList::ShowDeleteBusForm(Form^ owner) {
    try {
        if (Count == 0) {
            MessageBox::Show("Список автобусов пуст!", "Информация",
                MessageBoxButtons::OK, MessageBoxIcon::Information);
            return false;
        }

        DeleteBusForm^ form = gcnew DeleteBusForm(this);

        if (form->ShowDialog(owner) == DialogResult::OK) {
            return true;
        }
        return false;
    }
    catch (Exception^ ex) {
        MessageBox::Show("Ошибка при открытии формы удаления: " + ex->Message,
            "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        return false;
    }
}

// Показать форму списка автобусов
void BusList::ShowBusListForm(Form^ owner) {
    try {
        BusListForm^ form = gcnew BusListForm(this);
        form->ShowDialog(owner);
    }
    catch (Exception^ ex) {
        MessageBox::Show("Ошибка при открытии списка автобусов: " + ex->Message,
            "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}

// === МЕТОДЫ ПОЛУЧЕНИЯ ДАННЫХ ===

// Получить доступные автобусы
List<Bus^>^ BusList::GetAvailableBuses() {
    List<Bus^>^ result = gcnew List<Bus^>();
    if (buses != nullptr) {
        for each (Bus ^ bus in buses) {
            if (bus->CheckAvailability()) {
                result->Add(bus);
            }
        }
    }
    return result;
}

// Получить автобусы по марке
List<Bus^>^ BusList::GetBusesByBrand(String^ brand) {
    List<Bus^>^ result = gcnew List<Bus^>();
    if (buses != nullptr && !String::IsNullOrEmpty(brand)) {
        for each (Bus ^ bus in buses) {
            if (bus->GetBrand() == brand) {
                result->Add(bus);
            }
        }
    }
    return result;
}

// Вывести все автобусы в консоль
void BusList::DisplayAllBuses() {
    if (buses == nullptr || buses->Count == 0) {
        Console::WriteLine("Список автобусов пуст.");
        return;
    }

    Console::WriteLine("=== Список всех автобусов ({0}) ===", Count);
    int index = 1;
    for each (Bus ^ bus in buses) {
        Console::WriteLine("{0}. {1} - {2} мест, состояние: {3}, статус: {4}",
            index++,
            bus->GetFullName(),
            bus->GetSeatCount(),
            bus->GetTechCondition(),
            bus->GetAvailability() ? "Доступен" : "Не доступен");
    }
    Console::WriteLine("==================================");
}

// Проверить, есть ли доступные автобусы
bool BusList::HasAvailableBuses() {
    if (buses == nullptr) return false;

    for each (Bus ^ bus in buses) {
        if (bus->CheckAvailability()) {
            return true;
        }
    }
    return false;
}

// Получить информацию об автобусе по коду
String^ BusList::GetBusInfo(String^ code) {
    Bus^ bus = FindBusByCodeInternal(code);
    if (bus == nullptr) {
        return "Автобус с кодом '" + code + "' не найден.";
    }

    return GetBusDetailedInfo(bus->GetFormattedCode());
}

// === ДОПОЛНИТЕЛЬНЫЕ МЕТОДЫ ===

// Получить автобусы, доступные для поездки
List<Bus^>^ BusList::GetBusesReadyForTrip() {
    List<Bus^>^ result = gcnew List<Bus^>();
    if (buses != nullptr) {
        for each (Bus ^ bus in buses) {
            if (bus->CheckAvailability()) {
                result->Add(bus);
            }
        }
    }
    return result;
}

// Обновить техническое состояние автобуса
bool BusList::UpdateBusCondition(String^ code, String^ newCondition) {
    try {
        Bus^ bus = FindBusByCodeInternal(code);
        if (bus == nullptr) {
            MessageBox::Show("Автобус с кодом '" + code + "' не найден!",
                "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return false;
        }

        // Используем статический метод с errorMessage
        String^ errorMessage;
        if (!BusValidator::ValidateTechConditionStatic(newCondition, errorMessage)) {
            MessageBox::Show("Ошибка в техническом состоянии: " + errorMessage,
                "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return false;
        }

        bus->ChangeTechCondition(newCondition);
        return true;
    }
    catch (Exception^ ex) {
        MessageBox::Show("Ошибка при обновлении состояния автобуса: " + ex->Message,
            "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        return false;
    }
}


// Обновить дату последнего ТО
bool BusList::UpdateMaintenanceDate(String^ code, String^ newDate) {
    try {
        Bus^ bus = FindBusByCodeInternal(code);
        if (bus == nullptr) {
            MessageBox::Show("Автобус с кодом '" + code + "' не найден!",
                "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return false;
        }

        // Используем статический метод с errorMessage
        String^ errorMessage;
        if (!BusValidator::ValidateMaintenanceDateStatic(newDate, errorMessage)) {
            MessageBox::Show("Ошибка в дате ТО: " + errorMessage,
                "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return false;
        }

        bus->SetLastMaintenance(newDate);
        return true;
    }
    catch (Exception^ ex) {
        MessageBox::Show("Ошибка при обновлении даты ТО: " + ex->Message,
            "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        return false;
    }
}
// Получение всех кодов автобусов (без форматирования)
List<String^>^ BusList::GetAllBusCodes() {
    List<String^>^ result = gcnew List<String^>();

    if (buses != nullptr) {
        for each (Bus ^ bus in buses) {
            if (bus != nullptr) {
                // Получаем отформатированный код и убираем форматирование
                String^ formattedCode = bus->GetFormattedCode();
                String^ code = formattedCode->Replace("/", "");
                result->Add(code);
            }
        }
    }

    return result;
}

