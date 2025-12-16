#include "UserForm.h"
#include "TripList.hpp"
#include "TimingForm.h"
#include "OrdersForm.h"

using namespace InfSystBusStation;
using namespace System;
using namespace System::Windows::Forms;

void UserForm::UpdateOrderInfo() {
    if (currentOrder != nullptr) {
        lblOrderInfo->Text = String::Format("В вашем заказе: {0} билетов на сумму {1:F2} руб.",
            currentOrder->TicketCount,
            currentOrder->TotalPrice);

        // Включаем/выключаем кнопку "Мои билеты" в зависимости от наличия билетов
        btnMyTickets->Enabled = (currentOrder->TicketCount > 0);
    }
}

System::Void UserForm::btnSelectTrip_Click(System::Object^ sender, System::EventArgs^ e) {
    try {
        // Создаем TripList
        TripList^ tripList = gcnew TripList();

        // Открываем TimingForm
        TimingForm^ timingForm = gcnew TimingForm(tripList);

        // Передаем Order в TimingForm
        timingForm->SetCurrentOrder(currentOrder);

        this->Hide(); // Скрываем UserForm
        timingForm->ShowDialog();
        this->Show(); // Показываем снова

        // Обновляем информацию о заказе
        UpdateOrderInfo();
    }
    catch (Exception^ ex) {
        MessageBox::Show("Ошибка: " + ex->Message,
            "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}

System::Void UserForm::btnMyTickets_Click(System::Object^ sender, System::EventArgs^ e) {
    try {
        // Открываем OrderForm и передаем Order
        OrderForm^ orderForm = gcnew OrderForm(currentOrder);
        orderForm->ShowDialog();

        // Обновляем информацию о заказе
        UpdateOrderInfo();
    }
    catch (Exception^ ex) {
        MessageBox::Show("Ошибка: " + ex->Message,
            "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}

System::Void UserForm::btnBack_Click(System::Object^ sender, System::EventArgs^ e) {
    this->DialogResult = System::Windows::Forms::DialogResult::OK;
    this->Close();
}