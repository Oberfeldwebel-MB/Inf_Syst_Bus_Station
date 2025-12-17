// AdminForm.cpp
#include "AdminForm.h"

using namespace System::Windows::Forms;

namespace InfSystBusStation {

    String^ AdminForm::GetSystemInfo()
    {
        if (admin != nullptr && admin->IsSystemInitialized) {
            return admin->GetSystemStatistics();
        }
        return L"Система инициализирована. Все функции доступны.";
    }

    System::Void AdminForm::buttonSchedule_Click(System::Object^ sender, System::EventArgs^ e)
    {
        try {
            // Получаем TripList из Admin и создаем форму расписания
            TripList^ tripList = admin->TripSystem;
            TimingForm^ timingForm = gcnew TimingForm(tripList);
            timingForm->SetCurrentOrder(nullptr);  // Режим администратора

            this->Hide();  // Скрываем текущую форму
            timingForm->ShowDialog();  // Показываем форму расписания
            this->Show();  // Показываем текущую форму снова
        }
        catch (Exception^ ex) {
            MessageBox::Show("Ошибка при открытии расписания: " + ex->Message,
                "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }

    System::Void AdminForm::buttonDrivers_Click(System::Object^ sender, System::EventArgs^ e)
    {
        try {
            // Получаем DriversList из Admin и создаем форму водителей
            DriversList^ driversList = admin->DriverSystem;
            DriversListForm^ driversForm = gcnew DriversListForm(driversList);

            this->Hide();  // Скрываем текущую форму
            driversForm->ShowDialog();  // Показываем форму водителей
            this->Show();  // Показываем текущую форму снова
        }
        catch (Exception^ ex) {
            MessageBox::Show("Ошибка при открытии списка водителей: " + ex->Message,
                "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }

    System::Void AdminForm::buttonBuses_Click(System::Object^ sender, System::EventArgs^ e)
    {
        try {
            // Получаем BusList из Admin и создаем форму автобусов
            BusList^ busList = admin->BusSystem;
            BusListForm^ busForm = gcnew BusListForm(busList);

            this->Hide();  // Скрываем текущую форму
            busForm->ShowDialog();  // Показываем форму автобусов
            this->Show();  // Показываем текущую форму снова
        }
        catch (Exception^ ex) {
            MessageBox::Show("Ошибка при открытии списка автобусов: " + ex->Message,
                "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }

    System::Void AdminForm::buttonLogout_Click(System::Object^ sender, System::EventArgs^ e)
    {
        // Подтверждение выхода из системы
        if (MessageBox::Show("Вы действительно хотите выйти из системы администратора?",
            "Подтверждение выхода",
            MessageBoxButtons::YesNo,
            MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes)
        {
            this->Close();  // Закрываем форму администратора
        }
    }

    System::Void AdminForm::buttonBack_Click(System::Object^ sender, System::EventArgs^ e)
    {
        try {
            // Подтверждение возврата
            if (MessageBox::Show("Вернуться на стартовую страницу?",
                "Подтверждение",
                MessageBoxButtons::YesNo,
                MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes)
            {
                this->Close();  // Закрываем форму администратора
            }
        }
        catch (Exception^ ex) {
            MessageBox::Show("Ошибка при возврате: " + ex->Message,
                "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }
}