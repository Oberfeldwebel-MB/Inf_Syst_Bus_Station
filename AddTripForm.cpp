#include "AddTripForm.h"

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

// Вспомогательная функция для поиска автобуса по коду
Bus^ FindBusByCode(BusList^ busList, String^ code) {
    if (busList == nullptr || String::IsNullOrEmpty(code)) {
        return nullptr;
    }

    for each (Bus ^ bus in busList->AllBuses) {
        if (bus->GetCode() == code) {
            return bus;
        }
    }
    return nullptr;
}

// Вспомогательная функция для поиска водителя по имени
Driver^ FindDriverByName(DriversList^ driverList, String^ name) {
    if (driverList == nullptr || String::IsNullOrEmpty(name)) {
        return nullptr;
    }

    for each (Driver ^ driver in driverList->AllDrivers) {
        if (driver->GetFullName() == name) {
            return driver;
        }
    }
    return nullptr;
}

System::Void AddTripForm::add_button_Click(System::Object^ sender, System::EventArgs^ e) {
    try {
        // === 1. Проверка инициализации ===
        if (tripList == nullptr) {
            MessageBox::Show("Ошибка: список поездок не инициализирован!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        if (busList == nullptr || driverList == nullptr) {
            MessageBox::Show("Ошибка: списки автобусов или водителей не инициализированы!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        // === 2. Получение данных из формы ===

        // Пункт отправления
        String^ startPoint = StartPointBox->Text->Trim();
        if (String::IsNullOrEmpty(startPoint)) {
            MessageBox::Show("Введите пункт отправления!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            StartPointBox->Focus();
            StartPointBox->SelectAll();
            return;
        }

        // Пункт прибытия
        String^ finishPoint = FinishPointBox->Text->Trim();
        if (String::IsNullOrEmpty(finishPoint)) {
            MessageBox::Show("Введите пункт прибытия!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            FinishPointBox->Focus();
            FinishPointBox->SelectAll();
            return;
        }

        // Дата и время отправления
        String^ depDateStr = DepDateBox->Text->Trim();
        if (String::IsNullOrEmpty(depDateStr) || depDateStr->Contains("_")) {
            MessageBox::Show("Введите полную дату и время отправления!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            DepDateBox->Focus();
            DepDateBox->SelectAll();
            return;
        }

        // Дата и время прибытия
        String^ arrDateStr = ArrDateBox->Text->Trim();
        if (String::IsNullOrEmpty(arrDateStr) || arrDateStr->Contains("_")) {
            MessageBox::Show("Введите полную дату и время прибытия!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            ArrDateBox->Focus();
            ArrDateBox->SelectAll();
            return;
        }

        // Цена
        if (String::IsNullOrEmpty(PriceBox->Text)) {
            MessageBox::Show("Введите цену билета!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            PriceBox->Focus();
            PriceBox->SelectAll();
            return;
        }

        int price;
        try {
            price = Int32::Parse(PriceBox->Text);
            if (price <= 0) {
                MessageBox::Show("Цена должна быть больше 0!", "Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Warning);
                PriceBox->Focus();
                PriceBox->SelectAll();
                return;
            }
        }
        catch (Exception^) {
            MessageBox::Show("Цена должна быть целым числом!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            PriceBox->Focus();
            PriceBox->SelectAll();
            return;
        }

        // Водитель
        if (driverComboBox->SelectedIndex < 0) {
            MessageBox::Show("Выберите водителя!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            driverComboBox->Focus();
            return;
        }

        String^ selectedDriverName = safe_cast<String^>(driverComboBox->SelectedItem);
        if (selectedDriverName == "Нет доступных водителей" ||
            selectedDriverName == "Список водителей не загружен") {
            MessageBox::Show("Нет доступных водителей!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }

        // Поиск водителя по имени
        Driver^ selectedDriver = FindDriverByName(driverList, selectedDriverName);
        if (selectedDriver == nullptr) {
            MessageBox::Show("Водитель не найден!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }

        if (!selectedDriver->IsAvailable()) {
            MessageBox::Show("Выбранный водитель недоступен!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }

        // Автобус
        if (busComboBox->SelectedIndex < 0) {
            MessageBox::Show("Выберите автобус!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            busComboBox->Focus();
            return;
        }

        String^ selectedBusInfo = safe_cast<String^>(busComboBox->SelectedItem);
        if (selectedBusInfo == "Нет доступных автобусов" ||
            selectedBusInfo == "Список автобусов не загружен") {
            MessageBox::Show("Нет доступных автобусов!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }

        // Извлекаем код автобуса из строки
        String^ busCode = ExtractBusCodeFromInfo(selectedBusInfo);
        if (String::IsNullOrEmpty(busCode)) {
            MessageBox::Show("Не удалось определить код автобуса!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }

        // Поиск автобуса по коду
        Bus^ selectedBus = FindBusByCode(busList, busCode);
        if (selectedBus == nullptr) {
            MessageBox::Show("Автобус не найден!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }

        if (!selectedBus->CheckAvailability()) {
            MessageBox::Show("Выбранный автобус недоступен!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }

        // === 3. Проверка дат ===
        DateTime depDate;
        DateTime arrDate;

        try {
            // Парсим даты (формат: "dd/MM/yyyy HH:mm")
            depDate = DateTime::ParseExact(depDateStr, "dd/MM/yyyy HH:mm", nullptr);
            arrDate = DateTime::ParseExact(arrDateStr, "dd/MM/yyyy HH:mm", nullptr);

            if (arrDate <= depDate) {
                MessageBox::Show("Дата прибытия должна быть позже даты отправления!", "Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Warning);
                ArrDateBox->Focus();
                ArrDateBox->SelectAll();
                return;
            }
        }
        catch (Exception^) {
            MessageBox::Show("Неверный формат даты! Используйте формат: ДД/ММ/ГГГГ ЧЧ:ММ", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            DepDateBox->Focus();
            DepDateBox->SelectAll();
            return;
        }

        // === 4. Вызов метода TripList для добавления ===
        // Извлекаем время из строки даты (последние 5 символов "HH:mm")
        String^ departureTime = depDateStr->Substring(11, 5);

        // Используем InternalAddTrip из TripList
        if (tripList->InternalAddTrip(startPoint, finishPoint, price,
            selectedBus, selectedDriver, depDate, departureTime)) {

            // Успешно добавлено
            MessageBox::Show("Поездка успешно добавлена в расписание!", "Успех",
                MessageBoxButtons::OK, MessageBoxIcon::Information);

            // Очистка формы
            StartPointBox->Clear();
            FinishPointBox->Clear();
            DepDateBox->Clear();
            ArrDateBox->Clear();
            PriceBox->Clear();
            driverComboBox->SelectedIndex = -1;
            busComboBox->SelectedIndex = -1;
            StartPointBox->Focus();

            // Обновление списков (на случай если изменилась доступность)
            LoadDriverComboBox();
            LoadBusComboBox();

            // Генерация события
            if (DataAdded != nullptr) {
                DataAdded(this, EventArgs::Empty);
            }

            // Закрываем форму с результатом OK
            this->DialogResult = System::Windows::Forms::DialogResult::OK;
            this->Close();
        }
    }
    catch (Exception^ ex) {
        MessageBox::Show("Ошибка при добавлении поездки: " + ex->Message, "Ошибка системы",
            MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}