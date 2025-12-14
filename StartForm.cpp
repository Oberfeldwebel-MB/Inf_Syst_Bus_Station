#include "StartForm.h"
#include "AuthForm.h"        
#include "AdminForm.h"
#include "Admin.hpp"

namespace InfSystBusStation {

    System::Void StartForm::buttonAdmin_Click(System::Object^ sender, System::EventArgs^ e)
    {
        try {
            // 1. Показать форму авторизации в режиме администратора
            AuthForm^ authForm = gcnew AuthForm(true);

            if (authForm->ShowDialog() == System::Windows::Forms::DialogResult::OK)
            {
                // Проверяем свойство IsAuthenticated через геттер
                if (authForm->IsAuthenticated)
                {
                    // 2. Получаем данные из формы авторизации
                    String^ userFIO = authForm->UserFIO;
                    String^ userEmail = authForm->UserEmail;

                    MessageBox::Show(
                        String::Format(L"Авторизация успешна!\n\nФИО: {0}\nEmail: {1}\nРежим: Администратор",
                            userFIO, userEmail),
                        L"Успешная авторизация",
                        MessageBoxButtons::OK,
                        MessageBoxIcon::Information);

                    // 3. Пароль по умолчанию (без файлов)
                    String^ adminPassword = "admin123";

                    // 4. Создаем объект администратора
                    Admin^ admin = gcnew Admin(
                        adminPassword,            // password
                        userFIO,                  // fullName
                        "1234",                   // passportSeries
                        "567890",                 // passportNumber
                        50000,                    // salary
                        userEmail                 // email
                    );

                    // 5. Проверяем аутентификацию через email
                    if (admin->Authenticate(userEmail, adminPassword)) {
                        // 6. Создаем и показываем форму администратора
                        AdminForm^ adminForm = gcnew AdminForm(admin);
                        adminForm->Show();
                        this->Hide(); // Скрываем стартовую форму
                    }
                    else {
                        MessageBox::Show("Ошибка аутентификации! Неверный email или пароль.",
                            "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
                    }
                }
                else
                {
                    MessageBox::Show("Авторизация не пройдена.",
                        "Информация", MessageBoxButtons::OK, MessageBoxIcon::Information);
                }
            }
            else
            {
                MessageBox::Show("Авторизация отменена.",
                    "Информация", MessageBoxButtons::OK, MessageBoxIcon::Information);
            }

            delete authForm;
        }
        catch (Exception^ ex) {
            MessageBox::Show("Ошибка при входе администратора: " + ex->Message,
                "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }

    System::Void StartForm::buttonUser_Click(System::Object^ sender, System::EventArgs^ e)
    {
        //try {
        //    // 1. Показать форму авторизации в режиме пользователя
        //    AuthForm^ authForm = gcnew AuthForm(false);

        //    if (authForm->ShowDialog() == System::Windows::Forms::DialogResult::OK)
        //    {
        //        // Проверяем свойство IsAuthenticated
        //        if (authForm->IsAuthenticated)
        //        {
        //            // 2. Получаем данные из формы авторизации
        //            String^ userFIO = authForm->UserFIO;
        //            String^ userEmail = authForm->UserEmail;

        //            MessageBox::Show(
        //                String::Format(L"Добро пожаловать, {0}!\n\nEmail: {1}\nРежим: Пользователь",
        //                    userFIO, userEmail),
        //                L"Успешный вход",
        //                MessageBoxButtons::OK,
        //                MessageBoxIcon::Information);

        //            // 3. Здесь можно создать форму пользователя
        //            MessageBox::Show("Режим пользователя (пассажира)\n\n"
        //                "В этом режиме вы можете:\n"
        //                "- Просматривать расписание\n"
        //                "- Покупать билеты\n"
        //                "- Просматривать информацию о рейсах\n"
        //                "- Отслеживать статус поездок\n\n"
        //                "ФИО: " + userFIO + "\n" +
        //                "Email: " + userEmail,
        //                "Режим пользователя", MessageBoxButtons::OK, MessageBoxIcon::Information);
        //        }
        //        else
        //        {
        //            MessageBox::Show("Вход не пройден.",
        //                "Информация", MessageBoxButtons::OK, MessageBoxIcon::Information);
        //        }
        //    }
        //    else
        //    {
        //        MessageBox::Show("Вход отменен.",
        //            "Информация", MessageBoxButtons::OK, MessageBoxIcon::Information);
        //    }

        //    delete authForm;
        //}
        //catch (Exception^ ex) {
        //    MessageBox::Show("Ошибка при входе пользователя: " + ex->Message,
        //        "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        //}
    }

    System::Void StartForm::buttonInfo_Click(System::Object^ sender, System::EventArgs^ e)
    {
        MessageBox::Show(
            "=== ИНФОРМАЦИОННАЯ СПРАВКА ===\n\n"
            "Система управления автобусным парком\n"
            "Версия: 2.0\n\n"
            "Режимы работы:\n"
            "1. Администратор - полный доступ к системе\n"
            "   - Требует ввода ФИО, email и пароля\n"
            "   - Доступ к управлению автобусами, водителями, расписанием\n"
            "   - Просмотр статистики и отчетов\n\n"
            "2. Пользователь - доступ к расписанию и покупке билетов\n"
            "   - Требует ввода ФИО и email\n"
            "   - Просмотр расписания рейсов\n"
            "   - Покупка билетов\n"
            "   - Отслеживание статуса поездок\n\n"
            "Формат ввода данных:\n"
            "- ФИО: А.А.Рогатин или А.А.Р.\n"
            "- Email: example@mail.ru\n"
            "- Пароль администратора: admin123\n\n"
            "По умолчанию пароль администратора: admin123",
            "Справка", MessageBoxButtons::OK, MessageBoxIcon::Information);
    }

    System::Void StartForm::buttonExit_Click(System::Object^ sender, System::EventArgs^ e)
    {
        System::Windows::Forms::DialogResult result = MessageBox::Show(
            "Вы уверены, что хотите выйти из программы?",
            "Подтверждение выхода",
            MessageBoxButtons::YesNo,
            MessageBoxIcon::Question);

        if (result == System::Windows::Forms::DialogResult::Yes) {
            Application::Exit();
        }
    }
}