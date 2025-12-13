// TripListForm.cpp
#include "TimingForm.h"

using namespace InfSystBusStation;

void TripListForm::UpdateDataGridView() {
    tripsDataGridView->Rows->Clear();

    if (tripList == nullptr || tripList->Count == 0) {
        btnBuyTicket->Enabled = false;
        return;
    }

    int rowIndex = 0;

    for each (Trip ^ trip in tripList->AllTrips) {
        tripsDataGridView->Rows->Add();

        // Галочка выбора (только для запланированных поездок)
        bool isPlanned = trip->IsPlanned();
        tripsDataGridView->Rows[rowIndex]->Cells[0]->Value = false;
        tripsDataGridView->Rows[rowIndex]->Cells[0]->ReadOnly = !isPlanned;

        // Номер маршрута
        tripsDataGridView->Rows[rowIndex]->Cells[1]->Value = (rowIndex + 1).ToString();

        // Начальный пункт
        tripsDataGridView->Rows[rowIndex]->Cells[2]->Value = trip->GetStartPoint();

        // Конечный пункт
        tripsDataGridView->Rows[rowIndex]->Cells[3]->Value = trip->GetFinishPoint();

        // Данные об автобусе
        String^ busInfo = "Не назначен";
        if (trip->GetBus() != nullptr) {
            busInfo = trip->GetBus()->GetBrand() + " " + trip->GetBus()->GetModel() +
                " [" + trip->GetBus()->GetFormattedCode() + "]";
        }
        tripsDataGridView->Rows[rowIndex]->Cells[4]->Value = busInfo;

        // Дата отправления
        tripsDataGridView->Rows[rowIndex]->Cells[5]->Value = trip->GetTripDate().ToString("dd.MM.yyyy");

        // Дата прибытия (можно добавить время в пути)
        DateTime arrivalDate = trip->GetTripDate().AddHours(2); // Пример: +2 часа
        tripsDataGridView->Rows[rowIndex]->Cells[6]->Value = arrivalDate.ToString("dd.MM.yyyy HH:mm");

        // Цена билета
        tripsDataGridView->Rows[rowIndex]->Cells[7]->Value = trip->GetPrice().ToString("N0") + " руб.";

        // Данные о водителе
        String^ driverInfo = "Не назначен";
        if (trip->GetDriver() != nullptr) {
            driverInfo = trip->GetDriver()->GetFullName();
        }
        tripsDataGridView->Rows[rowIndex]->Cells[8]->Value = driverInfo;

        // Цветовая индикация
        if (!isPlanned) {
            tripsDataGridView->Rows[rowIndex]->DefaultCellStyle->BackColor = Drawing::Color::LightGray;
            tripsDataGridView->Rows[rowIndex]->DefaultCellStyle->ForeColor = Drawing::Color::Gray;
        }
        else {
            tripsDataGridView->Rows[rowIndex]->DefaultCellStyle->BackColor = Drawing::Color::White;
        }

        rowIndex++;
    }
}

System::Void TripListForm::AddTrip_Click(System::Object^ sender, System::EventArgs^ e) {
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

    // Используем метод TripList для открытия формы добавления
    if (tripList->ShowAddTripForm(this, busList, driverList)) {
        UpdateDataGridView();
        MessageBox::Show("Поездка успешно добавлена!", "Успех",
            MessageBoxButtons::OK, MessageBoxIcon::Information);
    }
}

System::Void TripListForm::DeleteTrip_Click(System::Object^ sender, System::EventArgs^ e) {
    if (tripList == nullptr) {
        MessageBox::Show("Ошибка: список поездок не инициализирован!", "Ошибка",
            MessageBoxButtons::OK, MessageBoxIcon::Error);
        return;
    }

    if (tripList->Count == 0) {
        MessageBox::Show("Расписание пусто!", "Информация",
            MessageBoxButtons::OK, MessageBoxIcon::Information);
        return;
    }

    // Используем метод TripList для открытия формы удаления
    if (tripList->ShowDeleteTripForm(this)) {
        UpdateDataGridView();
        MessageBox::Show("Поездка успешно удалена!", "Успех",
            MessageBoxButtons::OK, MessageBoxIcon::Information);
    }
}

System::Void TripListForm::EditTrip_Click(System::Object^ sender, System::EventArgs^ e) {
    // TODO: Реализовать форму редактирования поездки
    MessageBox::Show("Функция редактирования поездки будет реализована позже", "В разработке",
        MessageBoxButtons::OK, MessageBoxIcon::Information);
}

System::Void TripListForm::Search_Click(System::Object^ sender, System::EventArgs^ e) {
    // TODO: Реализовать форму поиска поездок
    MessageBox::Show("Функция поиска поездок будет реализована позже", "В разработке",
        MessageBoxButtons::OK, MessageBoxIcon::Information);
}

System::Void TripListForm::Back_Click(System::Object^ sender, System::EventArgs^ e) {
    this->Close();
}

System::Void TripListForm::BuyTicket_Click(System::Object^ sender, System::EventArgs^ e) {
    try {
        // Находим выбранную строку
        int selectedRowIndex = -1;
        for (int i = 0; i < tripsDataGridView->Rows->Count; i++) {
            DataGridViewRow^ row = tripsDataGridView->Rows[i];
            if (row->Cells[0]->Value != nullptr && safe_cast<bool>(row->Cells[0]->Value)) {
                if (selectedRowIndex != -1) {
                    MessageBox::Show("Пожалуйста, выберите только одну поездку!", "Внимание",
                        MessageBoxButtons::OK, MessageBoxIcon::Warning);
                    return;
                }
                selectedRowIndex = i;
            }
        }

        if (selectedRowIndex == -1) {
            MessageBox::Show("Выберите поездку для покупки билета!", "Внимание",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }

        // Получаем информацию о выбранной поездке
        DataGridViewRow^ selectedRow = tripsDataGridView->Rows[selectedRowIndex];

        String^ startPoint = safe_cast<String^>(selectedRow->Cells[2]->Value);
        String^ finishPoint = safe_cast<String^>(selectedRow->Cells[3]->Value);
        String^ busInfo = safe_cast<String^>(selectedRow->Cells[4]->Value);
        String^ depDate = safe_cast<String^>(selectedRow->Cells[5]->Value);
        String^ arrDate = safe_cast<String^>(selectedRow->Cells[6]->Value);
        String^ price = safe_cast<String^>(selectedRow->Cells[7]->Value);
        String^ driverInfo = safe_cast<String^>(selectedRow->Cells[8]->Value);

        // TODO: Открыть форму покупки билета с передачей информации
        // Например: TicketPurchaseForm^ ticketForm = gcnew TicketPurchaseForm(...);
        // ticketForm->ShowDialog();

        MessageBox::Show(
            "Переход к покупке билета:\n\n" +
            "Маршрут: " + startPoint + " → " + finishPoint + "\n" +
            "Дата отправления: " + depDate + "\n" +
            "Дата прибытия: " + arrDate + "\n" +
            "Автобус: " + busInfo + "\n" +
            "Водитель: " + driverInfo + "\n" +
            "Цена: " + price + "\n\n" +
            "Форма покупки билета будет открыта.",
            "Информация о поездке",
            MessageBoxButtons::OK,
            MessageBoxIcon::Information
        );

        // Здесь можно открыть форму покупки билета
        // TicketPurchaseForm^ ticketForm = gcnew TicketPurchaseForm(selectedTripInfo);
        // ticketForm->ShowDialog();

    }
    catch (Exception^ ex) {
        MessageBox::Show("Ошибка при выборе поездки: " + ex->Message, "Ошибка",
            MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}

System::Void TripListForm::tripsDataGridView_CellContentClick(System::Object^ sender,
    System::Windows::Forms::DataGridViewCellEventArgs^ e) {

    // Если кликнули на ячейку с галочкой (первая колонка)
    if (e->ColumnIndex == 0 && e->RowIndex >= 0) {
        // Если выбираем эту поездку, снимаем выбор с других
        bool isChecked = safe_cast<bool>(tripsDataGridView->Rows[e->RowIndex]->Cells[0]->Value);

        if (isChecked) {
            // Снимаем выбор со всех других строк
            for (int i = 0; i < tripsDataGridView->Rows->Count; i++) {
                if (i != e->RowIndex) {
                    tripsDataGridView->Rows[i]->Cells[0]->Value = false;
                }
            }
        }
    }
}