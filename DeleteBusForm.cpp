// DeleteBusForm.cpp
#include "DeleteBusForm.h"

using namespace InfSystBusStation;
using namespace System::Windows::Forms;

// Загрузка кодов автобусов в ComboBox
void DeleteBusForm::LoadBusCodes() {
    busComboBox->Items->Clear();

    if (busList == nullptr || busList->Count == 0) {
        busComboBox->Enabled = false;
        deleteButton->Enabled = false;
        infoLabel->Text = "Список автобусов пуст!";
        infoLabel->ForeColor = Drawing::Color::DarkRed;
        return;
    }

    // Получаем все коды автобусов
    auto busCodes = busList->GetAllBusCodes();
    for each (String ^ code in busCodes) {
        busComboBox->Items->Add(code);
    }

    if (busComboBox->Items->Count > 0) {
        busComboBox->SelectedIndex = 0;
    }
}

// Обновление информации о выбранном автобусе
void DeleteBusForm::UpdateBusInfo(Bus^ bus) {
    if (bus == nullptr) {
        brandLabel->Text = "Марка: не указано";
        modelLabel->Text = "Модель: не указано";
        placesLabel->Text = "Количество мест: не указано";
        conditionLabel->Text = "Техническое состояние: не указано";
        maintenanceLabel->Text = "Последнее ТО: не указано";
        statusLabel->Text = "Статус: не указано";
        return;
    }

    // Заполняем информацию
    brandLabel->Text = "Марка: " + bus->GetBrand();
    modelLabel->Text = "Модель: " + bus->GetModel();
    placesLabel->Text = "Количество мест: " + bus->GetPlaceCount().ToString();
    conditionLabel->Text = "Техническое состояние: " + bus->GetTechCondition();

    // Дата ТО
    String^ maintenanceText = "Последнее ТО: ";
    if (!String::IsNullOrEmpty(bus->GetLastMaintenance())) {
        maintenanceText += bus->GetLastMaintenance();
    }
    else {
        maintenanceText += "не указано";
    }
    maintenanceLabel->Text = maintenanceText;

    // Статус
    String^ statusText = "Статус: ";
    if (bus->GetAvailability() && !bus->IsInCriticalCondition()) {
        statusText += "Доступен";
    }
    else if (bus->IsInCriticalCondition()) {
        statusText += "Требует ремонта";
    }
    else {
        statusText += "Не доступен";
    }
    statusLabel->Text = statusText;

    // Обновляем информационную метку
    infoLabel->Text = "Готово к удалению";
    infoLabel->ForeColor = Drawing::Color::DarkRed;
}

System::Void DeleteBusForm::busComboBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
    if (busComboBox->SelectedIndex >= 0) {
        String^ selectedCode = safe_cast<String^>(busComboBox->SelectedItem);
        Bus^ selectedBus = busList->GetBusByFormattedCode(selectedCode);
        UpdateBusInfo(selectedBus);
    }
}

System::Void DeleteBusForm::deleteButton_Click(System::Object^ sender, System::EventArgs^ e) {
    if (busComboBox->SelectedIndex < 0) {
        MessageBox::Show("Выберите автобус для удаления!", "Ошибка",
            MessageBoxButtons::OK, MessageBoxIcon::Error);
        return;
    }

    String^ selectedCode = safe_cast<String^>(busComboBox->SelectedItem);
    Bus^ selectedBus = busList->GetBusByFormattedCode(selectedCode);

    if (selectedBus == nullptr) {
        MessageBox::Show("Выбранный автобус не найден в системе!", "Ошибка",
            MessageBoxButtons::OK, MessageBoxIcon::Error);
        return;
    }

    // Подтверждение удаления
    String^ message = String::Format(
        "Вы действительно хотите удалить автобус?\n\n"
        "Код: {0}\n"
        "Марка: {1}\n"
        "Модель: {2}\n"
        "Мест: {3}\n"
        "Состояние: {4}\n\n"
        "Данное действие нельзя отменить!",
        selectedBus->GetFormattedCode(),
        selectedBus->GetBrand(),
        selectedBus->GetModel(),
        selectedBus->GetPlaceCount(),
        selectedBus->GetTechCondition());

    DialogResult result = MessageBox::Show(
        message,
        "Подтверждение удаления",
        MessageBoxButtons::YesNo,
        MessageBoxIcon::Warning);

    if (result == DialogResult::Yes) {
        try {
            // Удаляем автобус через BusList
            bool success = busList->InternalRemoveBus(selectedCode);

            if (success) {
                MessageBox::Show("Автобус успешно удален!", "Успех",
                    MessageBoxButtons::OK, MessageBoxIcon::Information);

                // Обновляем список в ComboBox
                LoadBusCodes();

                // Если еще есть автобусы, выбираем первый
                if (busComboBox->Items->Count > 0) {
                    busComboBox->SelectedIndex = 0;
                }
                else {
                    // Если автобусов не осталось, закрываем форму
                    this->DialogResult = DialogResult::OK;
                    this->Close();
                }
            }
            else {
                MessageBox::Show("Не удалось удалить автобус!", "Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }
        catch (Exception^ ex) {
            MessageBox::Show("Ошибка при удалении: " + ex->Message, "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }
}

System::Void DeleteBusForm::cancelButton_Click(System::Object^ sender, System::EventArgs^ e) {
    this->DialogResult = DialogResult::Cancel;
    this->Close();
}