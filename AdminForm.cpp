// AdminForm.cpp
#include "AdminForm.h"

using namespace System::Windows::Forms;

namespace InfSystBusStation {

    System::Void AdminForm::buttonSchedule_Click(System::Object^ sender, System::EventArgs^ e)
    {
        try {
            TripList^ tripList = admin->TripSystem;
            BusList^ busList = admin->BusSystem;           
            DriversList^ driverList = admin->DriverSystem; 

            // Создаем TimingForm со ВСЕМИ тремя параметрами
            TimingForm^ timingForm = gcnew TimingForm(tripList, busList, driverList, true);
            timingForm->SetCurrentOrder(nullptr);  // Режим администратора

            this->Hide();  
            timingForm->ShowDialog(); 
            this->Show();  
        }
        catch (Exception^ ex) {
            MessageBox::Show("Ошибка при открытии расписания: " + ex->Message,
                "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }

    System::Void AdminForm::buttonDrivers_Click(System::Object^ sender, System::EventArgs^ e)
    {
        try {
            
            DriversList^ driversList = admin->DriverSystem;
            DriversListForm^ driversForm = gcnew DriversListForm(driversList);

            this->Hide();  
            driversForm->ShowDialog();  
            this->Show();  
        }
        catch (Exception^ ex) {
            MessageBox::Show("Ошибка при открытии списка водителей: " + ex->Message,
                "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }

    System::Void AdminForm::buttonBuses_Click(System::Object^ sender, System::EventArgs^ e)
    {
        try {
            
            BusList^ busList = admin->BusSystem;
            BusListForm^ busForm = gcnew BusListForm(busList);

            this->Hide();  
            busForm->ShowDialog();  
            this->Show();  
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
            this->Close();  
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
                // Извлекаем все обновленные списки из admin
                TripList^ updatedTripList = admin->TripSystem;
                BusList^ updatedBusList = admin->BusSystem;
                DriversList^ updatedDriversList = admin->DriverSystem;


                this->Close();

                StartForm^ startForm = gcnew StartForm(admin, updatedBusList,
                    updatedDriversList, updatedTripList);


                startForm->Show();
            }
        }
        catch (Exception^ ex) {
            MessageBox::Show("Ошибка при возврате: " + ex->Message,
                "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }
}