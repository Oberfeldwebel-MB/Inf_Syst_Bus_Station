#include "TicketSelectionForm.h"
#include "Trip.hpp"
#include "Order.hpp"

using namespace InfSystBusStation;
using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::Collections::Generic;

// Инициализация данных формы
System::Void TicketSelectionForm::InitializeFormData() {
    if (selectedTrip == nullptr) {
        lblTripInfo->Text = "Ошибка: поездка не выбрана!";
        return;
    }

    // Устанавливаем информацию о поездке
    lblTripInfo->Text = String::Format(
        "МАРШРУТ: {0}\n"
        "ДАТА: {1:dd.MM.yyyy}\n"
        "ВРЕМЯ: {2}\n"
        "АВТОБУС: {3}\n"
        "ВОДИТЕЛЬ: {4}",
        selectedTrip->GetRoute(),
        selectedTrip->GetTripDate(),
        selectedTrip->GetTripTime(),
        selectedTrip->GetBus() != nullptr ?
        selectedTrip->GetBus()->GetBrand() + " " + selectedTrip->GetBus()->GetModel() : "Не указан",
        selectedTrip->GetDriver() != nullptr ?
        selectedTrip->GetDriver()->GetFullName() : "Не назначен"
    );

    // Обновляем информацию о цене
    UpdatePriceInfo();

    // ЗАГРУЖАЕМ СВОБОДНЫЕ МЕСТА В COMBOBOX ← ЭТО САМОЕ ВАЖНОЕ!
    LoadAvailableSeats();

    // Обновляем состояние кнопок
    UpdateButtonsState();
}

// Загрузить свободные места в ComboBox
System::Void TicketSelectionForm::LoadAvailableSeats() {
    cmbSeats->Items->Clear();

    if (selectedTrip == nullptr) {
        cmbSeats->Items->Add("Ошибка: поездка не выбрана");
        cmbSeats->Enabled = false;
        return;
    }

    // Получаем список свободных мест из Trip
    List<int>^ availableSeats = selectedTrip->GetAvailableSeats();

    if (availableSeats == nullptr || availableSeats->Count == 0) {
        cmbSeats->Items->Add("Нет свободных мест");
        cmbSeats->Enabled = false;
        lblSelectedSeat->Text = "Все места заняты";
        lblSelectedSeat->ForeColor = Color::Red;
    }
    else {
        for each (int seat in availableSeats) {
            cmbSeats->Items->Add("Место " + seat.ToString());
        }
        if (cmbSeats->Items->Count > 0) {
            cmbSeats->SelectedIndex = 0;
        }
    }
}

// Обновить информацию о цене
System::Void TicketSelectionForm::UpdatePriceInfo() {
    if (selectedTrip == nullptr) {
        lblPriceInfo->Text = "Цена: 0 руб.";
        return;
    }

    int price = selectedTrip->GetPrice();
    lblPriceInfo->Text = String::Format("Цена билета: {0} руб.", price);
}

// Обновить состояние кнопок
System::Void TicketSelectionForm::UpdateButtonsState() {
    bool hasSelection = cmbSeats->SelectedIndex >= 0 && cmbSeats->Enabled;

    btnAddToOrder->Enabled = hasSelection && currentOrder != nullptr;

    if (btnAddToOrder->Enabled) {
        btnAddToOrder->BackColor = Color::LightGreen;
        btnAddToOrder->ForeColor = Color::Black;
    }
    else {
        btnAddToOrder->BackColor = Color::LightGray;
        btnAddToOrder->ForeColor = Color::DarkGray;
    }
}

// === ОБРАБОТЧИКИ СОБЫТИЙ ===

// Изменение выбранного места
System::Void TicketSelectionForm::cmbSeats_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
    if (cmbSeats->SelectedItem != nullptr) {
        String^ selectedItem = cmbSeats->SelectedItem->ToString();
        lblSelectedSeat->Text = selectedItem;
        lblSelectedSeat->ForeColor = Color::DarkBlue;
    }
    UpdateButtonsState();
}

// Добавить в заказ
System::Void TicketSelectionForm::btnAddToOrder_Click(System::Object^ sender, System::EventArgs^ e) {
    try {
        // Проверки
        if (selectedTrip == nullptr) {
            MessageBox::Show("Ошибка: поездка не выбрана!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        if (cmbSeats->SelectedItem == nullptr || !cmbSeats->Enabled) {
            MessageBox::Show("Выберите место!", "Внимание",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }

        // Извлекаем номер места
        String^ selectedItem = cmbSeats->SelectedItem->ToString();
        String^ seatStr = selectedItem->Substring(6); // "Место X" -> "X"
        int seatNumber = Convert::ToInt32(seatStr);

        // Проверяем доступность места
        if (!selectedTrip->IsSeatAvailable(seatNumber)) {
            MessageBox::Show("Это место уже занято! Выберите другое место.",
                "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            LoadAvailableSeats();
            return;
        }

        // Проверяем Order
        if (currentOrder == nullptr) {
            MessageBox::Show("Ошибка: заказ не инициализирован!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        // Проверяем пользователя
        if (currentUser == nullptr) {
            MessageBox::Show("Ошибка: данные пассажира не заполнены!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        // Бронируем место
        if (!selectedTrip->BookSeat(seatNumber)) {
            MessageBox::Show("Не удалось забронировать место!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        // СОЗДАЕМ БИЛЕТ С РЕАЛЬНЫМ ПОЛЬЗОВАТЕЛЕМ
        try {
            Ticket^ ticket = gcnew Ticket(
                seatNumber,          // номер места
                selectedTrip,        // поездка
                currentUser,         // ← РЕАЛЬНЫЙ пользователь из формы
                TicketType::ADULT    // тип билета
            );

            // Добавляем билет в заказ
            currentOrder->AddTicket(ticket);
            ticketAdded = true;

            Console::WriteLine("[TicketSelectionForm] Билет создан:");
            Console::WriteLine("  Место: №{0}", seatNumber);
            Console::WriteLine("  Пассажир: {0}", currentUser->GetFullName());
            Console::WriteLine("  Цена: {0:F2} руб.", ticket->FinalPrice);

            MessageBox::Show(
                String::Format(
                    "✅ Билет успешно добавлен в заказ!\n\n"
                    "Маршрут: {0}\n"
                    "Место: №{1}\n"
                    "Пассажир: {2}\n"
                    "Цена: {3:F2} руб.\n"
                    "Email: {4}\n"
                    "Телефон: {5}\n"
                    "Свободных мест осталось: {6}",
                    selectedTrip->GetRoute(),
                    seatNumber,
                    currentUser->GetFullName(),
                    ticket->FinalPrice,
                    currentUser->GetEmail(),
                    currentUser->PhoneNumber,
                    selectedTrip->GetAvailableSeatsCount()
                ),
                "Успех!",
                MessageBoxButtons::OK,
                MessageBoxIcon::Information
            );

            this->DialogResult = System::Windows::Forms::DialogResult::OK;
            this->Close();

        }
        catch (Exception^ ex) {
            // Отменяем бронирование если ошибка
            selectedTrip->CancelSeatBooking(seatNumber);
            MessageBox::Show("Ошибка при создании билета: " + ex->Message,
                "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            throw;
        }

    }
    catch (Exception^ ex) {
        MessageBox::Show("Ошибка при добавлении билета: " + ex->Message,
            "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}

// Отмена
System::Void TicketSelectionForm::btnCancel_Click(System::Object^ sender, System::EventArgs^ e) {
    this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
    this->Close();
}