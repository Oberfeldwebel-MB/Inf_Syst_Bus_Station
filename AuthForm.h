#pragma once

#include "ChangePasswordForm.h"

namespace InfSystBusStation {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	/// <summary>
	/// Форма авторизации администратора для автобусного парка
	/// </summary>
	public ref class AuthForm : public System::Windows::Forms::Form
	{
	public:
		// Убираем значение по умолчанию
		AuthForm(bool isAdminMode)
		{
			_isAdminMode = isAdminMode;
			InitializeComponent();
			this->Text = L"Авторизация - Автобусный парк";
			InitializeFormBasedOnMode();
		}

		// Дополнительный конструктор без параметров для обратной совместимости
		AuthForm(void) : AuthForm(false) // Вызываем основной конструктор с false
		{
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~AuthForm()
		{
			if (components)
			{
				delete components;
			}
		}

		// ===== ПУБЛИЧНЫЕ СВОЙСТВА =====
	public:
		// Свойства для получения данных
		property bool IsAuthenticated {
			bool get() { return _authenticated; }
		}

		property String^ UserFIO {
			String^ get() { return _userFIO; }
		}

		property String^ UserEmail {
			String^ get() { return _userEmail; }
		}

	private:
		bool _authenticated = false;
		bool _isAdminMode = false;
		String^ _userFIO = "";
		String^ _userEmail = "";

		// Элементы управления формы
		System::Windows::Forms::Label^ label1;
		System::Windows::Forms::TextBox^ check_pass_box;
		System::Windows::Forms::Button^ next_pass;
		System::Windows::Forms::Button^ change_pass;
		System::Windows::Forms::Button^ back_from_pass;

		// Новые элементы
		System::Windows::Forms::Label^ labelFIO;
		System::Windows::Forms::TextBox^ fio_textbox;
		System::Windows::Forms::Label^ labelInfo;
		System::Windows::Forms::Label^ labelEmail;
		System::Windows::Forms::TextBox^ email_textbox;
		System::Windows::Forms::Label^ labelEmailInfo;

		// Оставляем только ChangePassword для совместимости
		System::Void ChangePassword(String^ newPassword);

		// Новый метод для инициализации формы в зависимости от режима
		System::Void InitializeFormBasedOnMode();

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->check_pass_box = (gcnew System::Windows::Forms::TextBox());
			this->next_pass = (gcnew System::Windows::Forms::Button());
			this->change_pass = (gcnew System::Windows::Forms::Button());
			this->back_from_pass = (gcnew System::Windows::Forms::Button());
			this->labelFIO = (gcnew System::Windows::Forms::Label());
			this->fio_textbox = (gcnew System::Windows::Forms::TextBox());
			this->labelInfo = (gcnew System::Windows::Forms::Label());
			this->labelEmail = (gcnew System::Windows::Forms::Label());
			this->email_textbox = (gcnew System::Windows::Forms::TextBox());
			this->labelEmailInfo = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();

			// label1 (пароль)
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->label1->Location = System::Drawing::Point(102, 200);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(226, 20);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Введите пароль администратора";

			// check_pass_box
			this->check_pass_box->Location = System::Drawing::Point(128, 230);
			this->check_pass_box->Name = L"check_pass_box";
			this->check_pass_box->PasswordChar = '*';
			this->check_pass_box->Size = System::Drawing::Size(168, 22);
			this->check_pass_box->TabIndex = 4;

			// next_pass
			this->next_pass->BackColor = System::Drawing::Color::LightGreen;
			this->next_pass->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->next_pass->Location = System::Drawing::Point(167, 280);
			this->next_pass->Name = L"next_pass";
			this->next_pass->Size = System::Drawing::Size(75, 30);
			this->next_pass->TabIndex = 5;
			this->next_pass->Text = L"Войти";
			this->next_pass->UseVisualStyleBackColor = false;
			this->next_pass->Click += gcnew System::EventHandler(this, &AuthForm::next_pass_Click);

			// change_pass
			this->change_pass->BackColor = System::Drawing::Color::LightBlue;
			this->change_pass->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->change_pass->Location = System::Drawing::Point(137, 340);
			this->change_pass->Name = L"change_pass";
			this->change_pass->Size = System::Drawing::Size(150, 30);
			this->change_pass->TabIndex = 6;
			this->change_pass->Text = L"Сменить пароль";
			this->change_pass->UseVisualStyleBackColor = false;
			this->change_pass->Click += gcnew System::EventHandler(this, &AuthForm::change_pass_Click);

			// back_from_pass
			this->back_from_pass->BackColor = System::Drawing::Color::LightCoral;
			this->back_from_pass->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->back_from_pass->Location = System::Drawing::Point(11, 17);
			this->back_from_pass->Name = L"back_from_pass";
			this->back_from_pass->Size = System::Drawing::Size(75, 30);
			this->back_from_pass->TabIndex = 7;
			this->back_from_pass->Text = L"Назад";
			this->back_from_pass->UseVisualStyleBackColor = false;
			this->back_from_pass->Click += gcnew System::EventHandler(this, &AuthForm::back_from_pass_Click);

			// labelFIO
			this->labelFIO->AutoSize = true;
			this->labelFIO->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->labelFIO->Location = System::Drawing::Point(102, 30);
			this->labelFIO->Name = L"labelFIO";
			this->labelFIO->Size = System::Drawing::Size(222, 20);
			this->labelFIO->TabIndex = 8;
			this->labelFIO->Text = L"Введите ФИО (формат А.А.Рогатин)";

			// fio_textbox
			this->fio_textbox->Location = System::Drawing::Point(128, 60);
			this->fio_textbox->Name = L"fio_textbox";
			this->fio_textbox->Size = System::Drawing::Size(168, 22);
			this->fio_textbox->TabIndex = 1;
			this->fio_textbox->TextChanged += gcnew System::EventHandler(this, &AuthForm::fio_textbox_TextChanged);

			// labelInfo (для ФИО)
			this->labelInfo->AutoSize = true;
			this->labelInfo->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Italic));
			this->labelInfo->ForeColor = System::Drawing::Color::Blue;
			this->labelInfo->Location = System::Drawing::Point(50, 85);
			this->labelInfo->Name = L"labelInfo";
			this->labelInfo->Size = System::Drawing::Size(330, 17);
			this->labelInfo->TabIndex = 9;
			this->labelInfo->Text = L"Пример: А.А.Рогатин или А.А.Р.";
			this->labelInfo->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;

			// labelEmail
			this->labelEmail->AutoSize = true;
			this->labelEmail->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->labelEmail->Location = System::Drawing::Point(102, 115);
			this->labelEmail->Name = L"labelEmail";
			this->labelEmail->Size = System::Drawing::Size(120, 20);
			this->labelEmail->TabIndex = 10;
			this->labelEmail->Text = L"Введите email";

			// email_textbox
			this->email_textbox->Location = System::Drawing::Point(128, 145);
			this->email_textbox->Name = L"email_textbox";
			this->email_textbox->Size = System::Drawing::Size(168, 22);
			this->email_textbox->TabIndex = 2;
			this->email_textbox->TextChanged += gcnew System::EventHandler(this, &AuthForm::email_textbox_TextChanged);

			// labelEmailInfo
			this->labelEmailInfo->AutoSize = true;
			this->labelEmailInfo->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Italic));
			this->labelEmailInfo->ForeColor = System::Drawing::Color::Blue;
			this->labelEmailInfo->Location = System::Drawing::Point(50, 170);
			this->labelEmailInfo->Name = L"labelEmailInfo";
			this->labelEmailInfo->Size = System::Drawing::Size(330, 17);
			this->labelEmailInfo->TabIndex = 11;
			this->labelEmailInfo->Text = L"Пример: example@mail.ru или user@gmail.com";
			this->labelEmailInfo->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;

			// AuthForm
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::LightGray;
			this->ClientSize = System::Drawing::Size(443, 380);
			this->Controls->Add(this->labelEmailInfo);
			this->Controls->Add(this->email_textbox);
			this->Controls->Add(this->labelEmail);
			this->Controls->Add(this->labelInfo);
			this->Controls->Add(this->fio_textbox);
			this->Controls->Add(this->labelFIO);
			this->Controls->Add(this->back_from_pass);
			this->Controls->Add(this->change_pass);
			this->Controls->Add(this->next_pass);
			this->Controls->Add(this->check_pass_box);
			this->Controls->Add(this->label1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"AuthForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Авторизация - Автобусный парк";
			this->ResumeLayout(false);
			this->PerformLayout();
		}
#pragma endregion

	private:
		// Обработчики событий
		System::Void back_from_pass_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void next_pass_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void change_pass_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void fio_textbox_TextChanged(System::Object^ sender, System::EventArgs^ e);
		System::Void email_textbox_TextChanged(System::Object^ sender, System::EventArgs^ e);

		// Новые методы
		System::Void ValidateFIOFormat();
		System::Void ValidateEmailFormat();
	};
}