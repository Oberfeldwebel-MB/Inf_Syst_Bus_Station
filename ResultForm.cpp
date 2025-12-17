#include "ResultForm.h"
#include "TicketSelectionForm.h"

using namespace InfSystBusStation;
using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;

void ResultForm::UpdateButtonsVisibility() {
    bool isUserMode = !isAdminMode;

    // В пользовательском режиме скрываем кнопки админа
    addTripMenuItem->Visible = isAdminMode;
    deleteTripMenuItem->Visible = isAdminMode;
    editTripMenuItem->Visible = isAdminMode;

    // В админском режиме скрываем кнопку покупки
    btnBuyTicket->Visible = isUserMode;
    selectColumn->Visible = isUserMode;

    if (isAdminMode) {
        this->Text = L"Результаты поиска (Администратор)";
    }
    else {
        this->Text = L"Результаты поиска (Пользователь)";
        btnBuyTicket->Enabled = false; // Включается при выборе поездки
    }
}

void ResultForm::UpdateDataGridView() {
    tripsDataGridView->Rows->Clear();

    if (tripList == nullptr || !tripList->HasSearchResults()) {
        // Если нет результатов поиска, показываем сообщение
        tripsDataGridView->Rows->Add();
        tripsDataGridView->Rows[0]->Cells[1]->Value = L"Нет результатов поиска";
        tripsDataGridView->Rows[0]->Cells[1]->Style->ForeColor = Color::Red;
        return;
    }

    int rowIndex = 0;
    int tripNumber = 1;

    // Используем результаты поиска вместо всех поездок
    auto searchResults = tripList->GetSearchResults();

    for each (Trip ^ trip in searchResults) {
        tripsDataGridView->Rows->Add();

        // Галочка выбора (только для пользовательского режима)
        bool canSelect = !isAdminMode && trip->IsPlanned() && trip->GetAvailableSeatsCount() > 0;

        tripsDataGridView->Rows[rowIndex]->Cells[0]->Value = false;
        tripsDataGridView->Rows[rowIndex]->Cells[0]->ReadOnly = !canSelect;

        // Номер
        tripsDataGridView->Rows[rowIndex]->Cells[1]->Value = tripNumber.ToString();

        // Начальный пункт
        tripsDataGridView->Rows[rowIndex]->Cells[2]->Value = trip->GetStartPoint();

        // Конечный пункт
        tripsDataGridView->Rows[rowIndex]->Cells[3]->Value = trip->GetFinishPoint();

        // Автобус
        String^ busInfo = L"Не назначен";
        if (trip->GetBus() != nullptr) {
            busInfo = trip->GetBus()->GetBrand() + L" " + trip->GetBus()->GetModel();
        }
        tripsDataGridView->Rows[rowIndex]->Cells[4]->Value = busInfo;

        // Дата отправления
        tripsDataGridView->Rows[rowIndex]->Cells[5]->Value =
            trip->GetTripDate().ToString(L"dd.MM.yyyy HH:mm");

        // Дата прибытия
        DateTime arrivalDate = trip->GetTripDate().AddHours(2);
        tripsDataGridView->Rows[rowIndex]->Cells[6]->Value =
            arrivalDate.ToString(L"dd.MM.yyyy HH:mm");

        // Цена
        tripsDataGridView->Rows[rowIndex]->Cells[7]->Value =
            trip->GetPrice().ToString(L"N0") + L" руб.";

        // Водитель
        String^ driverInfo = L"Не назначен";
        if (trip->GetDriver() != nullptr) {
            driverInfo = trip->GetDriver()->GetFullName();
        }
        tripsDataGridView->Rows[rowIndex]->Cells[8]->Value = driverInfo;

        // Цвет строки
        if (!trip->IsPlanned()) {
            // Неактивные поездки
            tripsDataGridView->Rows[rowIndex]->DefaultCellStyle->BackColor = Color::LightGray;
        }
        else if (trip->GetAvailableSeatsCount() <= 0) {
            // Нет мест
            tripsDataGridView->Rows[rowIndex]->DefaultCellStyle->BackColor = Color::LightPink;
        }

        rowIndex++;
        tripNumber++;
    }
}

// === ОБРАБОТЧИКИ СОБЫТИЙ ===

System::Void ResultForm::AddTrip_Click(System::Object^ sender, System::EventArgs^ e) {
    // В форме результатов нельзя добавлять поездки
    MessageBox::Show(L"В режиме просмотра результатов нельзя добавлять поездки",
        L"Информация", MessageBoxButtons::OK, MessageBoxIcon::Information);
}

System::Void ResultForm::DeleteTrip_Click(System::Object^ sender, System::EventArgs^ e) {
    // В форме результатов нельзя удалять поездки
    MessageBox::Show(L"В режиме просмотра результатов нельзя удалять поездки",
        L"Информация", MessageBoxButtons::OK, MessageBoxIcon::Information);
}

System::Void ResultForm::EditTrip_Click(System::Object^ sender, System::EventArgs^ e) {
    // В форме результатов нельзя редактировать поездки
    MessageBox::Show(L"В режиме просмотра результатов нельзя редактировать поездки",
        L"Информация", MessageBoxButtons::OK, MessageBoxIcon::Information);
}

System::Void ResultForm::Search_Click(System::Object^ sender, System::EventArgs^ e) {
    try {
        // Создаем и показываем форму поиска
        SearchForm^ searchForm = gcnew SearchForm(tripList, busList, driverList);

        if (searchForm->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
            // Получаем результаты из формы поиска
            List<Trip^>^ results = searchForm->SearchResults;

            if (results != nullptr && results->Count > 0) {
                // Сохраняем результаты в TripList
                tripList->SetSearchResults(results);

                // Обновляем отображение с новыми результатами
                UpdateDataGridView();

                MessageBox::Show(String::Format(L"Найдено {0} поездок", results->Count),
                    L"Результаты поиска", MessageBoxButtons::OK, MessageBoxIcon::Information);
            }
            else {
                MessageBox::Show(L"Поиск не дал результатов. Попробуйте изменить критерии поиска.",
                    L"Результаты поиска", MessageBoxButtons::OK, MessageBoxIcon::Information);
            }
        }
    }
    catch (Exception^ ex) {
        MessageBox::Show(L"Ошибка при поиске: " + ex->Message,
            L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}

System::Void ResultForm::Back_Click(System::Object^ sender, System::EventArgs^ e) {
    this->DialogResult = System::Windows::Forms::DialogResult::OK;
    this->Close();
}

System::Void ResultForm::BuyTicket_Click(System::Object^ sender, System::EventArgs^ e) {
    try {
        if (!tripList->HasSearchResults()) {
            MessageBox::Show(L"Нет доступных поездок для покупки", L"Внимание",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }

        // Найти выбранную строку
        int selectedRowIndex = -1;
        for (int i = 0; i < tripsDataGridView->Rows->Count; i++) {
            DataGridViewRow^ row = tripsDataGridView->Rows[i];
            if (row->Cells[0]->Value != nullptr && safe_cast<bool>(row->Cells[0]->Value)) {
                if (selectedRowIndex != -1) {
                    MessageBox::Show(L"Выберите только одну поездку", L"Внимание",
                        MessageBoxButtons::OK, MessageBoxIcon::Warning);
                    return;
                }
                selectedRowIndex = i;
            }
        }

        if (selectedRowIndex == -1) {
            MessageBox::Show(L"Выберите поездку", L"Внимание",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }

        // Получить данные поездки
        DataGridViewRow^ selectedRow = tripsDataGridView->Rows[selectedRowIndex];
        String^ startPoint = safe_cast<String^>(selectedRow->Cells[2]->Value);
        String^ finishPoint = safe_cast<String^>(selectedRow->Cells[3]->Value);
        String^ route = startPoint + L" → " + finishPoint;

        // Найти поездку в результатах поиска
        auto searchResults = tripList->GetSearchResults();
        Trip^ selectedTrip = nullptr;

        for each (Trip ^ trip in searchResults) {
            if (trip->GetStartPoint() == startPoint && trip->GetFinishPoint() == finishPoint) {
                selectedTrip = trip;
                break;
            }
        }

        if (selectedTrip == nullptr) {
            MessageBox::Show(L"Поездка не найдена в результатах поиска", L"Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        // Проверить места
        if (selectedTrip->GetAvailableSeatsCount() <= 0) {
            MessageBox::Show(L"Нет свободных мест", L"Информация",
                MessageBoxButtons::OK, MessageBoxIcon::Information);
            return;
        }

        // Создать новый заказ, если его нет
        if (currentOrder == nullptr) {
            // TODO: Получить имя пассажира (можно из формы входа или запросить)
            String^ passengerName = L"Пассажир"; // Заменить на реальное имя
            currentOrder = gcnew Order(passengerName);
        }

        // Открыть форму выбора билета
        TicketSelectionForm^ ticketForm = gcnew TicketSelectionForm(selectedTrip, currentOrder);

        if (ticketForm->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
            if (ticketForm->TicketAdded) {
                MessageBox::Show(L"Билет добавлен в заказ", L"Успех",
                    MessageBoxButtons::OK, MessageBoxIcon::Information);

                // Показать форму заказа с билетами
                OrderForm^ orderForm = gcnew OrderForm(currentOrder);
                orderForm->ShowDialog();

                // Обновляем данные о поездках (возможно изменилось количество свободных мест)
                UpdateDataGridView();
            }
        }
    }
    catch (Exception^ ex) {
        MessageBox::Show(L"Ошибка: " + ex->Message, L"Ошибка",
            MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}

System::Void ResultForm::tripsDataGridView_CellContentClick(System::Object^ sender,
    System::Windows::Forms::DataGridViewCellEventArgs^ e) {

    if (e->ColumnIndex == 0 && e->RowIndex >= 0 && !isAdminMode) {
        bool isChecked = safe_cast<bool>(tripsDataGridView->Rows[e->RowIndex]->Cells[0]->Value);

        if (isChecked) {
            // Снять выбор с других строк
            for (int i = 0; i < tripsDataGridView->Rows->Count; i++) {
                if (i != e->RowIndex) {
                    tripsDataGridView->Rows[i]->Cells[0]->Value = false;
                }
            }
            // Включить кнопку покупки
            btnBuyTicket->Enabled = true;
        }
        else {
            // Выключить кнопку покупки если ничего не выбрано
            btnBuyTicket->Enabled = false;
        }
    }
}