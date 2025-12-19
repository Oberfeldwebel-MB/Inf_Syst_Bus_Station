// StartForm.cpp
#include "StartForm.h"
#include "AdminLoginForm.h"
#include "AdminForm.h"
#include "PassengerForm.h"

using namespace System::Windows::Forms;  // Для MessageBox

namespace InfSystBusStation {

    System::Void StartForm::buttonAdmin_Click(System::Object^ sender, System::EventArgs^ e)
    {
        try {
            // Создаем форму входа администратора
            AdminLoginForm^ adminLoginForm = gcnew AdminLoginForm(admin);

            adminLoginForm->Show();

            // Скрываем стартовую форму
            this->Hide();

            

        }
        catch (Exception^ ex) {
            MessageBox::Show("Ошибка при входе администратора: " + ex->Message,
                "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            
        }
    }

    System::Void StartForm::buttonUser_Click(System::Object^ sender, System::EventArgs^ e)
    {
        try {
            // Открываем форму регистрации пассажира
            PassengerForm^ passengerForm = gcnew PassengerForm(tripList, busList, driversList);

            this->Hide();  // Скрываем стартовую форму

            if (passengerForm->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
                // Если регистрация успешна, пассажир переходит в UserForm через PassengerForm
                // PassengerForm сам откроет UserForm после успешной регистрации
            }

            this->Show();  // Показываем стартовую форму снова
        }
        catch (Exception^ ex) {
            MessageBox::Show("Ошибка при открытии регистрации: " + ex->Message,
                "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            this->Show();  // В случае ошибки показываем стартовую форму
        }
    }

    System::Void StartForm::buttonInfo_Click(System::Object^ sender, System::EventArgs^ e)
    {
        // Показываем информацию о системе
        String^ infoText =
            L"=== ИНФОРМАЦИОННАЯ СИСТЕМА АВТОБУСНОГО АВТОПАРКА ===\n\n"
            L"Версия: 1.0\n"
            L"Разработчик: Студенческая группа\n"
            L"Дисциплина: Программирование\n"
            L"Семестр: 3\n\n"
            L"Функционал:\n"
            L"• Режим администратора - управление системой\n"
            L"• Режим пользователя - просмотр и покупка билетов\n"
            L"• Управление автобусами, водителями, расписанием\n\n"
            L"Для начала работы выберите режим работы.";

        MessageBox::Show(infoText, "Справка о системе",
            MessageBoxButtons::OK, MessageBoxIcon::Information);
    }

    System::Void StartForm::buttonExit_Click(System::Object^ sender, System::EventArgs^ e)
    {
        // Подтверждение выхода
        if (MessageBox::Show("Вы действительно хотите выйти из программы?",
            "Подтверждение выхода",
            MessageBoxButtons::YesNo,
            MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes)
        {
            Application::Exit();  // Завершаем приложение
        }
    }
}