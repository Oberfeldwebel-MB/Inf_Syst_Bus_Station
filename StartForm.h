#pragma once
#include "IAppForm.h"


namespace InfSystBusStation {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для StartForm2
	/// </summary>
	public ref class StartForm : 
		public System::Windows::Forms::Form,
		public IAppForm
	{

	public:
		// === Реализация IAppForm ===

		virtual void OpenAndClose(Form^ nextForm) override;
		virtual System::Windows::Forms::DialogResult OpenModal(Form^ dialogForm) override;
		virtual void GoBack() override;


	public:
		StartForm(void)
		{
			InitializeComponent();
			_validationErrors = gcnew System::Collections::Generic::List<String^>();
			this->Text = L"ИСА Автобусный автопарк - Главное меню";
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~StartForm()
		{
			if (components)
			{
				delete components;
			}
		}

	public:
		

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

		// Элементы управления
		System::Windows::Forms::Label^ label_MenuAuthorization;
		System::Windows::Forms::Label^ label_ChoiceAccess;
		System::Windows::Forms::Button^ buttonAdmin;
		System::Windows::Forms::Button^ buttonUser;
		System::Windows::Forms::Button^ buttonInfo;
		System::Windows::Forms::Button^ buttonExit;


		// Для валидации
		System::Collections::Generic::List<String^>^ _validationErrors;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label_MenuAuthorization = (gcnew System::Windows::Forms::Label());
			this->label_ChoiceAccess = (gcnew System::Windows::Forms::Label());
			this->buttonAdmin = (gcnew System::Windows::Forms::Button());
			this->buttonUser = (gcnew System::Windows::Forms::Button());
			this->buttonInfo = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// label_MenuAuthorization
			// 
			this->label_MenuAuthorization->Cursor = System::Windows::Forms::Cursors::Default;
			this->label_MenuAuthorization->Location = System::Drawing::Point(264, 84);
			this->label_MenuAuthorization->Name = L"label_MenuAuthorization";
			this->label_MenuAuthorization->Size = System::Drawing::Size(169, 26);
			this->label_MenuAuthorization->TabIndex = 4;
			this->label_MenuAuthorization->Text = L"ИСА Автобусный парк";
			// 
			// label_ChoiceAccess
			// 
			this->label_ChoiceAccess->Location = System::Drawing::Point(265, 149);
			this->label_ChoiceAccess->Name = L"label_ChoiceAccess";
			this->label_ChoiceAccess->Size = System::Drawing::Size(168, 26);
			this->label_ChoiceAccess->TabIndex = 3;
			this->label_ChoiceAccess->Text = L"Выберите режим работы";
			// 
			// buttonAdmin
			// 
			this->buttonAdmin->BackColor = System::Drawing::Color::LightGreen;
			this->buttonAdmin->FlatAppearance->BorderColor = System::Drawing::Color::DarkGreen;
			this->buttonAdmin->Location = System::Drawing::Point(143, 212);
			this->buttonAdmin->Name = L"buttonAdmin";
			this->buttonAdmin->Size = System::Drawing::Size(124, 45);
			this->buttonAdmin->TabIndex = 2;
			this->buttonAdmin->Text = L"Администратор";
			this->buttonAdmin->UseVisualStyleBackColor = false;
			this->buttonAdmin->Click += gcnew System::EventHandler(this, &StartForm::buttonAdmin_Click);
			// 
			// buttonUser
			// 
			this->buttonUser->BackColor = System::Drawing::Color::LightGreen;
			this->buttonUser->FlatAppearance->BorderColor = System::Drawing::Color::DarkGreen;
			this->buttonUser->Location = System::Drawing::Point(434, 214);
			this->buttonUser->Name = L"buttonUser";
			this->buttonUser->Size = System::Drawing::Size(147, 43);
			this->buttonUser->TabIndex = 1;
			this->buttonUser->Text = L"Пользователь";
			this->buttonUser->UseVisualStyleBackColor = false;
			this->buttonUser->Click += gcnew System::EventHandler(this, &StartForm::buttonUser_Click);
			// 
			// buttonInfo
			// 
			this->buttonInfo->BackColor = System::Drawing::Color::LightGreen;
			this->buttonInfo->FlatAppearance->BorderColor = System::Drawing::Color::DarkGreen;
			this->buttonInfo->Location = System::Drawing::Point(573, 12);
			this->buttonInfo->Name = L"buttonInfo";
			this->buttonInfo->Size = System::Drawing::Size(90, 25);
			this->buttonInfo->TabIndex = 0;
			this->buttonInfo->Text = L"Справка";
			this->buttonInfo->UseVisualStyleBackColor = false;
			this->buttonInfo->Click += gcnew System::EventHandler(this, &StartForm::buttonInfo_Click);
			// 
			// StartForm2
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::SeaGreen;
			this->ClientSize = System::Drawing::Size(685, 365);
			this->Controls->Add(this->buttonInfo);
			this->Controls->Add(this->buttonUser);
			this->Controls->Add(this->buttonAdmin);
			this->Controls->Add(this->label_ChoiceAccess);
			this->Controls->Add(this->label_MenuAuthorization);
			this->Name = L"StartForm2";
			this->ResumeLayout(false);

		}
#pragma endregion

		private:
			// Обработчики событий
			System::Void buttonAdmin_Click(System::Object^ sender, System::EventArgs^ e);
			System::Void buttonUser_Click(System::Object^ sender, System::EventArgs^ e);
			System::Void buttonInfo_Click(System::Object^ sender, System::EventArgs^ e);
			System::Void buttonExit_Click(System::Object^ sender, System::EventArgs^ e);
	

};
}
