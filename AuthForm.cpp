#include "AuthForm.h"
#include "ChangePasswordForm.h"
#include "StartForm.h"

namespace InfSystBusStation {

	System::Void AuthForm::back_from_pass_Click(System::Object^ sender, System::EventArgs^ e) {
		// Возвращаемся на стартовую форму
		this->DialogResult = Windows::Forms::DialogResult::Cancel;
		this->Close();
	}

	System::Void AuthForm::next_pass_Click(System::Object^ sender, System::EventArgs^ e) {
		// Инициализируем файл пароля, если его нет
		InitializePasswordFile();

		// Читаем пароль из файла
		String^ passwordFile = "admin_password.txt";
		String^ admin_password;

		try {
			admin_password = System::IO::File::ReadAllText(passwordFile);
			admin_password = admin_password->Trim();
		}
		catch (Exception^ ex) {
			MessageBox::Show("Ошибка чтения файла пароля: " + ex->Message,
				"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		// Проверяем пароль (без учета регистра)
		if (admin_password->ToLower() == check_pass_box->Text->Trim()->ToLower()) {
			_authenticated = true;
			MessageBox::Show("Авторизация успешна!\nДоступ к функциям администратора разрешен.",
				"Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);

			// Закрываем форму с результатом OK
			this->DialogResult = Windows::Forms::DialogResult::OK;
			this->Close();

			// Здесь можно открыть форму администратора
			// Например: AdminForm^ adminForm = gcnew AdminForm();
			// adminForm->Show();
		}
		else {
			MessageBox::Show("Неверный пароль. Повторите попытку.",
				"Ошибка авторизации", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			check_pass_box->Clear();
			check_pass_box->Focus();
		}
	}

	System::Void AuthForm::change_pass_Click(System::Object^ sender, System::EventArgs^ e) {
		// Открываем форму смены пароля
		ChangePasswordForm^ change_pass_form = gcnew ChangePasswordForm();

		// Можем изменить секретный вопрос для автопарка
		change_pass_form->SecretAnswer = L"Мерседес"; // Или "автобус", "газель" и т.д.

		if (change_pass_form->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			// Меняем пароль
			ChangePassword(change_pass_form->NewPassword);

			// Очищаем поле ввода
			check_pass_box->Clear();
			check_pass_box->Focus();
		}

		delete change_pass_form;
	}

	System::Void AuthForm::InitializePasswordFile() {
		String^ passwordFile = "admin_password.txt";
		String^ defaultPassword = "admin123"; // Пароль по умолчанию

		try {
			// Если файл не существует — создаём его
			if (!System::IO::File::Exists(passwordFile)) {
				System::IO::StreamWriter^ writer = gcnew System::IO::StreamWriter(
					passwordFile,
					false, // Не дописывать, а перезаписать
					System::Text::Encoding::UTF8
				);

				writer->Write(defaultPassword); // Записываем пароль
				writer->Close(); // Закрываем файл

				MessageBox::Show("Создан файл пароля.\nПароль по умолчанию: " + defaultPassword +
					"\nСекретный вопрос: 'Какая ваша любимая марка автомобилей?'\nОтвет: 'Мерседес'",
					"Информация", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
		}
		catch (Exception^ ex) {
			MessageBox::Show("Ошибка при создании файла пароля: " + ex->Message,
				"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

	System::Void AuthForm::ChangePassword(String^ newPassword) {
		String^ passwordFile = "admin_password.txt";

		try {
			// 1. Проверяем, существует ли файл
			if (!File::Exists(passwordFile)) {
				InitializePasswordFile();
			}

			// 2. Валидация нового пароля
			if (String::IsNullOrWhiteSpace(newPassword)) {
				MessageBox::Show("Пароль не может быть пустым!",
					"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			if (newPassword->Length < 6) {
				MessageBox::Show("Пароль должен содержать минимум 6 символов!",
					"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			// 3. Записываем новый пароль
			StreamWriter^ writer = gcnew StreamWriter(passwordFile, false, Encoding::UTF8);
			writer->Write(newPassword);
			writer->Close();

			// 4. Проверяем, что запись прошла успешно
			String^ savedPassword = File::ReadAllText(passwordFile)->Trim();
			if (savedPassword != newPassword->Trim()) {
				throw gcnew Exception("Ошибка записи нового пароля");
			}

			MessageBox::Show("Пароль успешно изменен!",
				"Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
		catch (Exception^ ex) {
			MessageBox::Show("Ошибка при изменении пароля: " + ex->Message,
				"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}
}