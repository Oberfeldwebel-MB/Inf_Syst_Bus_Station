#include "ChangePasswordForm.h"

namespace InfSystBusStation {

	System::Void ChangePasswordForm::back_from_ch_pass_Click(System::Object^ sender, System::EventArgs^ e) {
		// Просто закрываем форму без сохранения
		this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
		this->Close();
	}

	System::Void ChangePasswordForm::change_pass_but_Click(System::Object^ sender, System::EventArgs^ e) {
		// Проверяем ответ на секретный вопрос
		if (check_quest_box->Text->Trim()->ToLower() == secret_answer->ToLower()) {
			// Проверяем новый пароль
			if (String::IsNullOrWhiteSpace(new_pass_box->Text)) {
				MessageBox::Show("Пароль не может быть пустым!",
					"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				new_pass_box->Focus();
				return;
			}

			if (new_pass_box->Text->Length < 6) {
				MessageBox::Show("Пароль должен содержать минимум 6 символов!",
					"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				new_pass_box->Focus();
				return;
			}

			// Пароль валиден
			MessageBox::Show("Пароль успешно изменен!\nНовый пароль: " + new_pass_box->Text,
				"Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);

			this->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->Close();
		}
		else {
			MessageBox::Show("Ответ на секретный вопрос неверен. Попробуйте снова.",
				"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			check_quest_box->Clear();
			check_quest_box->Focus();
		}
	}
}