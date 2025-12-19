#include "TimingForm.h"
#include "TicketSelectionForm.h"
#include "SearchForm.h"
#include "ResultForm.h"
#include "EditTripForm.h"

using namespace InfSystBusStation;
using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;

void TimingForm::UpdateButtonsVisibility() {
    bool isUserMode = !isAdminMode;

    // В пользовательском режиме скрываем кнопки админа
    addTripMenuItem->Visible = isAdminMode;
    deleteTripMenuItem->Visible = isAdminMode;
    editTripMenuItem->Visible = isAdminMode;

    // В админском режиме скрываем кнопку покупки
    btnBuyTicket->Visible = isUserMode;
    selectColumn->Visible = isUserMode;

    if (isAdminMode) {
        this->Text = L"Расписание поездок (Администратор)";
    }
    else {
        this->Text = L"Расписание поездок (Пользователь)";
        btnBuyTicket->Enabled = false; // Включается при выборе поездки
    }
}

void TimingForm::UpdateDataGridView() {
    tripsDataGridView->Rows->Clear();

    if (tripList == nullptr || tripList->Count == 0) {
        return;
    }

    int rowIndex = 0;
    int tripNumber = 1;

    for each (Trip ^ trip in tripList->AllTrips) {
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
        String^ busInfo = "Не назначен";
        if (trip->GetBus() != nullptr) {
            busInfo = trip->GetBus()->GetBrand() + " " + trip->GetBus()->GetModel();
        }
        tripsDataGridView->Rows[rowIndex]->Cells[4]->Value = busInfo;

        // Дата отправления
        tripsDataGridView->Rows[rowIndex]->Cells[5]->Value =
            trip->GetTripDate().ToString("dd.MM.yyyy HH:mm");

        // Дата прибытия
        DateTime arrivalDate = trip->GetTripDate().AddHours(2);
        tripsDataGridView->Rows[rowIndex]->Cells[6]->Value =
            arrivalDate.ToString("dd.MM.yyyy HH:mm");

        // Цена
        tripsDataGridView->Rows[rowIndex]->Cells[7]->Value =
            trip->GetPrice().ToString("N0") + " руб.";

        // Водитель
        String^ driverInfo = "Не назначен";
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

System::Void TimingForm::AddTrip_Click(System::Object^ sender, System::EventArgs^ e) {
    try {
        AddTripForm^ form = gcnew AddTripForm();
        form->SetTripList(tripList);
        form->SetBusList(busList);
        form->SetDriverList(driverList);

        if (form->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
            UpdateDataGridView(); // Обновить таблицу после добавления
        }
    }
    catch (Exception^ ex) {
        MessageBox::Show("Ошибка при открытии формы добавления: " + ex->Message,
            "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}

void TimingForm::SetCurrentUser(User^ user) {
    currentUser = user;
    if (user != nullptr && currentOrder != nullptr) {
        currentOrder->PassengerName = user->GetFullName();
    }
}

System::Void TimingForm::DeleteTrip_Click(System::Object^ sender, System::EventArgs^ e) {
    try {
        if (tripList == nullptr || tripList->Count == 0) {
            MessageBox::Show("Расписание пусто!", "Информация",
                MessageBoxButtons::OK, MessageBoxIcon::Information);
            return;
        }

        DeleteTripForm^ form = gcnew DeleteTripForm(tripList);

        if (form->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
            UpdateDataGridView(); // Обновить таблицу после удаления
        }
    }
    catch (Exception^ ex) {
        MessageBox::Show("Ошибка при открытии формы удаления: " + ex->Message,
            "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}

System::Void TimingForm::EditTrip_Click(System::Object^ sender, System::EventArgs^ e) {
    try {
        EditTripForm^ editForm = gcnew EditTripForm(tripList, busList, driverList);

        if (editForm->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
            // Получаем выбранную поездку
            Trip^ tripToEdit = tripList->AllTrips[editForm->tripIndex];

            // Применяем изменения
            if (editForm->NewStartPoint != nullptr) {
                tripToEdit->SetStartPoint(editForm->NewStartPoint);
            }
            if (editForm->NewFinishPoint != nullptr) {
                tripToEdit->SetFinishPoint(editForm->NewFinishPoint);
            }
            if (editForm->NewDepDate != nullptr) {
                // Нужно парсить дату из строки и устанавливать
                // tripToEdit->SetDepartureDate(parsedDate);
            }
            if (editForm->NewArrDate != nullptr) {
                // Аналогично для даты прибытия
            }
            if (editForm->NewPrice > 0) {
                tripToEdit->SetPrice(editForm->NewPrice);
            }
            if (editForm->NewDriver != nullptr) {
                tripToEdit->SetDriver(editForm->NewDriver);
            }
            if (editForm->NewBus != nullptr) {
                tripToEdit->SetBus(editForm->NewBus);
            }

            // Обновляем таблицу
            UpdateDataGridView();

            MessageBox::Show("Поездка успешно отредактирована!", "Успех",
                MessageBoxButtons::OK, MessageBoxIcon::Information);
        }
    }
    catch (Exception^ ex) {
        MessageBox::Show("Ошибка при редактировании поездки: " + ex->Message,
            "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}

System::Void TimingForm::Search_Click(System::Object^ sender, System::EventArgs^ e) {
    try {
        // Создаем и показываем форму поиска
        SearchForm^ searchForm = gcnew SearchForm(tripList, busList, driverList);

        if (searchForm->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
            // Получаем результаты из формы поиска
            List<Trip^>^ results = searchForm->SearchResults;

            if (results != nullptr && results->Count > 0) {
                // Сохраняем результаты в TripList
                tripList->SetSearchResults(results);

                // Открываем форму результатов
                ResultForm^ resultsForm = gcnew ResultForm(tripList, busList, driverList);
                resultsForm->SetCurrentOrder(currentOrder);
                resultsForm->SetCurrentUser(currentUser);

                // Если нужно установить пользовательский режим:
                // resultsForm->SetUserMode(true);

                this->Hide();
                resultsForm->ShowDialog();
                this->Show();
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

System::Void TimingForm::Back_Click(System::Object^ sender, System::EventArgs^ e) {
    this->DialogResult = System::Windows::Forms::DialogResult::OK;
    this->Close();
}

System::Void TimingForm::BuyTicket_Click(System::Object^ sender, System::EventArgs^ e) {
    try {
        if (currentOrder == nullptr) {
            MessageBox::Show("Ошибка: заказ не инициализирован", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        // Найти выбранную строку
        int selectedRowIndex = -1;
        for (int i = 0; i < tripsDataGridView->Rows->Count; i++) {
            DataGridViewRow^ row = tripsDataGridView->Rows[i];
            if (row->Cells[0]->Value != nullptr && safe_cast<bool>(row->Cells[0]->Value)) {
                if (selectedRowIndex != -1) {
                    MessageBox::Show("Выберите только одну поездку", "Внимание",
                        MessageBoxButtons::OK, MessageBoxIcon::Warning);
                    return;
                }
                selectedRowIndex = i;
            }
        }

        if (selectedRowIndex == -1) {
            MessageBox::Show("Выберите поездку", "Внимание",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }

        // Получить данные поездки
        DataGridViewRow^ selectedRow = tripsDataGridView->Rows[selectedRowIndex];
        String^ startPoint = safe_cast<String^>(selectedRow->Cells[2]->Value);
        String^ finishPoint = safe_cast<String^>(selectedRow->Cells[3]->Value);
        String^ route = startPoint + " → " + finishPoint;

        // Найти поездку
        Trip^ selectedTrip = tripList->FindTripByRoute(route);

        if (selectedTrip == nullptr) {
            MessageBox::Show("Поездка не найдена", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        // Проверить места
        if (selectedTrip->GetAvailableSeatsCount() <= 0) {
            MessageBox::Show("Нет свободных мест", "Информация",
                MessageBoxButtons::OK, MessageBoxIcon::Information);
            return;
        }

        // Открыть форму выбора билета
        TicketSelectionForm^ ticketForm = gcnew TicketSelectionForm(
            selectedTrip,
            currentOrder,
            currentUser  // ← передаем currentUser
        );

        if (ticketForm->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
            if (ticketForm->TicketAdded) {
                MessageBox::Show("Билет успешно добавлен в заказ!", "Успех",
                    MessageBoxButtons::OK, MessageBoxIcon::Information);

                // Показать подробную информацию
                if (currentOrder->HasTickets()) {
                    currentOrder->PrintOrderInfo(); // Вывод в консоль

                    MessageBox::Show(
                        String::Format("📋 Итог заказа:\n"
                            "Билетов: {0}\n"
                            "Сумма: {1:F2} руб.\n"
                            "Пассажир: {2}",
                            currentOrder->TicketCount,
                            currentOrder->TotalPrice,
                            currentOrder->PassengerName),
                        "Информация о заказе",
                        MessageBoxButtons::OK,
                        MessageBoxIcon::Information
                    );
                }

                UpdateDataGridView(); // Обновить таблицу
            }
        }
    }
    catch (Exception^ ex) {
        MessageBox::Show("Ошибка: " + ex->Message, "Ошибка",
            MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}

System::Void TimingForm::tripsDataGridView_CellContentClick(System::Object^ sender,
    System::Windows::Forms::DataGridViewCellEventArgs^ e) {

    if (e->ColumnIndex == 0 && e->RowIndex >= 0 && !isAdminMode) {
        // Ждем немного, чтобы значение обновилось
        tripsDataGridView->CommitEdit(DataGridViewDataErrorContexts::Commit);

        // Теперь проверяем
        DataGridViewCell^ cell = tripsDataGridView->Rows[e->RowIndex]->Cells[0];

        if (cell->Value != nullptr) {
            bool isChecked = safe_cast<bool>(cell->Value);

            if (isChecked) {
                // Снять выбор с других строк
                for (int i = 0; i < tripsDataGridView->Rows->Count; i++) {
                    if (i != e->RowIndex) {
                        tripsDataGridView->Rows[i]->Cells[0]->Value = false;
                    }
                }
                btnBuyTicket->Enabled = true;
            }
            else {
                // Проверить, остались ли выбранные строки
                bool anyChecked = false;
                for (int i = 0; i < tripsDataGridView->Rows->Count; i++) {
                    DataGridViewCell^ otherCell = tripsDataGridView->Rows[i]->Cells[0];
                    if (otherCell->Value != nullptr && safe_cast<bool>(otherCell->Value)) {
                        anyChecked = true;
                        break;
                    }
                }
                btnBuyTicket->Enabled = anyChecked;
            }
        }
    }
}

