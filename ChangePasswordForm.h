#pragma once

namespace InfSystBusStation {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Форма для смены пароля администратора
	/// </summary>
	public ref class ChangePasswordForm : public System::Windows::Forms::Form
	{
	public:
		ChangePasswordForm(void)
		{
			InitializeComponent();
			this->Text = L"Смена пароля администратора";
			// Устанавливаем ответ на секретный вопрос
			secret_answer = L"Мерседес"; // Можно изменить на что-то более подходящее для автопарка
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~ChangePasswordForm()
		{
			if (components)
			{
				delete components;
			}
		}

		// Свойства
		property String^ NewPassword {
			String^ get() { return new_pass_box->Text; }
		}

		property String^ SecretAnswer {
			String^ get() { return secret_answer; }
			void set(String^ value) { secret_answer = value; }
		}

	private:
		System::Windows::Forms::Label^ label1;
		System::Windows::Forms::Label^ label2;
		System::Windows::Forms::TextBox^ check_quest_box;
		System::Windows::Forms::Label^ label3;
		System::Windows::Forms::TextBox^ new_pass_box;
		System::Windows::Forms::Button^ change_pass_but;
		System::Windows::Forms::Button^ back_from_ch_pass;

		String^ secret_answer;

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
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->check_quest_box = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->new_pass_box = (gcnew System::Windows::Forms::TextBox());
			this->change_pass_but = (gcnew System::Windows::Forms::Button());
			this->back_from_ch_pass = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->label1->Location = System::Drawing::Point(12, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(338, 53);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Для смены пароля ответьте на секретный вопрос и введите новый пароль";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->label2->Location = System::Drawing::Point(30, 79);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(370, 20);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Какая ваша любимая марка автомобилей\?";
			// 
			// check_quest_box
			// 
			this->check_quest_box->Location = System::Drawing::Point(107, 113);
			this->check_quest_box->Name = L"check_quest_box";
			this->check_quest_box->Size = System::Drawing::Size(200, 22);
			this->check_quest_box->TabIndex = 2;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->label3->Location = System::Drawing::Point(1, 168);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(210, 20);
			this->label3->TabIndex = 3;
			this->label3->Text = L"Введите новый пароль:";
			// 
			// new_pass_box
			// 
			this->new_pass_box->Location = System::Drawing::Point(228, 168);
			this->new_pass_box->Name = L"new_pass_box";
			this->new_pass_box->PasswordChar = '*';
			this->new_pass_box->Size = System::Drawing::Size(200, 22);
			this->new_pass_box->TabIndex = 3;
			// 
			// change_pass_but
			// 
			this->change_pass_but->BackColor = System::Drawing::Color::LightGreen;
			this->change_pass_but->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->change_pass_but->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->change_pass_but->Location = System::Drawing::Point(200, 220);
			this->change_pass_but->Name = L"change_pass_but";
			this->change_pass_but->Size = System::Drawing::Size(150, 35);
			this->change_pass_but->TabIndex = 4;
			this->change_pass_but->Text = L"Изменить пароль";
			this->change_pass_but->UseVisualStyleBackColor = false;
			this->change_pass_but->Click += gcnew System::EventHandler(this, &ChangePasswordForm::change_pass_but_Click);
			// 
			// back_from_ch_pass
			// 
			this->back_from_ch_pass->BackColor = System::Drawing::Color::LightCoral;
			this->back_from_ch_pass->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->back_from_ch_pass->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->back_from_ch_pass->Location = System::Drawing::Point(50, 220);
			this->back_from_ch_pass->Name = L"back_from_ch_pass";
			this->back_from_ch_pass->Size = System::Drawing::Size(100, 35);
			this->back_from_ch_pass->TabIndex = 5;
			this->back_from_ch_pass->Text = L"Назад";
			this->back_from_ch_pass->UseVisualStyleBackColor = false;
			this->back_from_ch_pass->Click += gcnew System::EventHandler(this, &ChangePasswordForm::back_from_ch_pass_Click);
			// 
			// ChangePasswordForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::LightGray;
			this->ClientSize = System::Drawing::Size(450, 280);
			this->Controls->Add(this->back_from_ch_pass);
			this->Controls->Add(this->change_pass_but);
			this->Controls->Add(this->new_pass_box);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->check_quest_box);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"ChangePasswordForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Смена пароля администратора";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private:
		// Обработчики событий
		System::Void back_from_ch_pass_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void change_pass_but_Click(System::Object^ sender, System::EventArgs^ e);
	};
}