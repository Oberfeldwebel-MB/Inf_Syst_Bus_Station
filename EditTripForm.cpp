// EditTripForm.cpp
#include "EditTripForm.h"

using namespace InfSystBusStation;
using namespace System::Windows::Forms;

// Загрузка информации о выбранной поездке
void EditTripForm::LoadTripInfo() {
    if (currentTrip == nullptr) {
        currentInfoLabel->Text = "Текущая поездка: не выбрана";
        return;
    }

    // Отображаем текущую информацию
    currentInfoLabel->Text = "Текущая поездка: " + currentTrip->GetRoute();

    // Заполняем поля текущими значениями (только для отображения)
    startPointBox->Text = currentTrip->GetStartPoint();
    finishPointBox->Text = currentTrip->GetFinishPoint();
    depDateBox->Text = currentTrip->GetTripDate().ToString("dd/MM/yyyy ") + currentTrip->GetTripTime();

    // Дата прибытия (расчетная)
    DateTime arrivalDate = currentTrip->GetTripDate().AddHours(2);
    arrDateBox->Text = arrivalDate.ToString("dd/MM/yyyy HH:mm");

    priceBox->Text = currentTrip->GetPrice().ToString();

    // Водитель
    if (currentTrip->GetDriver() != nullptr) {
        driverComboBox->Text = currentTrip->GetDriver()->GetFullName();
    }

    // Автобус
    if (currentTrip->GetBus() != nullptr) {
        busComboBox->Text = currentTrip->GetBus()->GetBrand() + " " +
            currentTrip->GetBus()->GetModel() +
            " [" + currentTrip->GetBus()->GetFormattedCode() + "]";
    }
}

// Загрузка списка водителей в ComboBox
void EditTripForm::LoadDriverComboBox() {
    driverComboBox->Items->Clear();

    if (driverList == nullptr || driverList->Count == 0) {
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
        return;
    }

    // Загружаем все автобусы (включая текущий)
    for each (Bus ^ bus in busList->AllBuses) {
        String^ busInfo = String::Format("{0} {1} [{2}]",
            bus->GetBrand(),
            bus->GetModel(),
            bus->GetFormattedCode());
        busComboBox->Items->Add(busInfo);
    }
}

System::Void EditTripForm::btnLoad_Click(System::Object^ sender, System::EventArgs^ e) {
    try {
        // Получаем номер поездки
        if (String::IsNullOrEmpty(tripIndexBox->Text)) {
            MessageBox::Show("Введите номер поездки!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }

        int index;
        if (!Int32::TryParse(tripIndexBox->Text, index)) {
            MessageBox::Show("Номер поездки должен быть числом!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }

        // Проверяем диапазон
        if (index < 1 || index > tripList->Count) {
            MessageBox::Show("Поездка с таким номером не найдена!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }

        // Получаем поездку
        currentTrip = tripList->AllTrips[index - 1];

        // Загружаем информацию
        LoadTripInfo();
        LoadDriverComboBox();
        LoadBusComboBox();

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

        // Проверяем изменения для каждого поля
        if (startPointCheckBox->Checked) {
            String^ newStartPoint = startPointBox->Text->Trim();
            if (String::IsNullOrEmpty(newStartPoint)) {
                MessageBox::Show("Введите пункт отправления!", "Ошибка",
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
            if (!Int32::TryParse(priceText, newPrice) || newPrice <= 0) {
                MessageBox::Show("Цена должна быть положительным числом!", "Ошибка",
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

            // Извлекаем код автобуса
            int startBracket = busInfo->IndexOf('[');
            int endBracket = busInfo->IndexOf(']');
            if (startBracket != -1 && endBracket != -1) {
                busCode = busInfo->Substring(startBracket + 1, endBracket - startBracket - 1);
            }

            Bus^ newBus = busList->FindBusByCode(busCode);
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

        // Сохраняем индекс
        tripIndex = Int32::Parse(tripIndexBox->Text) - 1;

        // Закрываем форму с результатом OK
        this->DialogResult = DialogResult::OK;
        this->Close();

    }
    catch (Exception^ ex) {
        MessageBox::Show("Ошибка при сохранении изменений: " + ex->Message, "Ошибка",
            MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}

System::Void EditTripForm::btnCancel_Click(System::Object^ sender, System::EventArgs^ e) {
    this->DialogResult = DialogResult::Cancel;
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