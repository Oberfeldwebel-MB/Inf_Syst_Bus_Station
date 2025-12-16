#include "OrdersForm.h"
#include "Trip.hpp"

using namespace InfSystBusStation;
using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::Collections::Generic;

void OrderForm::InitializeFormData() {
    if (currentOrder == nullptr) {
        lblOrderId->Text = "Заказ №: не загружен";
        lblOrderStatus->Text = "Статус: ошибка";
        lblTotalPrice->Text = "Итого: 0 руб.";
        return;
    }

    // Заполняем информацию о заказе
    lblOrderId->Text = "Заказ №: " + currentOrder->OrderId;
    lblOrderDate->Text = "Дата: " + currentOrder->OrderDate.ToString("dd.MM.yyyy HH:mm");
    lblOrderStatus->Text = "Статус: " + currentOrder->Status;
    lblPassengerName->Text = "Пассажир: " + currentOrder->PassengerName;
    lblTotalPrice->Text = String::Format("Итого: {0:F2} руб.", currentOrder->TotalPrice);

    // Обновляем статистику
    UpdateStatistics();

    // Обновляем счетчик выбранных
    UpdateSelectedCount();

    // Обновляем состояние кнопок
    UpdateButtonsState();
}

void OrderForm::LoadTickets() {
    dgvTickets->Rows->Clear();

    if (currentOrder == nullptr || currentOrder->IsEmpty) {
        return;
    }

    List<Ticket^>^ tickets = currentOrder->Tickets;
    int ticketNumber = 1;

    for each (Ticket ^ ticket in tickets) {
        dgvTickets->Rows->Add();
        int rowIndex = dgvTickets->Rows->Count - 1;

        // Галочка выбора (только для неоплаченных билетов)
        bool canSelect = (ticket->Status != "Оплачен");
        dgvTickets->Rows[rowIndex]->Cells[0]->Value = false;
        dgvTickets->Rows[rowIndex]->Cells[0]->ReadOnly = !canSelect;

        // Номер билета
        dgvTickets->Rows[rowIndex]->Cells[1]->Value = ticketNumber.ToString();

        // Номер места
        dgvTickets->Rows[rowIndex]->Cells[2]->Value = ticket->PlaceNumber.ToString();

        // Тип билета
        dgvTickets->Rows[rowIndex]->Cells[3]->Value = ticket->TicketTypeName;

        // Маршрут
        String^ route = "Неизвестно";
        if (ticket->TripData != nullptr) {
            route = ticket->TripData->GetRoute();
        }
        dgvTickets->Rows[rowIndex]->Cells[4]->Value = route;

        // Дата поездки
        String^ tripDate = "Неизвестно";
        if (ticket->TripData != nullptr) {
            tripDate = ticket->TripData->GetTripDate().ToString("dd.MM.yyyy HH:mm");
        }
        dgvTickets->Rows[rowIndex]->Cells[5]->Value = tripDate;

        // Цена
        dgvTickets->Rows[rowIndex]->Cells[6]->Value =
            String::Format("{0:F2} руб.", ticket->FinalPrice);

        // Статус
        dgvTickets->Rows[rowIndex]->Cells[7]->Value = ticket->Status;

        // Цвет строки в зависимости от статуса
        if (ticket->Status == "Оплачен") {
            dgvTickets->Rows[rowIndex]->DefaultCellStyle->BackColor = Color::LightGreen;
            dgvTickets->Rows[rowIndex]->DefaultCellStyle->ForeColor = Color::DarkGreen;
        }
        else if (ticket->Status == "Забронирован") {
            dgvTickets->Rows[rowIndex]->DefaultCellStyle->BackColor = Color::LightYellow;
        }

        ticketNumber++;
    }
}

void OrderForm::UpdateStatistics() {
    if (currentOrder == nullptr || currentOrder->IsEmpty) {
        lblStatistics->Text = "Статистика: нет билетов";
        return;
    }

    Dictionary<TicketType, int>^ stats = currentOrder->GetTicketsStatistics();

    int adultCount = stats[TicketType::ADULT];
    int childCount = stats[TicketType::CHILD];
    int luggageCount = stats[TicketType::LUGGAGE];

    lblStatistics->Text = String::Format(
        "Статистика: взрослых - {0}, детских - {1}, багажных - {2}",
        adultCount, childCount, luggageCount
    );
}

void OrderForm::UpdateSelectedCount() {
    int selectedCount = 0;

    for (int i = 0; i < dgvTickets->Rows->Count; i++) {
        if (dgvTickets->Rows[i]->Cells[0]->Value != nullptr &&
            safe_cast<bool>(dgvTickets->Rows[i]->Cells[0]->Value)) {
            selectedCount++;
        }
    }

    lblSelectedCount->Text = String::Format("Выбрано билетов: {0}", selectedCount);
}

void OrderForm::UpdateButtonsState() {
    if (currentOrder == nullptr) {
        btnPaySelected->Enabled = false;
        btnRemoveSelected->Enabled = false;
        btnSelectAll->Enabled = false;
        btnDeselectAll->Enabled = false;
        return;
    }

    bool hasTickets = !currentOrder->IsEmpty;
    int selectedCount = 0;
    bool hasUnpaidTickets = false;

    // Считаем выбранные и проверяем наличие неоплаченных билетов
    for (int i = 0; i < dgvTickets->Rows->Count; i++) {
        if (dgvTickets->Rows[i]->Cells[0]->Value != nullptr &&
            safe_cast<bool>(dgvTickets->Rows[i]->Cells[0]->Value)) {
            selectedCount++;
        }

        // Проверяем статус билета в 8-й колонке (индекс 7)
        if (dgvTickets->Rows[i]->Cells[7]->Value != nullptr &&
            safe_cast<String^>(dgvTickets->Rows[i]->Cells[7]->Value) != "Оплачен") {
            hasUnpaidTickets = true;
        }
    }

    // Кнопка "Оплатить выбранные"
    btnPaySelected->Enabled = (selectedCount > 0) && hasUnpaidTickets;
    btnPaySelected->BackColor = btnPaySelected->Enabled ?
        Color::LightGreen : Color::LightGray;

    // Кнопка "Удалить выбранные"
    btnRemoveSelected->Enabled = (selectedCount > 0);
    btnRemoveSelected->BackColor = btnRemoveSelected->Enabled ?
        Color::LightCoral : Color::LightGray;

    // Кнопки "Выбрать все" и "Снять все"
    btnSelectAll->Enabled = hasTickets;
    btnDeselectAll->Enabled = hasTickets;
    btnSelectAll->BackColor = btnSelectAll->Enabled ?
        Color::LightBlue : Color::LightGray;
    btnDeselectAll->BackColor = btnDeselectAll->Enabled ?
        Color::LightGray : Color::LightGray;
}

// === ОБРАБОТЧИКИ СОБЫТИЙ ===

System::Void OrderForm::btnPaySelected_Click(System::Object^ sender, System::EventArgs^ e) {
    try {
        if (currentOrder == nullptr) {
            MessageBox::Show("Ошибка: заказ не загружен!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        // Собираем выбранные билеты
        List<Ticket^>^ ticketsToPay = gcnew List<Ticket^>();
        double totalToPay = 0.0;

        for (int i = 0; i < dgvTickets->Rows->Count; i++) {
            if (dgvTickets->Rows[i]->Cells[0]->Value != nullptr &&
                safe_cast<bool>(dgvTickets->Rows[i]->Cells[0]->Value)) {

                int placeNumber = Convert::ToInt32(dgvTickets->Rows[i]->Cells[2]->Value);
                Ticket^ ticket = currentOrder->FindTicketByPlaceNumber(placeNumber);

                if (ticket != nullptr && ticket->Status != "Оплачен") {
                    ticketsToPay->Add(ticket);
                    totalToPay += ticket->FinalPrice;
                }
            }
        }

        if (ticketsToPay->Count == 0) {
            MessageBox::Show("Выберите билеты для оплаты!", "Внимание",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }

        System::Windows::Forms::DialogResult result = MessageBox::Show(
            String::Format("Оплатить {0} билет(ов) на сумму {1:F2} руб.?",
                ticketsToPay->Count, totalToPay),
            "Подтверждение оплаты",
            MessageBoxButtons::YesNo,
            MessageBoxIcon::Question
        );

        if (result == System::Windows::Forms::DialogResult::Yes) {
            // Помечаем выбранные билеты как оплаченные
            for each (Ticket ^ ticket in ticketsToPay) {
                ticket->MarkAsPaid();
            }

            // Проверяем, все ли билеты оплачены
            bool allPaid = true;
            for each (Ticket ^ ticket in currentOrder->Tickets) {
                if (ticket->Status != "Оплачен") {
                    allPaid = false;
                    break;
                }
            }

            // Если все билеты оплачены, меняем статус заказа
            if (allPaid) {
                currentOrder->PayOrder();
            }

            MessageBox::Show(
                String::Format("Успешно оплачено {0} билет(ов) на сумму {1:F2} руб.",
                    ticketsToPay->Count, totalToPay),
                "Успех",
                MessageBoxButtons::OK,
                MessageBoxIcon::Information
            );

            // Обновляем форму
            LoadTickets();
            InitializeFormData();
            UpdateButtonsState();
        }
    }
    catch (Exception^ ex) {
        MessageBox::Show("Ошибка при оплате билетов: " + ex->Message,
            "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}

System::Void OrderForm::btnRemoveSelected_Click(System::Object^ sender, System::EventArgs^ e) {
    try {
        // Собираем выбранные билеты
        List<Ticket^>^ ticketsToRemove = gcnew List<Ticket^>();

        for (int i = 0; i < dgvTickets->Rows->Count; i++) {
            if (dgvTickets->Rows[i]->Cells[0]->Value != nullptr &&
                safe_cast<bool>(dgvTickets->Rows[i]->Cells[0]->Value)) {

                int placeNumber = Convert::ToInt32(dgvTickets->Rows[i]->Cells[2]->Value);
                Ticket^ ticket = currentOrder->FindTicketByPlaceNumber(placeNumber);

                if (ticket != nullptr) {
                    ticketsToRemove->Add(ticket);
                }
            }
        }

        if (ticketsToRemove->Count == 0) {
            MessageBox::Show("Выберите билеты для удаления!", "Внимание",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }

        System::Windows::Forms::DialogResult result = MessageBox::Show(
            String::Format("Удалить {0} выбранных билет(ов)?", ticketsToRemove->Count),
            "Подтверждение удаления",
            MessageBoxButtons::YesNo,
            MessageBoxIcon::Question
        );

        if (result == System::Windows::Forms::DialogResult::Yes) {
            // Удаляем билеты
            int removedCount = 0;
            for each (Ticket ^ ticket in ticketsToRemove) {
                if (currentOrder->RemoveTicket(ticket)) {
                    removedCount++;
                }
            }

            MessageBox::Show(
                String::Format("Удалено {0} билет(ов) из заказа.", removedCount),
                "Успех",
                MessageBoxButtons::OK,
                MessageBoxIcon::Information
            );

            // Обновляем форму
            LoadTickets();
            InitializeFormData();
            UpdateButtonsState();
        }
    }
    catch (Exception^ ex) {
        MessageBox::Show("Ошибка при удалении билетов: " + ex->Message,
            "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}

System::Void OrderForm::btnSelectAll_Click(System::Object^ sender, System::EventArgs^ e) {
    for (int i = 0; i < dgvTickets->Rows->Count; i++) {
        // Выбираем только неоплаченные билеты
        if (dgvTickets->Rows[i]->Cells[7]->Value != nullptr &&
            safe_cast<String^>(dgvTickets->Rows[i]->Cells[7]->Value) != "Оплачен") {
            dgvTickets->Rows[i]->Cells[0]->Value = true;
        }
    }
    UpdateSelectedCount();
    UpdateButtonsState();
}

System::Void OrderForm::btnDeselectAll_Click(System::Object^ sender, System::EventArgs^ e) {
    for (int i = 0; i < dgvTickets->Rows->Count; i++) {
        dgvTickets->Rows[i]->Cells[0]->Value = false;
    }
    UpdateSelectedCount();
    UpdateButtonsState();
}

System::Void OrderForm::btnBack_Click(System::Object^ sender, System::EventArgs^ e) {
    this->DialogResult = System::Windows::Forms::DialogResult::OK;
    this->Close();
}

System::Void OrderForm::dgvTickets_CellContentClick(System::Object^ sender,
    System::Windows::Forms::DataGridViewCellEventArgs^ e) {

    if (e->ColumnIndex == 0 && e->RowIndex >= 0) {
        // Обновляем счетчик выбранных при клике на галочку
        UpdateSelectedCount();
        UpdateButtonsState();
    }
}