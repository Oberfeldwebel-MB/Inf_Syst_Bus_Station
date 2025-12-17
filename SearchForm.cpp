#include "SearchForm.h"
#include "Search.hpp"
#include "TripList.hpp"
#include "BusList.hpp"
#include "DriversList.hpp"

using namespace InfSystBusStation;
using namespace System;
using namespace System::Windows::Forms;
using namespace System::Collections::Generic;

// Загрузить список водителей в ComboBox
void SearchForm::LoadDriverComboBox() {
    driverComboBox->Items->Clear();
    if (driverList != nullptr) {
        for each (Driver ^ driver in driverList->AllDrivers) {
            driverComboBox->Items->Add(driver->GetFullName());
        }
    }
}

// Загрузить список автобусов в ComboBox
void SearchForm::LoadBusComboBox() {
    busComboBox->Items->Clear();
    if (busList != nullptr) {
        for each (Bus ^ bus in busList->AllBuses) {
            busComboBox->Items->Add(bus->GetBrand() + " " + bus->GetModel() +
                " (" + bus->GetFormattedCode() + ")");
        }
    }
}

// ================= ОБРАБОТЧИКИ ЧЕКБОКСОВ =================

System::Void SearchForm::checkStartBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
    StartPointBox->Enabled = checkStartBox->Checked;
    if (!checkStartBox->Checked) {
        StartPointBox->Clear();
    }
}

System::Void SearchForm::checkFinishBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
    FinishPointBox->Enabled = checkFinishBox->Checked;
    if (!checkFinishBox->Checked) {
        FinishPointBox->Clear();
    }
}

System::Void SearchForm::checkDateStartBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
    DepDateBox->Enabled = checkDateStartBox->Checked;
    if (!checkDateStartBox->Checked) {
        DepDateBox->Clear();
    }
}

System::Void SearchForm::checkDateFinishBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
    ArrDateBox->Enabled = checkDateFinishBox->Checked;
    if (!checkDateFinishBox->Checked) {
        ArrDateBox->Clear();
    }
}

System::Void SearchForm::checkPriceBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
    PriceBox->Enabled = checkPriceBox->Checked;
    if (!checkPriceBox->Checked) {
        PriceBox->Clear();
    }
}

System::Void SearchForm::checkDriverBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
    driverComboBox->Enabled = checkDriverBox->Checked;
    if (!checkDriverBox->Checked) {
        driverComboBox->SelectedIndex = -1;
    }
}

System::Void SearchForm::checkBusBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
    busComboBox->Enabled = checkBusBox->Checked;
    if (!checkBusBox->Checked) {
        busComboBox->SelectedIndex = -1;
    }
}

// ================= ОСНОВНЫЕ МЕТОДЫ =================

System::Void SearchForm::SearchButton_Click(System::Object^ sender, System::EventArgs^ e) {
    try {
        if (tripList == nullptr) {
            MessageBox::Show("Список поездок не загружен!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        // === ПОДГОТОВКА ПАРАМЕТРОВ ===
        String^ startPoint = nullptr;
        String^ finishPoint = nullptr;
        DateTime^ date = nullptr;
        int minPrice = 0, maxPrice = 0;
        String^ driverName = nullptr;
        String^ busCode = nullptr;

        // Пункт отправления
        if (checkStartBox->Checked && !String::IsNullOrEmpty(StartPointBox->Text)) {
            startPoint = StartPointBox->Text->Trim();
        }

        // Пункт назначения
        if (checkFinishBox->Checked && !String::IsNullOrEmpty(FinishPointBox->Text)) {
            finishPoint = FinishPointBox->Text->Trim();
        }

        // Дата
        if (checkDateStartBox->Checked && !String::IsNullOrEmpty(DepDateBox->Text)) {
            try {
                date = gcnew DateTime(DateTime::ParseExact(
                    DepDateBox->Text, "dd/MM/yyyy HH:mm", nullptr).Date);
            }
            catch (Exception^) {
                MessageBox::Show("Неверный формат даты! Используйте ДД/ММ/ГГГГ ЧЧ:ММ",
                    "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }
        }

        // Цена
        if (checkPriceBox->Checked && !String::IsNullOrEmpty(PriceBox->Text)) {
            try {
                int price = Convert::ToInt32(PriceBox->Text);
                if (price < 0) {
                    MessageBox::Show("Цена не может быть отрицательной!", "Ошибка",
                        MessageBoxButtons::OK, MessageBoxIcon::Warning);
                    return;
                }
                minPrice = price - 100;
                maxPrice = price + 100;
                if (minPrice < 0) minPrice = 0;
            }
            catch (Exception^) {
                MessageBox::Show("Цена должна быть числом!", "Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }
        }

        // Водитель
        if (checkDriverBox->Checked && driverComboBox->SelectedItem != nullptr) {
            driverName = driverComboBox->SelectedItem->ToString();
        }

        // Автобус
        if (checkBusBox->Checked && busComboBox->SelectedItem != nullptr) {
            String^ busInfo = busComboBox->SelectedItem->ToString();
            int startBracket = busInfo->IndexOf('[');
            int endBracket = busInfo->IndexOf(']');
            if (startBracket != -1 && endBracket != -1 && endBracket > startBracket) {
                busCode = busInfo->Substring(startBracket + 1, endBracket - startBracket - 1);
            }
        }

        // === ВЫЗОВ МЕТОДА ПОИСКА ===
        searchResults = Search::SearchTrips(
            tripList,
            startPoint,
            finishPoint,
            date,
            minPrice,
            maxPrice,
            driverName,
            busCode
        );

        // === ОБРАБОТКА РЕЗУЛЬТАТОВ ===
        if (searchResults != nullptr && searchResults->Count > 0) {
            this->DialogResult = System::Windows::Forms::DialogResult::OK;
            this->Close();
        }
        else {
            MessageBox::Show("По указанным критериям ничего не найдено.\n"
                "Попробуйте изменить параметры поиска или сбросить критерии.",
                "Результат поиска", MessageBoxButtons::OK, MessageBoxIcon::Information);
        }
    }
    catch (ArgumentException^ ex) {
        MessageBox::Show(ex->Message, "Ошибка валидации",
            MessageBoxButtons::OK, MessageBoxIcon::Warning);
    }
    catch (Exception^ ex) {
        MessageBox::Show("Ошибка при поиске: " + ex->Message,
            "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}

System::Void SearchForm::back_add_Click(System::Object^ sender, System::EventArgs^ e) {
    this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
    this->Close();
}