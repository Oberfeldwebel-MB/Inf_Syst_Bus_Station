#include "AuthForm.h"
#include "ChangePasswordForm.h"
#include "StartForm.h"
#include "AdminForm.h"

namespace InfSystBusStation {

	// Статическая переменная для хранения пароля (вместо файла)
	static String^ currentAdminPassword = "admin123";

	System::Void AuthForm::back_from_pass_Click(System::Object^ sender, System::EventArgs^ e) {
		// Возвращаемся на стартовую форму
		this->DialogResult = Windows::Forms::DialogResult::Cancel;
		this->Close();
	}

	System::Void AuthForm::next_pass_Click(System::Object^ sender, System::EventArgs^ e) {
		// Проверяем пароль (без учета регистра)
		if (currentAdminPassword->ToLower() == check_pass_box->Text->Trim()->ToLower()) {
			_authenticated = true;
			MessageBox::Show("Авторизация успешна!\nДоступ к функциям администратора разрешен.",
				"Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);

			// Закрываем форму с результатом OK
			this->DialogResult = Windows::Forms::DialogResult::OK;
			this->Close();

			// После закрытия AuthForm, StartForm откроет AdminForm
		}
		else {
			MessageBox::Show("Неверный пароль. Повторите попытку.",
				"Ошибка авторизации", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			check_pass_box->Clear();
			check_pass_box->Focus();
		}
	}

	System::Void AuthForm::change_pass_Click(System::Object^ sender, System::EventArgs^ e) {
		// Создаем диалог для смены пароля
		Form^ passwordDialog = gcnew Form();
		passwordDialog->Text = L"Смена пароля администратора";
		passwordDialog->Size = Drawing::Size(350, 220);
		passwordDialog->FormBorderStyle = FormBorderStyle::FixedDialog;
		passwordDialog->StartPosition = FormStartPosition::CenterParent;
		passwordDialog->MaximizeBox = false;
		passwordDialog->MinimizeBox = false;

		// Создаем элементы управления
		Label^ lblCurrent = gcnew Label();
		lblCurrent->Text = L"Текущий пароль:";
		lblCurrent->Location = Drawing::Point(30, 30);
		lblCurrent->Size = Drawing::Size(120, 20);

		TextBox^ txtCurrent = gcnew TextBox();
		txtCurrent->Location = Drawing::Point(160, 27);
		txtCurrent->Size = Drawing::Size(150, 22);
		txtCurrent->PasswordChar = '*';

		Label^ lblNew = gcnew Label();
		lblNew->Text = L"Новый пароль:";
		lblNew->Location = Drawing::Point(30, 70);
		lblNew->Size = Drawing::Size(120, 20);

		TextBox^ txtNew = gcnew TextBox();
		txtNew->Location = Drawing::Point(160, 67);
		txtNew->Size = Drawing::Size(150, 22);
		txtNew->PasswordChar = '*';

		Label^ lblConfirm = gcnew Label();
		lblConfirm->Text = L"Подтверждение:";
		lblConfirm->Location = Drawing::Point(30, 110);
		lblConfirm->Size = Drawing::Size(120, 20);

		TextBox^ txtConfirm = gcnew TextBox();
		txtConfirm->Location = Drawing::Point(160, 107);
		txtConfirm->Size = Drawing::Size(150, 22);
		txtConfirm->PasswordChar = '*';

		Button^ btnOk = gcnew Button();
		btnOk->Text = L"Сменить";
		btnOk->Location = Drawing::Point(80, 150);
		btnOk->Size = Drawing::Size(80, 30);
		btnOk->BackColor = Drawing::Color::LightGreen;
		btnOk->FlatStyle = FlatStyle::Flat;

		Button^ btnCancel = gcnew Button();
		btnCancel->Text = L"Отмена";
		btnCancel->Location = Drawing::Point(180, 150);
		btnCancel->Size = Drawing::Size(80, 30);
		btnCancel->BackColor = Drawing::Color::LightCoral;
		btnCancel->FlatStyle = FlatStyle::Flat;
		btnCancel->DialogResult = DialogResult::Cancel;

		// Обработчик для кнопки OK
		btnOk->Click += gcnew System::EventHandler([=](System::Object^ sender2, System::EventArgs^ e2) {
			// Проверяем текущий пароль
			if (txtCurrent->Text->Trim()->ToLower() != currentAdminPassword->ToLower()) {
				MessageBox::Show("Неверный текущий пароль!", "Ошибка",
					MessageBoxButtons::OK, MessageBoxIcon::Warning);
				txtCurrent->Focus();
				return;
			}

			if (String::IsNullOrWhiteSpace(txtNew->Text)) {
				MessageBox::Show("Новый пароль не может быть пустым!", "Ошибка",
					MessageBoxButtons::OK, MessageBoxIcon::Warning);
				txtNew->Focus();
				return;
			}

			if (txtNew->Text->Length < 6) {
				MessageBox::Show("Новый пароль должен содержать минимум 6 символов!", "Ошибка",
					MessageBoxButtons::OK, MessageBoxIcon::Warning);
				txtNew->Focus();
				return;
			}

			if (txtNew->Text != txtConfirm->Text) {
				MessageBox::Show("Пароли не совпадают!", "Ошибка",
					MessageBoxButtons::OK, MessageBoxIcon::Warning);
				txtConfirm->Focus();
				return;
			}

			// Меняем пароль
			currentAdminPassword = txtNew->Text;
			MessageBox::Show("Пароль успешно изменен!\nНовый пароль: " + currentAdminPassword,
				"Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);

			passwordDialog->DialogResult = DialogResult::OK;
			passwordDialog->Close();
			});

		// Добавляем элементы на форму
		passwordDialog->Controls->Add(lblCurrent);
		passwordDialog->Controls->Add(txtCurrent);
		passwordDialog->Controls->Add(lblNew);
		passwordDialog->Controls->Add(txtNew);
		passwordDialog->Controls->Add(lblConfirm);
		passwordDialog->Controls->Add(txtConfirm);
		passwordDialog->Controls->Add(btnOk);
		passwordDialog->Controls->Add(btnCancel);

		// Показываем диалог
		if (passwordDialog->ShowDialog() == DialogResult::OK) {
			// Обновляем поле ввода
			check_pass_box->Clear();
			check_pass_box->Focus();
		}

		delete passwordDialog;
	}

	System::Void AuthForm::ChangePassword(String^ newPassword) {
		// Просто обновляем статическую переменную
		currentAdminPassword = newPassword;
		MessageBox::Show("Пароль успешно изменен!",
			"Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
	}
}