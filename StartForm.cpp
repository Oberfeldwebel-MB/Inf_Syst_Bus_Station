#include "StartForm.h"

namespace InfSystBusStation {

    // === РЕАЛИЗАЦИЯ IAppForm ===

    // 1. Открыть новую форму и закрыть текущую
    void StartForm::OpenAndClose(Form^ nextForm)
    {
        if (nextForm != nullptr)
        {
            nextForm->Show();
            this->Close();
        }
    }

    // 2. Открыть модальное окно
    DialogResult StartForm::OpenModal(Form^ dialogForm)
    {
        if (dialogForm != nullptr)
        {
            this->Hide();  // Скрываем текущую форму

            // Используем полное имя типа
            System::Windows::Forms::DialogResult result = dialogForm->ShowDialog(this);

            this->Show();  // Показываем текущую форму снова
            return result;
        }
    }

    
    void StartForm::GoBack()
    {
        // Стартовая форма - закрываем приложение
        Application::Exit();
    }

    // === Обработчики событий ===

    System::Void StartForm::buttonAdmin_Click(System::Object^ sender, System::EventArgs^ e)
    {
        

        MessageBox::Show("Функция администратора", "Информация");
    }

    System::Void StartForm::buttonUser_Click(System::Object^ sender, System::EventArgs^ e)
    {
        

        MessageBox::Show("Функция пользователя", "Информация");
    }

    System::Void StartForm::buttonInfo_Click(System::Object^ sender, System::EventArgs^ e)
    {
        MessageBox::Show("Информационная справка\n\nСистема управления автобусным парком",
            "Справка");
    }

    System::Void StartForm::buttonExit_Click(System::Object^ sender, System::EventArgs^ e)
    {
        GoBack();
    }
}