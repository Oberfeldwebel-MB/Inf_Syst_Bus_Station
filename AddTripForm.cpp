#include "AddTripForm.h"
#include "TripValidator.hpp"

using namespace InfSystBusStation;
using namespace System;
using namespace System::Windows::Forms;

// Загрузка списка водителей в ComboBox
void AddTripForm::LoadDriverComboBox() {
    driverComboBox->Items->Clear();

    if (driverList == nullptr) {
        driverComboBox->Enabled = false;
        driverComboBox->Items->Add("Список водителей не загружен");
        return;
    }

    // Получаем доступных водителей
    bool hasAvailableDrivers = false;

    for each (Driver ^ driver in driverList->AllDrivers) {
        if (driver->IsAvailable()) {  // Используем IsAvailable()
            driverComboBox->Items->Add(driver->GetFullName());
            hasAvailableDrivers = true;
        }
    }

    if (hasAvailableDrivers) {
        driverComboBox->SelectedIndex = 0;
        driverComboBox->Enabled = true;
    }
    else {
        driverComboBox->Items->Add("Нет доступных водителей");
        driverComboBox->SelectedIndex = 0;
        driverComboBox->Enabled = false;
    }
}

// Загрузка списка автобусов в ComboBox
void AddTripForm::LoadBusComboBox() {
    busComboBox->Items->Clear();

    if (busList == nullptr) {
        busComboBox->Enabled = false;
        busComboBox->Items->Add("Список автобусов не загружен");
        return;
    }

    // Загружаем только доступные автобусы
    bool hasAvailableBuses = false;

    for each (Bus ^ bus in busList->AllBuses) {
        if (bus->CheckAvailability()) {  // Используем CheckAvailability()
            String^ busInfo = String::Format("{0} {1} [{2}]",
                bus->GetBrand(),
                bus->GetModel(),
                bus->GetFormattedCode());
            busComboBox->Items->Add(busInfo);
            hasAvailableBuses = true;
        }
    }

    if (hasAvailableBuses) {
        busComboBox->SelectedIndex = 0;
        busComboBox->Enabled = true;
    }
    else {
        busComboBox->Items->Add("Нет доступных автобусов");
        busComboBox->SelectedIndex = 0;
        busComboBox->Enabled = false;
    }
}

// Вспомогательная функция для извлечения кода автобуса из строки
String^ ExtractBusCodeFromInfo(String^ busInfo) {
    int startBracket = busInfo->IndexOf('[');
    int endBracket = busInfo->IndexOf(']');

    if (startBracket != -1 && endBracket != -1 && endBracket > startBracket) {
        return busInfo->Substring(startBracket + 1, endBracket - startBracket - 1);
    }

    return String::Empty;
}

System::Void AddTripForm::add_button_Click(System::Object^ sender, System::EventArgs^ e) {
    try {
        // === 1. Быстрая проверка инициализации ===
        if (tripList == nullptr || busList == nullptr || driverList == nullptr) {
            MessageBox::Show("Ошибка: данные не загружены!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        // === 2. Получение данных из формы ===
        String^ startPoint = StartPointBox->Text->Trim();
        String^ finishPoint = FinishPointBox->Text->Trim();
        String^ depDateStr = DepDateBox->Text->Trim();
        String^ arrDateStr = ArrDateBox->Text->Trim();
        String^ priceStr = PriceBox->Text->Trim();

        // Проверка на пустые поля
        if (String::IsNullOrEmpty(startPoint) || String::IsNullOrEmpty(finishPoint) ||
            String::IsNullOrEmpty(depDateStr) || String::IsNullOrEmpty(arrDateStr) ||
            String::IsNullOrEmpty(priceStr)) {
            MessageBox::Show("Заполните все поля!", "Внимание",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }

        // === 3. Парсинг дат и цены ===
        DateTime depDate, arrDate;
        int price;

        try {
            depDate = DateTime::ParseExact(depDateStr, "dd/MM/yyyy HH:mm", nullptr);
            arrDate = DateTime::ParseExact(arrDateStr, "dd/MM/yyyy HH:mm", nullptr);
            price = Int32::Parse(priceStr);
        }
        catch (Exception^) {
            MessageBox::Show("Неверный формат данных!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }

        // Проверка времени прибытия
        if (arrDate <= depDate) {
            MessageBox::Show("Время прибытия должно быть позже отправления!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }

        // === 4. Получение выбранных автобуса и водителя ===
        if (driverComboBox->SelectedIndex < 0 || busComboBox->SelectedIndex < 0) {
            MessageBox::Show("Выберите автобус и водителя!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }

        String^ selectedDriverName = safe_cast<String^>(driverComboBox->SelectedItem);
        String^ selectedBusInfo = safe_cast<String^>(busComboBox->SelectedItem);

        // Быстрая проверка на доступность
        if (selectedDriverName->Contains("не доступ") || selectedBusInfo->Contains("не доступ")) {
            MessageBox::Show("Нет доступных ресурсов!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }

        Driver^ selectedDriver = Search::FindDriverByName(driverList, selectedDriverName);
        String^ busCode = ExtractBusCodeFromInfo(selectedBusInfo);
        Bus^ selectedBus = Search::FindBusByCode(busList, busCode);

        if (selectedDriver == nullptr || selectedBus == nullptr) {
            MessageBox::Show("Ошибка при выборе ресурсов!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        // === 5. ВАЛИДАЦИЯ (ОСНОВНОЙ ВЫЗОВ) ===
        String^ validationError;
        bool isValid = TripValidator::ValidateNewTripStatic(
            startPoint,
            finishPoint,
            price,
            selectedBus,
            selectedDriver,
            depDate,
            depDateStr->Substring(11, 5),  // Время отправления
            tripList,
            validationError
        );

        if (!isValid) {
            MessageBox::Show(validationError, "Ошибка валидации",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }

        // === 6. Добавление поездки ===
        if (tripList->InternalAddTrip(startPoint, finishPoint, price,
            selectedBus, selectedDriver, depDate, depDateStr->Substring(11, 5))) {

            MessageBox::Show("Поездка успешно добавлена!", "Успех",
                MessageBoxButtons::OK, MessageBoxIcon::Information);

            // Очистка и обновление
            ClearForm();
            LoadDriverComboBox();
            LoadBusComboBox();

            DataAdded(this, EventArgs::Empty);
            this->DialogResult = System::Windows::Forms::DialogResult::OK;
            this->Close();
        }
    }
    catch (Exception^ ex) {
        MessageBox::Show("Ошибка: " + ex->Message, "Ошибка системы",
            MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}

// Новый метод для очистки формы
void AddTripForm::ClearForm() {
    StartPointBox->Clear();
    FinishPointBox->Clear();
    DepDateBox->Clear();
    ArrDateBox->Clear();
    PriceBox->Clear();
    driverComboBox->SelectedIndex = -1;
    busComboBox->SelectedIndex = -1;
    StartPointBox->Focus();
}