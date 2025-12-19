#include "DeleteDriverForm.h"
#include "Search.hpp" 

using namespace InfSystBusStation;
using namespace System::Windows::Forms;

// Загрузка имен водителей в ComboBox
void DeleteDriverForm::LoadDriverNames() {
    driverComboBox->Items->Clear();

    if (driversList == nullptr || driversList->Count == 0) {
        driverComboBox->Enabled = false;
        deleteButton->Enabled = false;
        infoLabel->Text = "Список водителей пуст!";
        infoLabel->ForeColor = Drawing::Color::DarkRed;
        return;
    }

    for each (Driver ^ driver in driversList->AllDrivers) {
        driverComboBox->Items->Add(driver->GetFullName());
    }

    if (driverComboBox->Items->Count > 0) {
        driverComboBox->SelectedIndex = 0;
    }
}

// Обновление информации о выбранном водителе
void DeleteDriverForm::UpdateDriverInfo(Driver^ driver) {
    if (driver == nullptr) {
        licenseLabel->Text = "Водительские права: не указано";
        passportLabel->Text = "Паспорт: не указано";
        salaryLabel->Text = "Зарплата: не указано";
        statusLabel->Text = "Статус: не указано";
        return;
    }

    // Водительские права
    licenseLabel->Text = "Водительские права: " + driver->GetLicense();

    // Паспортные данные
    String^ passportText = "Паспорт: ";
    if (!String::IsNullOrEmpty(driver->GetPassportSeries()) &&
        !String::IsNullOrEmpty(driver->GetPassportNumber())) {
        passportText += driver->GetPassportSeries() + " " + driver->GetPassportNumber();
    }
    else {
        passportText += "не указано";
    }
    passportLabel->Text = passportText;

    // Зарплата
    salaryLabel->Text = "Зарплата: " + driver->GetSalary().ToString("N0") + " руб.";

    // Статус
    statusLabel->Text = "Статус: " + (driver->GetAvailability() ? "Доступен" : "Занят");

    // Обновляем информационную метку
    infoLabel->Text = "Готово к удалению";
    infoLabel->ForeColor = Drawing::Color::DarkRed;
}

System::Void DeleteDriverForm::driverComboBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
    if (driverComboBox->SelectedIndex >= 0) {
        String^ selectedFio = safe_cast<String^>(driverComboBox->SelectedItem);
        Driver^ selectedDriver = Search::FindDriverByName(driversList, selectedFio);

        UpdateDriverInfo(selectedDriver);
    }
}

System::Void DeleteDriverForm::deleteButton_Click(System::Object^ sender, System::EventArgs^ e) {
    if (driverComboBox->SelectedIndex < 0) {
        MessageBox::Show("Выберите водителя для удаления!", "Ошибка",
            MessageBoxButtons::OK, MessageBoxIcon::Error);
        return;
    }

    String^ selectedFio = safe_cast<String^>(driverComboBox->SelectedItem);
    Driver^ selectedDriver = Search::FindDriverByName(driversList, selectedFio);

    if (selectedDriver == nullptr) {
        MessageBox::Show("Выбранный водитель не найден в системе!", "Ошибка",
            MessageBoxButtons::OK, MessageBoxIcon::Error);
        return;
    }

    // Подтверждение удаления
    String^ message = String::Format(
        "Вы действительно хотите удалить водителя?\n\n"
        "ФИО: {0}\n"
        "Права: {1}\n"
        "Паспорт: {2} {3}\n\n"
        "Данное действие нельзя отменить!",
        selectedDriver->GetFullName(),
        selectedDriver->GetLicense(),
        selectedDriver->GetPassportSeries(),
        selectedDriver->GetPassportNumber());

    System::Windows::Forms::DialogResult result = MessageBox::Show(
        message,
        "Подтверждение удаления",
        MessageBoxButtons::YesNo,
        MessageBoxIcon::Warning);

    if (result == System::Windows::Forms::DialogResult::Yes) {
        try {
            bool success = driversList->RemoveDriver(selectedFio);

            if (success) {
                MessageBox::Show("Водитель успешно удален!", "Успех",
                    MessageBoxButtons::OK, MessageBoxIcon::Information);

                this->DialogResult = System::Windows::Forms::DialogResult::OK;
                this->Close();
            }
            else {
                MessageBox::Show("Не удалось удалить водителя!", "Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }
        catch (Exception^ ex) {
            MessageBox::Show("Ошибка при удалении: " + ex->Message, "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }
}

System::Void DeleteDriverForm::cancelButton_Click(System::Object^ sender, System::EventArgs^ e) {
    this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
    this->Close();
}