#include "StartForm.h"
#include "Order.hpp"
#include "TripList.hpp"
#include "TimingForm.h"
#include "UserForm.h"

using namespace InfSystBusStation;
using namespace System;
using namespace System::Windows::Forms;

System::Void StartForm::buttonAdmin_Click(System::Object^ sender, System::EventArgs^ e) {
    try {
        // Для админского режима создаем TripList
        TripList^ tripList = gcnew TripList();

        // Открываем TimingForm в режиме админа
        TimingForm^ timingForm = gcnew TimingForm(tripList);
        this->Hide(); // Скрываем стартовую форму
        timingForm->ShowDialog();
        this->Show(); // Показываем снова
    }
    catch (Exception^ ex) {
        MessageBox::Show("Ошибка при открытии режима администратора: " + ex->Message,
            "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}

System::Void StartForm::buttonUser_Click(System::Object^ sender, System::EventArgs^ e) {
    try {
        // Создаем Order для пользовательской сессии
        Order^ userOrder = gcnew Order("Пользователь");

        // Открываем UserForm и передаем Order
        UserForm^ userForm = gcnew UserForm(userOrder);
        this->Hide(); // Скрываем стартовую форму
        userForm->ShowDialog();
        this->Show(); // Показываем снова
    }
    catch (Exception^ ex) {
        MessageBox::Show("Ошибка при открытии пользовательского режима: " + ex->Message,
            "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}

System::Void StartForm::buttonInfo_Click(System::Object^ sender, System::EventArgs^ e) {
    MessageBox::Show(
        "Информационная система автовокзала\n\n"
        "Режимы работы:\n"
        "1. Администратор - управление поездками, автобусами, водителями\n"
        "2. Пользователь - поиск поездок, покупка билетов\n\n"
        "Версия: 1.0\n"
        "Разработчик: Ваше имя",
        "Справка",
        MessageBoxButtons::OK,
        MessageBoxIcon::Information
    );
}

System::Void StartForm::buttonExit_Click(System::Object^ sender, System::EventArgs^ e) {
    System::Windows::Forms::DialogResult result = MessageBox::Show(
        "Вы уверены, что хотите выйти из программы?",
        "Подтверждение выхода",
        MessageBoxButtons::YesNo,
        MessageBoxIcon::Question
    );

    if (result == System::Windows::Forms::DialogResult::Yes) {
        Application::Exit();
    }
}