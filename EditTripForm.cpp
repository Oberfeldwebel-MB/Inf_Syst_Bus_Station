#include "EditTripForm.h"
#include "Search.hpp"
#include "TripValidator.hpp"

using namespace InfSystBusStation;
using namespace System::Windows::Forms;

// Загрузка списка поездок в ComboBox
void EditTripForm::LoadTripComboBox() {
    tripComboBox->Items->Clear();

    if (tripList == nullptr || tripList->Count == 0) {
        tripComboBox->Items->Add("Нет доступных поездок");
        tripComboBox->Enabled = false;
        return;
    }

    int index = 1;
    for each (Trip ^ trip in tripList->AllTrips) {
        // Формируем строку для отображения: "1. Москва → Санкт-Петербург (15.12.2024 10:00)"
        String^ displayText = String::Format("{0}. {1} → {2} ({3:dd.MM.yyyy} {4})",
            index,
            trip->GetStartPoint(),
            trip->GetFinishPoint(),
            trip->GetTripDate(),
            trip->GetTripTime()
        );
        tripComboBox->Items->Add(displayText);
        index++;
    }

    tripComboBox->Enabled = true;
}

// Загрузка информации о выбранной поездке
void EditTripForm::LoadTripInfo() {
    if (currentTrip == nullptr) {
        currentInfoLabel->Text = "Текущая поездка: не выбрана";

        // Очищаем все поля
        startPointBox->Text = "";
        finishPointBox->Text = "";
        depDateBox->Text = "";
        arrDateBox->Text = "";
        priceBox->Text = "";
        driverComboBox->Text = "";
        busComboBox->Text = "";

        // Сбрасываем все чекбоксы
        startPointCheckBox->Checked = false;
        finishPointCheckBox->Checked = false;
        depDateCheckBox->Checked = false;
        arrDateCheckBox->Checked = false;
        priceCheckBox->Checked = false;
        driverCheckBox->Checked = false;
        busCheckBox->Checked = false;

        return;
    }

    // Отображаем текущую информацию
    currentInfoLabel->Text = "Текущая поездка: " + currentTrip->GetRoute();

    // Заполняем поля текущими значениями (только для отображения)
    startPointBox->Text = currentTrip->GetStartPoint();
    finishPointBox->Text = currentTrip->GetFinishPoint();

    // Форматируем дату отправления
    String^ depDateTime = currentTrip->GetTripDate().ToString("dd/MM/yyyy") + " " +
        currentTrip->GetTripTime();
    depDateBox->Text = depDateTime;

    // Дата прибытия (расчетная) - прибавляем 2 часа
    DateTime arrivalDate = currentTrip->GetTripDate().AddHours(2);
    arrDateBox->Text = arrivalDate.ToString("dd/MM/yyyy HH:mm");

    priceBox->Text = currentTrip->GetPrice().ToString();

    // Водитель
    if (currentTrip->GetDriver() != nullptr) {
        driverComboBox->Text = currentTrip->GetDriver()->GetFullName();
    }

    // Автобус
    if (currentTrip->GetBus() != nullptr) {
        String^ busDisplay = String::Format("{0} {1} [{2}]",
            currentTrip->GetBus()->GetBrand(),
            currentTrip->GetBus()->GetModel(),
            currentTrip->GetBus()->GetFormattedCode()
        );
        busComboBox->Text = busDisplay;
    }

    // Сбрасываем все чекбоксы
    startPointCheckBox->Checked = false;
    finishPointCheckBox->Checked = false;
    depDateCheckBox->Checked = false;
    arrDateCheckBox->Checked = false;
    priceCheckBox->Checked = false;
    driverCheckBox->Checked = false;
    busCheckBox->Checked = false;
}

// Загрузка списка водителей в ComboBox
void EditTripForm::LoadDriverComboBox() {
    driverComboBox->Items->Clear();

    if (driverList == nullptr || driverList->Count == 0) {
        driverComboBox->Items->Add("Нет доступных водителей");
        return;
    }

    // Загружаем всех водителей (включая текущего)
    for each (Driver ^ driver in driverList->AllDrivers) {
        driverComboBox->Items->Add(driver->GetFullName());
    }
}

// Загрузка списка автобусов в ComboBox
void EditTripForm::LoadBusComboBox() {
    busComboBox->Items->Clear();

    if (busList == nullptr || busList->Count == 0) {
        busComboBox->Items->Add("Нет доступных автобусов");
        return;
    }

    // Загружаем все автобусы (включая текущий)
    for each (Bus ^ bus in busList->AllBuses) {
        String^ busInfo = String::Format("{0} {1} [{2}]",
            bus->GetBrand(),
            bus->GetModel(),
            bus->GetFormattedCode()
        );
        busComboBox->Items->Add(busInfo);
    }
}

System::Void EditTripForm::btnLoad_Click(System::Object^ sender, System::EventArgs^ e) {
    try {
        // Проверяем, выбрана ли поездка
        if (tripComboBox->SelectedIndex < 0) {
            MessageBox::Show("Выберите поездку из списка!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }

        // Получаем индекс выбранной поездки (0-based)
        int selectedIndex = tripComboBox->SelectedIndex;

        // Проверяем диапазон
        if (selectedIndex < 0 || selectedIndex >= tripList->Count) {
            MessageBox::Show("Выбранная поездка не найдена!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }

        // Получаем поездку
        currentTrip = tripList->AllTrips[selectedIndex];
        tripIndex = selectedIndex;

        // Загружаем информацию
        LoadTripInfo();

        MessageBox::Show("Информация о поездке загружена!", "Успех",
            MessageBoxButtons::OK, MessageBoxIcon::Information);

    }
    catch (Exception^ ex) {
        MessageBox::Show("Ошибка при загрузке информации: " + ex->Message, "Ошибка",
            MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}

System::Void EditTripForm::btnEdit_Click(System::Object^ sender, System::EventArgs^ e) {
    try {
        if (currentTrip == nullptr) {
            MessageBox::Show("Сначала загрузите информацию о поездке!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }

        bool hasChanges = false;
        String^ errorMessage;

        // Проверяем изменения для каждого поля с использованием валидаторов
        if (startPointCheckBox->Checked) {
            String^ newStartPoint = startPointBox->Text->Trim();
            if (String::IsNullOrEmpty(newStartPoint)) {
                MessageBox::Show("Введите пункт отправления!", "Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }

            // Валидация через TripValidator
            if (!TripValidator::ValidateStartPointStatic(newStartPoint, errorMessage)) {
                MessageBox::Show("Ошибка в пункте отправления: " + errorMessage, "Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }

            NewStartPoint = newStartPoint;
            hasChanges = true;
        }

        if (finishPointCheckBox->Checked) {
            String^ newFinishPoint = finishPointBox->Text->Trim();
            if (String::IsNullOrEmpty(newFinishPoint)) {
                MessageBox::Show("Введите пункт прибытия!", "Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }

            // Валидация через TripValidator
            if (!TripValidator::ValidateFinishPointStatic(newFinishPoint, errorMessage)) {
                MessageBox::Show("Ошибка в пункте прибытия: " + errorMessage, "Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }

            NewFinishPoint = newFinishPoint;
            hasChanges = true;
        }

        if (depDateCheckBox->Checked) {
            String^ newDepDate = depDateBox->Text->Trim();
            if (String::IsNullOrEmpty(newDepDate) || newDepDate->Contains("_")) {
                MessageBox::Show("Введите полную дату и время отправления!", "Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }

            // Валидация даты через TripValidator
            if (!TripValidator::ValidateDateStringStatic(newDepDate, errorMessage)) {
                MessageBox::Show("Ошибка в дате отправления: " + errorMessage, "Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }

            NewDepDate = newDepDate;
            hasChanges = true;
        }

        if (arrDateCheckBox->Checked) {
            String^ newArrDate = arrDateBox->Text->Trim();
            if (String::IsNullOrEmpty(newArrDate) || newArrDate->Contains("_")) {
                MessageBox::Show("Введите полную дату и время прибытия!", "Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }

            // Валидация даты через TripValidator
            if (!TripValidator::ValidateDateStringStatic(newArrDate, errorMessage)) {
                MessageBox::Show("Ошибка в дате прибытия: " + errorMessage, "Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }

            NewArrDate = newArrDate;
            hasChanges = true;
        }

        if (priceCheckBox->Checked) {
            String^ priceText = priceBox->Text->Trim();
            if (String::IsNullOrEmpty(priceText)) {
                MessageBox::Show("Введите цену!", "Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }

            int newPrice;
            if (!Int32::TryParse(priceText, newPrice)) {
                MessageBox::Show("Цена должна быть числом!", "Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }

            // Валидация цены через TripValidator
            if (!TripValidator::ValidatePriceStatic(newPrice, errorMessage)) {
                MessageBox::Show("Ошибка в цене: " + errorMessage, "Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }

            NewPrice = newPrice;
            hasChanges = true;
        }

        if (driverCheckBox->Checked) {
            if (driverComboBox->SelectedIndex < 0) {
                MessageBox::Show("Выберите водителя!", "Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }

            String^ driverName = safe_cast<String^>(driverComboBox->SelectedItem);
            Driver^ newDriver = nullptr;

            for each (Driver ^ driver in driverList->AllDrivers) {
                if (driver->GetFullName() == driverName) {
                    newDriver = driver;
                    break;
                }
            }

            if (newDriver == nullptr) {
                MessageBox::Show("Выбранный водитель не найден!", "Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }

            NewDriver = newDriver;
            hasChanges = true;
        }

        if (busCheckBox->Checked) {
            if (busComboBox->SelectedIndex < 0) {
                MessageBox::Show("Выберите автобус!", "Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }

            String^ busInfo = safe_cast<String^>(busComboBox->SelectedItem);
            String^ busCode = "";

            // Извлекаем код автобуса из строки формата "Марка Модель [Код]"
            int startBracket = busInfo->IndexOf('[');
            int endBracket = busInfo->IndexOf(']');
            if (startBracket != -1 && endBracket != -1) {
                busCode = busInfo->Substring(startBracket + 1, endBracket - startBracket - 1);
                // Убираем форматирование слэшами
                busCode = busCode->Replace("/", "");
            }

            // Находим автобус по коду
            Bus^ newBus = nullptr;
            for each (Bus ^ bus in busList->AllBuses) {
                if (bus->GetCode() == busCode) {
                    newBus = bus;
                    break;
                }
            }

            if (newBus == nullptr) {
                MessageBox::Show("Выбранный автобус не найден!", "Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }

            NewBus = newBus;
            hasChanges = true;
        }

        if (!hasChanges) {
            MessageBox::Show("Выберите хотя бы одно поле для изменения!", "Внимание",
                MessageBoxButtons::OK, MessageBoxIcon::Information);
            return;
        }

        // Закрываем форму с результатом OK
        this->DialogResult = System::Windows::Forms::DialogResult::OK;
        this->Close();

    }
    catch (Exception^ ex) {
        MessageBox::Show("Ошибка при сохранении изменений: " + ex->Message, "Ошибка",
            MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}

System::Void EditTripForm::btnCancel_Click(System::Object^ sender, System::EventArgs^ e) {
    this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
    this->Close();
}

// Обработчики CheckBox для активации полей
System::Void EditTripForm::startPointCheckBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
    startPointBox->Enabled = startPointCheckBox->Checked;
}

System::Void EditTripForm::finishPointCheckBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
    finishPointBox->Enabled = finishPointCheckBox->Checked;
}

System::Void EditTripForm::depDateCheckBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
    depDateBox->Enabled = depDateCheckBox->Checked;
}

System::Void EditTripForm::arrDateCheckBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
    arrDateBox->Enabled = arrDateCheckBox->Checked;
}

System::Void EditTripForm::priceCheckBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
    priceBox->Enabled = priceCheckBox->Checked;
}

System::Void EditTripForm::driverCheckBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
    driverComboBox->Enabled = driverCheckBox->Checked;
}

System::Void EditTripForm::busCheckBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
    busComboBox->Enabled = busCheckBox->Checked;
}