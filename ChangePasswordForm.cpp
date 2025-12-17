// ChangePasswordForm.cpp
#include "ChangePasswordForm.h"

using namespace System::Windows::Forms;

namespace InfSystBusStation {

    System::Void ChangePasswordForm::back_from_ch_pass_Click(System::Object^ sender, System::EventArgs^ e)
    {
        // Просто закрываем форму без сохранения
        this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
        this->Close();
    }

    System::Void ChangePasswordForm::change_pass_but_Click(System::Object^ sender, System::EventArgs^ e)
    {
        try {
            // Проверяем ответ на секретный вопрос
            if (check_quest_box->Text->Trim()->ToLower() == secret_answer->ToLower()) {
                // Проверяем новый пароль
                String^ newPassword = new_pass_box->Text;

                if (String::IsNullOrWhiteSpace(newPassword)) {
                    MessageBox::Show("Пароль не может быть пустым!",
                        "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                    new_pass_box->Focus();
                    return;
                }

                if (newPassword->Length < 6) {
                    MessageBox::Show("Пароль должен содержать минимум 6 символов!",
                        "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                    new_pass_box->Focus();
                    return;
                }

                // Если у нас есть доступ к объекту Admin, меняем пароль
                if (admin != nullptr) {
                    try {
                        // Используем новый метод SetPassword
                        admin->SetPassword(newPassword);

                        MessageBox::Show("Пароль успешно изменен!",
                            "Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);

                        this->DialogResult = System::Windows::Forms::DialogResult::OK;
                        this->Close();
                    }
                    catch (Exception^ ex) {
                        MessageBox::Show("Ошибка при изменении пароля в системе: " + ex->Message,
                            "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
                    }
                }
                else {
                    // Если Admin не передан, просто показываем сообщение
                    MessageBox::Show("Новый пароль: " + newPassword,
                        "Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);

                    this->DialogResult = System::Windows::Forms::DialogResult::OK;
                    this->Close();
                }
            }
            else {
                MessageBox::Show("Ответ на секретный вопрос неверен. Попробуйте снова.",
                    "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
                check_quest_box->Clear();
                check_quest_box->Focus();
            }
        }
        catch (Exception^ ex) {
            MessageBox::Show("Ошибка при смене пароля: " + ex->Message,
                "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }
}