#include "UserForm.h"
#include "TimingForm.h"
#include "OrdersForm.h"

using namespace InfSystBusStation;
using namespace System;
using namespace System::Windows::Forms;

// Обновление информации о заказе
void UserForm::UpdateOrderInfo() {
    if (currentUser != nullptr && currentUser->CurrentOrder != nullptr) {
        Order^ order = currentUser->CurrentOrder;
        lblOrderInfo->Text = String::Format("В вашем заказе: {0} билетов на сумму {1:F2} руб.",
            order->TicketCount, order->TotalPrice);
    }
    else {
        lblOrderInfo->Text = "У вас нет активного заказа";
    }
}

// Обработчик кнопки "Выбрать поездку"
System::Void UserForm::btnSelectTrip_Click(System::Object^ sender, System::EventArgs^ e) {
    // Проверяем или создаем заказ
    if (currentUser->CurrentOrder == nullptr) {
        currentUser->CurrentOrder = gcnew Order();
    }

    TimingForm^ timingForm = gcnew TimingForm(tripList, busList, driverList, false);
    timingForm->SetCurrentOrder(currentUser->CurrentOrder);
    timingForm->SetCurrentUser(currentUser);

    this->Hide();
    timingForm->ShowDialog();
    this->Show();
    UpdateOrderInfo();
}

// Обработчик кнопки "Мои билеты"
System::Void UserForm::btnMyTickets_Click(System::Object^ sender, System::EventArgs^ e) {
    // OrderForm работает напрямую с Order
    if (currentUser->CurrentOrder != nullptr) {
        OrderForm^ orderForm = gcnew OrderForm(currentUser->CurrentOrder);
        orderForm->ShowDialog();
        UpdateOrderInfo();
    }
}

// Обработчик кнопки "Выйти из системы"
System::Void UserForm::btnBack_Click(System::Object^ sender, System::EventArgs^ e) {
    // Подтверждение выхода
    if (MessageBox::Show("Вы действительно хотите выйти из системы?",
        "Подтверждение выхода",
        MessageBoxButtons::YesNo,
        MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes) {

        this->DialogResult = System::Windows::Forms::DialogResult::OK;
        this->Close();
    }
}