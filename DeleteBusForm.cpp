// DeleteBusForm.cpp - УПРОЩЕННАЯ ВЕРСИЯ
#include "DeleteBusForm.h"

using namespace InfSystBusStation;
using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;

DeleteBusForm::DeleteBusForm(BusList^ busList) {
    InitializeComponent();
    this->busList = busList;

    // Загрузка данных через BusList
    LoadBusCodes();
}

DeleteBusForm::~DeleteBusForm() {
    if (components) {
        delete components;
    }
}

// Загрузка кодов автобусов через BusList
void DeleteBusForm::LoadBusCodes() {
    busComboBox->Items->Clear();

    if (busList == nullptr) {
        busComboBox->Enabled = false;
        deleteButton->Enabled = false;
        infoLabel->Text = "Ошибка: список автобусов не инициализирован!";
        infoLabel->ForeColor = Color::DarkRed;
        return;
    }

    // Используем метод BusList для получения данных
    auto busCodes = busList->GetAllBusFormattedCodes();

    if (busCodes == nullptr || busCodes->Count == 0) {
        busComboBox->Enabled = false;
        deleteButton->Enabled = false;
        infoLabel->Text = "Список автобусов пуст!";
        infoLabel->ForeColor = Color::DarkRed;
        return;
    }

    for each (String ^ code in busCodes) {
        busComboBox->Items->Add(code);
    }

    if (busComboBox->Items->Count > 0) {
        busComboBox->SelectedIndex = 0;
    }
}

// Обновление информации через BusList
// DeleteBusForm.cpp - Оставьте старую сигнатуру
void DeleteBusForm::UpdateBusInfo(Bus^ bus) {
    if (bus == nullptr) {
        ClearBusInfo();
        return;
    }

    // Заполняем информацию
    brandLabel->Text = "Марка: " + bus->GetBrand();
    modelLabel->Text = "Модель: " + bus->GetModel();
    placesLabel->Text = "Количество мест: " + bus->GetSeatCount().ToString();
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
    infoLabel->ForeColor = Color::DarkRed;
}

void DeleteBusForm::ClearBusInfo() {
    brandLabel->Text = "Марка: не указано";
    modelLabel->Text = "Модель: не указано";
    placesLabel->Text = "Количество мест: не указано";
    conditionLabel->Text = "Техническое состояние: не указано";
    maintenanceLabel->Text = "Последнее ТО: не указано";
    statusLabel->Text = "Статус: не указано";
}

System::Void DeleteBusForm::busComboBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
    if (busComboBox->SelectedIndex >= 0) {
        String^ selectedCode = safe_cast<String^>(busComboBox->SelectedItem);
        // Получаем автобус через BusList
        Bus^ selectedBus = busList->GetBusByFormattedCode(selectedCode);
        UpdateBusInfo(selectedBus);  // Передаем объект Bus, а не строку
    }
}

System::Void DeleteBusForm::deleteButton_Click(System::Object^ sender, System::EventArgs^ e) {
    if (busComboBox->SelectedIndex < 0) {
        System::Windows::Forms::MessageBox::Show("Выберите автобус для удаления!", "Ошибка",
            System::Windows::Forms::MessageBoxButtons::OK,
            System::Windows::Forms::MessageBoxIcon::Error);
        return;
    }

    String^ selectedCode = safe_cast<String^>(busComboBox->SelectedItem);

    // Подтверждение удаления
    String^ message = String::Format(
        "Вы действительно хотите удалить автобус с кодом {0}?\n\n"
        "Данное действие нельзя отменить!",
        selectedCode);

    System::Windows::Forms::DialogResult result =
        System::Windows::Forms::MessageBox::Show(
            message,
            "Подтверждение удаления",
            System::Windows::Forms::MessageBoxButtons::YesNo,
            System::Windows::Forms::MessageBoxIcon::Warning);

    if (result == System::Windows::Forms::DialogResult::Yes) {
        try {
            // Удаляем автобус через BusList
            bool success = busList->RemoveBusByFormattedCode(selectedCode);

            if (success) {
                System::Windows::Forms::MessageBox::Show("Автобус успешно удален!", "Успех",
                    System::Windows::Forms::MessageBoxButtons::OK,
                    System::Windows::Forms::MessageBoxIcon::Information);

                // Обновляем список через BusList
                LoadBusCodes();

                // Если еще есть автобусы, выбираем первый
                if (busComboBox->Items->Count > 0) {
                    busComboBox->SelectedIndex = 0;
                }
                else {
                    // Если автобусов не осталось, закрываем форму
                    this->DialogResult = System::Windows::Forms::DialogResult::OK;
                    this->Close();
                }
            }
            else {
                System::Windows::Forms::MessageBox::Show("Не удалось удалить автобус!", "Ошибка",
                    System::Windows::Forms::MessageBoxButtons::OK,
                    System::Windows::Forms::MessageBoxIcon::Error);
            }
        }
        catch (Exception^ ex) {
            System::Windows::Forms::MessageBox::Show("Ошибка при удалении: " + ex->Message, "Ошибка",
                System::Windows::Forms::MessageBoxButtons::OK,
                System::Windows::Forms::MessageBoxIcon::Error);
        }
    }
}

System::Void DeleteBusForm::cancelButton_Click(System::Object^ sender, System::EventArgs^ e) {
    this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
    this->Close();
}