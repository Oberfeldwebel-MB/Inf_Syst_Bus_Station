#pragma once

namespace InfSystBusStation {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для UserForm
	/// </summary>
	public ref class UserForm : public System::Windows::Forms::Form
	{
	public:
		UserForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~UserForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ ChoseButton;
	protected:
	private: System::Windows::Forms::Button^ TicketListButton;
	private: System::Windows::Forms::Button^ BackButton;


	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->ChoseButton = (gcnew System::Windows::Forms::Button());
			this->TicketListButton = (gcnew System::Windows::Forms::Button());
			this->BackButton = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// ChoseButton
			// 
			this->ChoseButton->Location = System::Drawing::Point(57, 208);
			this->ChoseButton->Name = L"ChoseButton";
			this->ChoseButton->Size = System::Drawing::Size(126, 30);
			this->ChoseButton->TabIndex = 0;
			this->ChoseButton->Text = L"Выбрать Билет";
			this->ChoseButton->UseVisualStyleBackColor = true;
			this->ChoseButton->Click += gcnew System::EventHandler(this, &UserForm::ChoseButton_Click);
			// 
			// TicketListButton
			// 
			this->TicketListButton->Location = System::Drawing::Point(255, 208);
			this->TicketListButton->Name = L"TicketListButton";
			this->TicketListButton->Size = System::Drawing::Size(125, 30);
			this->TicketListButton->TabIndex = 1;
			this->TicketListButton->Text = L"Мои билеты";
			this->TicketListButton->UseVisualStyleBackColor = true;
			this->TicketListButton->Click += gcnew System::EventHandler(this, &UserForm::TicketListButton_Click);
			// 
			// BackButton
			// 
			this->BackButton->Location = System::Drawing::Point(12, 10);
			this->BackButton->Name = L"BackButton";
			this->BackButton->Size = System::Drawing::Size(66, 27);
			this->BackButton->TabIndex = 2;
			this->BackButton->Text = L"Назад";
			this->BackButton->UseVisualStyleBackColor = true;
			this->BackButton->Click += gcnew System::EventHandler(this, &UserForm::BackButton_Click);
			// 
			// UserForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(433, 375);
			this->Controls->Add(this->BackButton);
			this->Controls->Add(this->TicketListButton);
			this->Controls->Add(this->ChoseButton);
			this->Name = L"UserForm";
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void ChoseButton_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void TicketListButton_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void BackButton_Click(System::Object^ sender, System::EventArgs^ e);
	};
}
