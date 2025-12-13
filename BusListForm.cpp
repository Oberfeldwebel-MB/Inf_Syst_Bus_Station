// BusListForm.cpp
#include "BusListForm.h"

using namespace InfSystBusStation;

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
        busesDataGridView->Rows[rowIndex]->Cells[0]->Value = (rowIndex + 1).ToString();
        busesDataGridView->Rows[rowIndex]->Cells[1]->Value = bus->GetFormattedCode();
        busesDataGridView->Rows[rowIndex]->Cells[2]->Value = bus->GetBrand();
        busesDataGridView->Rows[rowIndex]->Cells[3]->Value = bus->GetModel();
        busesDataGridView->Rows[rowIndex]->Cells[4]->Value = bus->GetPlaceCount().ToString();
        busesDataGridView->Rows[rowIndex]->Cells[5]->Value = bus->GetTechCondition();
        busesDataGridView->Rows[rowIndex]->Cells[6]->Value = bus->GetLastMaintenance();

        // Статус с цветовой индикацией
        String^ statusText = "";
        if (bus->GetAvailability() && !bus->IsInCriticalCondition()) {
            statusText = "Доступен";
            busesDataGridView->Rows[rowIndex]->DefaultCellStyle->BackColor = Drawing::Color::LightGreen;
        }
        else if (bus->IsInCriticalCondition()) {
            statusText = "Требует ремонта";
            busesDataGridView->Rows[rowIndex]->DefaultCellStyle->BackColor = Drawing::Color::LightCoral;
        }
        else {
            statusText = "Не доступен";
            busesDataGridView->Rows[rowIndex]->DefaultCellStyle->BackColor = Drawing::Color::LightGray;
        }
        busesDataGridView->Rows[rowIndex]->Cells[7]->Value = statusText;

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

    // Используем метод BusList для открытия формы добавления
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

    // Используем метод BusList для открытия формы удаления
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