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
		AuthForm(void)
		{
			InitializeComponent();
			this->Text = L"Авторизация администратора - Автобусный парк";
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

		// Свойства
		property bool IsAuthenticated {
			bool get() { return _authenticated; }
		}

	private:
		bool _authenticated = false;
		System::Windows::Forms::Label^ label1;
		System::Windows::Forms::TextBox^ check_pass_box;
		System::Windows::Forms::Button^ next_pass;
		System::Windows::Forms::Button^ change_pass;
		System::Windows::Forms::Button^ back_from_pass;

		// Оставляем только ChangePassword для совместимости
		System::Void ChangePassword(String^ newPassword);

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
			this->SuspendLayout();

			// label1
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->label1->Location = System::Drawing::Point(102, 114);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(226, 20);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Введите пароль администратора";

			// check_pass_box
			this->check_pass_box->Location = System::Drawing::Point(128, 143);
			this->check_pass_box->Name = L"check_pass_box";
			this->check_pass_box->PasswordChar = '*';
			this->check_pass_box->Size = System::Drawing::Size(168, 22);
			this->check_pass_box->TabIndex = 1;

			// next_pass
			this->next_pass->BackColor = System::Drawing::Color::LightGreen;
			this->next_pass->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->next_pass->Location = System::Drawing::Point(167, 171);
			this->next_pass->Name = L"next_pass";
			this->next_pass->Size = System::Drawing::Size(75, 30);
			this->next_pass->TabIndex = 2;
			this->next_pass->Text = L"Войти";
			this->next_pass->UseVisualStyleBackColor = false;
			this->next_pass->Click += gcnew System::EventHandler(this, &AuthForm::next_pass_Click);

			// change_pass
			this->change_pass->BackColor = System::Drawing::Color::LightBlue;
			this->change_pass->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->change_pass->Location = System::Drawing::Point(137, 278);
			this->change_pass->Name = L"change_pass";
			this->change_pass->Size = System::Drawing::Size(150, 30);
			this->change_pass->TabIndex = 3;
			this->change_pass->Text = L"Сменить пароль";
			this->change_pass->UseVisualStyleBackColor = false;
			this->change_pass->Click += gcnew System::EventHandler(this, &AuthForm::change_pass_Click);

			// back_from_pass
			this->back_from_pass->BackColor = System::Drawing::Color::LightCoral;
			this->back_from_pass->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->back_from_pass->Location = System::Drawing::Point(11, 17);
			this->back_from_pass->Name = L"back_from_pass";
			this->back_from_pass->Size = System::Drawing::Size(75, 30);
			this->back_from_pass->TabIndex = 4;
			this->back_from_pass->Text = L"Назад";
			this->back_from_pass->UseVisualStyleBackColor = false;
			this->back_from_pass->Click += gcnew System::EventHandler(this, &AuthForm::back_from_pass_Click);

			// AuthForm
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::LightGray;
			this->ClientSize = System::Drawing::Size(443, 313);
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
			this->Text = L"Авторизация администратора - Автобусный парк";
			this->ResumeLayout(false);
			this->PerformLayout();
		}
#pragma endregion

	private:
		// Обработчики событий
		System::Void back_from_pass_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void next_pass_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void change_pass_Click(System::Object^ sender, System::EventArgs^ e);
	};
}