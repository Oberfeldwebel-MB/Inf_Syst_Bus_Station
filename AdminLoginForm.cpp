// AdminLoginForm.cpp
#include "AdminLoginForm.h"
#include "AdminForm.h"
#include "ChangePasswordForm.h"

using namespace System::Windows::Forms;

namespace InfSystBusStation {

    System::Void AdminLoginForm::LoginButton_Click(System::Object^ sender, System::EventArgs^ e)
    {
        try {
            // Получаем данные из формы
            String^ fullName = PassFioBox->Text;
            String^ gender = "";
            if (PolPassBox->GetItemChecked(0)) gender = "Мужской";
            else if (PolPassBox->GetItemChecked(1)) gender = "Женский";

            String^ passport = PassportPassBox->Text;
            String^ email = EMAILBox->Text;
            String^ phone = PhonePassBox->Text;
            String^ password = textBoxPassword->Text;

            // Проверяем обязательные поля
            if (String::IsNullOrEmpty(fullName) ||
                String::IsNullOrEmpty(gender) ||
                String::IsNullOrEmpty(passport) ||
                String::IsNullOrEmpty(email) ||
                String::IsNullOrEmpty(password)) {

                MessageBox::Show("Заполните все обязательные поля", "Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }

            // Разбираем паспорт на серию и номер
            if (!PassportPassBox->MaskCompleted) {
                MessageBox::Show("Паспортные данные заполнены не полностью", "Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Warning);
                PassportPassBox->Focus();
                return;
            }

            if (admin->Authenticate(email, password)) {
                MessageBox::Show("Успешный вход в систему", "Успех",
                    MessageBoxButtons::OK, MessageBoxIcon::Information);

                isAuthenticated = true;

                // Создаем и показываем форму администратора
                AdminForm^ adminForm = gcnew AdminForm(admin);

                // Закрываем форму входа
                this->DialogResult = System::Windows::Forms::DialogResult::OK;
                this->Hide();

                adminForm->ShowDialog();

                // После закрытия AdminForm
                this->Close();
            }
            else {
                MessageBox::Show("Неверный email или пароль", "Ошибка аутентификации",
                    MessageBoxButtons::OK, MessageBoxIcon::Error);
                textBoxPassword->Clear();
                textBoxPassword->Focus();
            }

        }
        catch (Exception^ ex) {
            MessageBox::Show("Ошибка при входе: " + ex->Message, "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }

    System::Void AdminLoginForm::BackButton_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
        this->Close();
    }

    System::Void AdminLoginForm::ChangePasswordButton_Click(System::Object^ sender, System::EventArgs^ e)
    {
        try {
            String^ email = EMAILBox->Text->Trim();

            if (String::IsNullOrEmpty(email)) {
                MessageBox::Show("Введите email для смены пароля", "Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }


            ChangePasswordForm^ changePassForm = gcnew ChangePasswordForm(admin);

            if (changePassForm->ShowDialog() == System::Windows::Forms::DialogResult::OK) {

                textBoxPassword->Text = changePassForm->NewPassword;

                MessageBox::Show("Пароль успешно изменен", "Успех",
                    MessageBoxButtons::OK, MessageBoxIcon::Information);
            }
        }
        catch (Exception^ ex) {
            MessageBox::Show("Ошибка при смене пароля: " + ex->Message, "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }
}