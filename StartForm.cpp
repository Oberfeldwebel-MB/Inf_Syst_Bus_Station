// StartForm.cpp
#include "StartForm.h"
#include "AdminLoginForm.h"
#include "AdminForm.h"
#include "TimingForm.h"

using namespace System::Windows::Forms;  // Для MessageBox

namespace InfSystBusStation {

    System::Void StartForm::buttonAdmin_Click(System::Object^ sender, System::EventArgs^ e)
    {
        try {
            // Создаем форму входа администратора и передаем Admin
            AdminLoginForm^ adminLoginForm = gcnew AdminLoginForm(admin);

            if (adminLoginForm->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
                // Если вход успешен, открываем панель администратора
                AdminForm^ adminForm = gcnew AdminForm(admin);
                this->Hide();  // Скрываем стартовую форму
                adminForm->ShowDialog();  // Показываем форму администратора
                this->Show();  // Показываем стартовую форму снова
            }
        }
        catch (Exception^ ex) {
            MessageBox::Show("Ошибка при входе администратора: " + ex->Message,
                "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }

    System::Void StartForm::buttonUser_Click(System::Object^ sender, System::EventArgs^ e)
    {
        try {
            // Создаем форму расписания для пользователя, передаем TripList
            TimingForm^ timingForm = gcnew TimingForm(tripList);
            timingForm->SetCurrentOrder(nullptr);  // Режим пользователя (без текущего заказа)

            this->Hide();  // Скрываем стартовую форму
            timingForm->ShowDialog();  // Показываем расписание
            this->Show();  // Возвращаемся на стартовую форму
        }
        catch (Exception^ ex) {
            MessageBox::Show("Ошибка при открытии расписания: " + ex->Message,
                "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
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