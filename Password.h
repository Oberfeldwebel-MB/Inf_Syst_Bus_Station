#pragma once

namespace InfSystBusStation {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для Password
	/// </summary>
	public ref class Password : public System::Windows::Forms::Form
	{
	public:
		Password(void);

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~Password()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Label^ label_PutPassword;
	protected:

	private: System::Windows::Forms::Button^ button_EnterPassword;
	protected:

	private: System::Windows::Forms::TextBox^ textBox_Password;
	private: System::Windows::Forms::Button^ button_ChangePassword;

	private:
		System::String^ correctPassword; // Переменная пароля

	private:
		System::ComponentModel::Container^ components;
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Password::typeid));
			this->label_PutPassword = (gcnew System::Windows::Forms::Label());
			this->button_EnterPassword = (gcnew System::Windows::Forms::Button());
			this->textBox_Password = (gcnew System::Windows::Forms::TextBox());
			this->button_ChangePassword = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// label_PutPassword
			// 
			this->label_PutPassword->AutoSize = true;
			this->label_PutPassword->Font = (gcnew System::Drawing::Font(L"Papyrus", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label_PutPassword->Location = System::Drawing::Point(12, 39);
			this->label_PutPassword->Name = L"label_PutPassword";
			this->label_PutPassword->Size = System::Drawing::Size(257, 21);
			this->label_PutPassword->TabIndex = 0;
			this->label_PutPassword->Text = L"Введите пароль администратора";
			// 
			// button_EnterPassword
			// 
			this->button_EnterPassword->BackColor = System::Drawing::Color::LightGreen;
			this->button_EnterPassword->FlatAppearance->BorderColor = System::Drawing::Color::DarkGreen;
			this->button_EnterPassword->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button_EnterPassword->Font = (gcnew System::Drawing::Font(L"Papyrus", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button_EnterPassword->Location = System::Drawing::Point(94, 149);
			this->button_EnterPassword->Name = L"button_EnterPassword";
			this->button_EnterPassword->Size = System::Drawing::Size(100, 40);
			this->button_EnterPassword->TabIndex = 1;
			this->button_EnterPassword->Text = L"Продолжить";
			this->button_EnterPassword->UseVisualStyleBackColor = false;
			this->button_EnterPassword->Click += gcnew System::EventHandler(this, &Password::button_EnterPassword_Click);
			// 
			// textBox_Password
			// 
			this->textBox_Password->Location = System::Drawing::Point(74, 102);
			this->textBox_Password->Name = L"textBox_Password";
			this->textBox_Password->PasswordChar = '*';
			this->textBox_Password->Size = System::Drawing::Size(140, 20);
			this->textBox_Password->TabIndex = 2;
			// 
			// button_ChangePassword
			// 
			this->button_ChangePassword->BackColor = System::Drawing::Color::LightGreen;
			this->button_ChangePassword->FlatAppearance->BorderColor = System::Drawing::Color::DarkGreen;
			this->button_ChangePassword->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button_ChangePassword->Font = (gcnew System::Drawing::Font(L"Papyrus", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button_ChangePassword->Location = System::Drawing::Point(16, 223);
			this->button_ChangePassword->Name = L"button_ChangePassword";
			this->button_ChangePassword->Size = System::Drawing::Size(121, 26);
			this->button_ChangePassword->TabIndex = 3;
			this->button_ChangePassword->Text = L"Сменить пароль";
			this->button_ChangePassword->UseVisualStyleBackColor = false;
			this->button_ChangePassword->Click += gcnew System::EventHandler(this, &Password::button_ChangePassword_Click);
			// 
			// Password
			// 
			this->AcceptButton = this->button_EnterPassword;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::SeaGreen;
			this->ClientSize = System::Drawing::Size(284, 261);
			this->Controls->Add(this->button_ChangePassword);
			this->Controls->Add(this->textBox_Password);
			this->Controls->Add(this->button_EnterPassword);
			this->Controls->Add(this->label_PutPassword);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximumSize = System::Drawing::Size(300, 300);
			this->MinimumSize = System::Drawing::Size(300, 300);
			this->Name = L"Password";
			this->Text = L"АСУ \"Автобусный автопарк\" | Ввод пароля";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private:
		System::Void button_EnterPassword_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void button_ChangePassword_Click(System::Object^ sender, System::EventArgs^ e);
	};
}
