// BusListForm.cpp
#include "BusListForm.h"

using namespace InfSystBusStation;
using namespace System;
using namespace System::Windows::Forms;

void BusListForm::UpdateDataGridView() {
    busesDataGridView->Rows->Clear();

    if (busList == nullptr || busList->Count == 0) {
        busesCountLabel->Text = "Всего автобусов: 0";
        availableLabel->Text = "Доступно: 0";
        return;
    }

    int rowIndex = 0;
    for each (Bus ^ bus in busList->AllBuses) {
        busesDataGridView->Rows->Add();

        // Заполняем данные в колонки 
        busesDataGridView->Rows[rowIndex]->Cells[0]->Value = false;
        busesDataGridView->Rows[rowIndex]->Cells[1]->Value = (rowIndex + 1).ToString();
        busesDataGridView->Rows[rowIndex]->Cells[2]->Value = bus->GetFormattedCode();
        busesDataGridView->Rows[rowIndex]->Cells[3]->Value = bus->GetBrand();
        busesDataGridView->Rows[rowIndex]->Cells[4]->Value = bus->GetModel();
        busesDataGridView->Rows[rowIndex]->Cells[5]->Value = bus->GetSeatCount().ToString();
        busesDataGridView->Rows[rowIndex]->Cells[6]->Value = bus->GetTechCondition();
        busesDataGridView->Rows[rowIndex]->Cells[7]->Value = bus->GetLastMaintenance();


        String^ statusText = "";
        if (bus->GetAvailability()) {
            statusText = "Доступен";
            busesDataGridView->Rows[rowIndex]->DefaultCellStyle->BackColor = Drawing::Color::LightGreen;
        }
        else {
            statusText = "Не доступен";
            busesDataGridView->Rows[rowIndex]->DefaultCellStyle->BackColor = Drawing::Color::LightGray;
        }
        busesDataGridView->Rows[rowIndex]->Cells[8]->Value = statusText;

        rowIndex++;
    }

    busesCountLabel->Text = "Всего автобусов: " + busList->Count.ToString();
    availableLabel->Text = "Доступно: " + busList->AvailableCount.ToString();
}

System::Void BusListForm::AddBus_Click(System::Object^ sender, System::EventArgs^ e) {
    if (busList == nullptr) {
        MessageBox::Show("Ошибка: список автобусов не инициализирован!",
            "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        return;
    }


    if (busList->ShowAddBusForm(this)) {
        UpdateDataGridView();
        MessageBox::Show("Автобус успешно добавлен!", "Успех",
            MessageBoxButtons::OK, MessageBoxIcon::Information);
    }
}

System::Void BusListForm::DeleteBus_Click(System::Object^ sender, System::EventArgs^ e) {
    if (busList == nullptr) {
        MessageBox::Show("Ошибка: список автобусов не инициализирован!",
            "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        return;
    }

    if (busList->Count == 0) {
        MessageBox::Show("Список автобусов пуст!", "Информация",
            MessageBoxButtons::OK, MessageBoxIcon::Information);
        return;
    }

    if (busList->ShowDeleteBusForm(this)) {
        UpdateDataGridView();
        MessageBox::Show("Автобус успешно удален!", "Успех",
            MessageBoxButtons::OK, MessageBoxIcon::Information);
    }
}

System::Void BusListForm::Back_Click(System::Object^ sender, System::EventArgs^ e) {
    this->Close();
}

System::Void BusListForm::Refresh_Click(System::Object^ sender, System::EventArgs^ e) {
    UpdateDataGridView();
    MessageBox::Show("Список автобусов обновлен!", "Обновление",
        MessageBoxButtons::OK, MessageBoxIcon::Information);
}

System::Void BusListForm::SendToMaintenance_Click(System::Object^ sender, System::EventArgs^ e) {
    if (busList == nullptr || busList->Count == 0) {
        MessageBox::Show("Список автобусов пуст!", "Внимание",
            MessageBoxButtons::OK, MessageBoxIcon::Warning);
        return;
    }

    String^ selectedBusCode = nullptr;
    int selectedRowIndex = -1;
    int selectedCount = 0;

    // Подсчет выбранных автобусов
    for (int i = 0; i < busesDataGridView->Rows->Count; i++) {
        DataGridViewRow^ row = busesDataGridView->Rows[i];

        // Проверяем, есть ли значение в ячейке выбора
        if (row->Cells[0]->Value != nullptr) {
            bool isSelected = safe_cast<bool>(row->Cells[0]->Value);

            if (isSelected) {
                selectedBusCode = safe_cast<String^>(row->Cells[2]->Value);
                selectedRowIndex = i;
                selectedCount++;


                if (selectedCount > 1) {
                    break;
                }
            }
        }
    }

    if (selectedCount == 0) {
        MessageBox::Show("Не выбран ни один автобус!\nПоставьте галочку в колонке 'Выбрать'.",
            "Внимание", MessageBoxButtons::OK, MessageBoxIcon::Warning);
        return;
    }

    if (selectedCount > 1) {
        MessageBox::Show("Можно выбрать только один автобус за раз!\nСнимите лишние галочки.",
            "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        return;
    }

    // Получаем сегодняшнюю дату в формате DD/MM/YYYY
    DateTime today = DateTime::Today;
    String^ todayString = today.ToString("dd/MM/yyyy");

    // Подтверждение действия
    String^ message = String::Format("Вы уверены, что хотите отправить автобус на ТО?\n\n"
        "Автобус: {0}\n"
        "Дата ТО: {1}\n\n"
        "После ТО техническое состояние будет установлено на 'Отличное'.",
        selectedBusCode, todayString);

    if (MessageBox::Show(message, "Подтверждение отправки на ТО",
        MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::No) {
        return;
    }

    // Получаем код автобуса без форматирования для поиска
    String^ codeWithoutFormatting = selectedBusCode->Replace("/", "");

    try {
        // Обновляем дату ТО
        bool dateUpdated = busList->UpdateMaintenanceDate(codeWithoutFormatting, todayString);

        if (!dateUpdated) {
            MessageBox::Show("Ошибка при обновлении даты ТО!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        // Обновляем техническое состояние
        bool conditionUpdated = busList->UpdateBusCondition(codeWithoutFormatting, "Отличное");

        if (!conditionUpdated) {
            MessageBox::Show("Ошибка при обновлении технического состояния!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        // Снимаем галочку после успешной отправки
        busesDataGridView->Rows[selectedRowIndex]->Cells[0]->Value = false;

        // Обновляем отображение
        UpdateDataGridView();

        MessageBox::Show(String::Format("Автобус {0} успешно отправлен на ТО!\n"
            "Дата ТО: {1}\n"
            "Техническое состояние: Отличное",
            selectedBusCode, todayString),
            "Успешно", MessageBoxButtons::OK, MessageBoxIcon::Information);
    }
    catch (Exception^ ex) {
        MessageBox::Show("Ошибка при отправке автобуса на ТО: " + ex->Message,
            "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}