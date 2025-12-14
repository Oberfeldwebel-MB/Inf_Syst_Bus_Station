#include "AuthForm.h"

namespace InfSystBusStation {

	System::Void AuthForm::InitializeFormBasedOnMode()
	{
		if (!_isAdminMode)
		{
			// Режим обычного пользователя - скрываем элементы пароля
			label1->Visible = false;
			check_pass_box->Visible = false;
			change_pass->Visible = false;

			// Меняем текст кнопки и положение
			next_pass->Text = L"Продолжить";
			next_pass->Location = System::Drawing::Point(167, 200);

			// Увеличиваем размер формы для лучшего отображения
			this->ClientSize = System::Drawing::Size(443, 280);

			// Меняем заголовок формы
			this->Text = L"Регистрация пользователя - Автобусный парк";

			// Изменяем подсказки
			labelFIO->Text = L"Введите ваше ФИО (формат А.А.Рогатин)";
			labelInfo->Text = L"Пример: А.А.Рогатин или А.А.Р.";
			labelEmail->Text = L"Введите ваш email";
			labelEmailInfo->Text = L"Пример: example@mail.ru или user@gmail.com";
		}
		else
		{
			// Режим администратора - показываем все элементы
			label1->Visible = true;
			check_pass_box->Visible = true;
			change_pass->Visible = true;

			// Возвращаем стандартные настройки
			next_pass->Text = L"Войти";
			next_pass->Location = System::Drawing::Point(167, 280);

			this->ClientSize = System::Drawing::Size(443, 380);

			this->Text = L"Авторизация администратора - Автобусный парк";

			labelFIO->Text = L"Введите ФИО администратора (формат А.А.Рогатин)";
			labelInfo->Text = L"Пример: А.А.Рогатин или А.А.Р.";
			labelEmail->Text = L"Введите email администратора";
			labelEmailInfo->Text = L"Пример: admin@buspark.ru или admin@gmail.com";
		}
	}

	System::Void AuthForm::ValidateFIOFormat()
	{
		String^ fio = fio_textbox->Text->Trim();

		if (String::IsNullOrEmpty(fio))
		{
			fio_textbox->BackColor = System::Drawing::Color::White;
			return;
		}

		// Паттерн для формата: А.А.Рогатин или А.А.Р.
		// Допускаются русские буквы и точки
		System::Text::RegularExpressions::Regex^ regex =
			gcnew System::Text::RegularExpressions::Regex(L"^[А-ЯЁ]\\.[А-ЯЁ]\\.([А-ЯЁ][а-яё]+|[А-ЯЁ]\\.)$");

		if (regex->IsMatch(fio))
		{
			fio_textbox->BackColor = System::Drawing::Color::LightGreen;
		}
		else
		{
			fio_textbox->BackColor = System::Drawing::Color::LightPink;
		}
	}

	System::Void AuthForm::ValidateEmailFormat()
	{
		String^ email = email_textbox->Text->Trim();

		if (String::IsNullOrEmpty(email))
		{
			email_textbox->BackColor = System::Drawing::Color::White;
			return;
		}

		// Простая валидация email
		try
		{
			// Используем встроенную проверку MailAddress
			System::Net::Mail::MailAddress^ mailAddress = gcnew System::Net::Mail::MailAddress(email);
			email_textbox->BackColor = System::Drawing::Color::LightGreen;
		}
		catch (Exception^)
		{
			// Или используем regex для более гибкой проверки
			System::Text::RegularExpressions::Regex^ regex =
				gcnew System::Text::RegularExpressions::Regex(
					L"^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");

			if (regex->IsMatch(email))
			{
				email_textbox->BackColor = System::Drawing::Color::LightGreen;
			}
			else
			{
				email_textbox->BackColor = System::Drawing::Color::LightPink;
			}
		}
	}

	System::Void AuthForm::fio_textbox_TextChanged(System::Object^ sender, System::EventArgs^ e)
	{
		ValidateFIOFormat();
	}

	System::Void AuthForm::email_textbox_TextChanged(System::Object^ sender, System::EventArgs^ e)
	{
		ValidateEmailFormat();
	}

	System::Void AuthForm::next_pass_Click(System::Object^ sender, System::EventArgs^ e)
	{
		// Проверка ФИО
		String^ fio = fio_textbox->Text->Trim();

		if (String::IsNullOrEmpty(fio))
		{
			MessageBox::Show(L"Пожалуйста, введите ФИО!", L"Ошибка",
				MessageBoxButtons::OK, MessageBoxIcon::Warning);
			fio_textbox->Focus();
			return;
		}

		// Проверка формата ФИО
		System::Text::RegularExpressions::Regex^ fioRegex =
			gcnew System::Text::RegularExpressions::Regex(L"^[А-ЯЁ]\\.[А-ЯЁ]\\.([А-ЯЁ][а-яё]+|[А-ЯЁ]\\.)$");

		if (!fioRegex->IsMatch(fio))
		{
			MessageBox::Show(L"Неверный формат ФИО! Используйте формат: А.А.Рогатин или А.А.Р.",
				L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			fio_textbox->Focus();
			fio_textbox->SelectAll();
			return;
		}

		// Проверка email
		String^ email = email_textbox->Text->Trim();

		if (String::IsNullOrEmpty(email))
		{
			MessageBox::Show(L"Пожалуйста, введите email!", L"Ошибка",
				MessageBoxButtons::OK, MessageBoxIcon::Warning);
			email_textbox->Focus();
			return;
		}

		// Проверка формата email
		System::Text::RegularExpressions::Regex^ emailRegex =
			gcnew System::Text::RegularExpressions::Regex(
				L"^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");

		if (!emailRegex->IsMatch(email))
		{
			MessageBox::Show(L"Неверный формат email! Используйте формат: example@mail.ru",
				L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			email_textbox->Focus();
			email_textbox->SelectAll();
			return;
		}

		// Сохраняем данные
		_userFIO = fio;
		_userEmail = email;

		if (_isAdminMode)
		{
			// Проверка пароля для режима администратора
			String^ password = check_pass_box->Text;

			if (String::IsNullOrEmpty(password))
			{
				MessageBox::Show(L"Пожалуйста, введите пароль!", L"Ошибка",
					MessageBoxButtons::OK, MessageBoxIcon::Warning);
				check_pass_box->Focus();
				return;
			}

			// Здесь должна быть проверка пароля из файла или базы данных
			String^ filePath = "admin_password.txt";
			String^ storedPassword = "";

			if (File::Exists(filePath))
			{
				storedPassword = File::ReadAllText(filePath)->Trim();
			}
			else
			{
				// Если файла нет, используем пароль по умолчанию
				storedPassword = "admin";
			}

			if (password == storedPassword)
			{
				_authenticated = true;

				// Дополнительно можно сохранить данные администратора
				try
				{
					String^ adminData = String::Format("FIO: {0}\nEmail: {1}\nLastLogin: {2}",
						fio, email, DateTime::Now.ToString("dd.MM.yyyy HH:mm:ss"));
					File::WriteAllText("admin_info.txt", adminData);
				}
				catch (Exception^ ex)
				{
					// Логируем ошибку, но не прерываем авторизацию
					System::Diagnostics::Debug::WriteLine("Ошибка сохранения данных администратора: " + ex->Message);
				}

				this->DialogResult = Windows::Forms::DialogResult::OK;
				this->Close();
			}
			else
			{
				MessageBox::Show(L"Неверный пароль администратора!", L"Ошибка",
					MessageBoxButtons::OK, MessageBoxIcon::Error);
				check_pass_box->Clear();
				check_pass_box->Focus();
			}
		}
		else
		{
			// Режим обычного пользователя - сохраняем данные и закрываем форму
			_authenticated = true;

			// Сохраняем данные пользователя (опционально)
			try
			{
				String^ userData = String::Format("FIO: {0}\nEmail: {1}\nRegistrationDate: {2}",
					fio, email, DateTime::Now.ToString("dd.MM.yyyy HH:mm:ss"));
				File::AppendAllText("users_log.txt", userData + "\n\n");
			}
			catch (Exception^ ex)
			{
				System::Diagnostics::Debug::WriteLine("Ошибка сохранения данных пользователя: " + ex->Message);
			}

			this->DialogResult = Windows::Forms::DialogResult::OK;
			this->Close();
		}
	}

	System::Void AuthForm::back_from_pass_Click(System::Object^ sender, System::EventArgs^ e)
	{
		this->DialogResult = Windows::Forms::DialogResult::Cancel;
		this->Close();
	}

	System::Void AuthForm::change_pass_Click(System::Object^ sender, System::EventArgs^ e)
	{
		// Проверяем, заполнены ли обязательные поля
		String^ fio = fio_textbox->Text->Trim();
		String^ email = email_textbox->Text->Trim();

		if (String::IsNullOrEmpty(fio) || String::IsNullOrEmpty(email))
		{
			MessageBox::Show(L"Заполните ФИО и email перед сменой пароля!", L"Предупреждение",
				MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		// Проверяем текущий пароль перед сменой
		String^ currentPassword = check_pass_box->Text;

		if (String::IsNullOrEmpty(currentPassword))
		{
			MessageBox::Show(L"Введите текущий пароль для смены!", L"Предупреждение",
				MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		// Открываем форму смены пароля
		ChangePasswordForm^ changeForm = gcnew ChangePasswordForm();
		if (changeForm->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			MessageBox::Show(L"Пароль успешно изменен!", L"Успех",
				MessageBoxButtons::OK, MessageBoxIcon::Information);

			// Записываем информацию о смене пароля
			try
			{
				String^ changeLog = String::Format("[{0}] Пароль изменен администратором: {1} ({2})",
					DateTime::Now.ToString("dd.MM.yyyy HH:mm:ss"), fio, email);
				File::AppendAllText("password_changes.log", changeLog + "\n");
			}
			catch (Exception^ ex)
			{
				System::Diagnostics::Debug::WriteLine("Ошибка логирования смены пароля: " + ex->Message);
			}
		}
	}

	System::Void AuthForm::ChangePassword(String^ newPassword)
	{
		// Реализация смены пароля
		String^ filePath = "admin_password.txt";
		File::WriteAllText(filePath, newPassword);
	}
}