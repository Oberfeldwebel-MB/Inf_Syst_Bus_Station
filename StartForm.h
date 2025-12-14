#pragma once

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
		public System::Windows::Forms::Form
	{
	public:
		StartForm(void)
		{
			InitializeComponent();
			_validationErrors = gcnew System::Collections::Generic::List<String^>();
			this->Text = L"ИСА Автобусный автопарк - Главное меню";
		}

	protected:
		~StartForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		System::ComponentModel::Container^ components;
		System::Windows::Forms::Label^ label_MenuAuthorization;
		System::Windows::Forms::Label^ label_ChoiceAccess;
		System::Windows::Forms::Button^ buttonAdmin;
		System::Windows::Forms::Button^ buttonUser;
		System::Windows::Forms::Button^ buttonInfo;
		System::Windows::Forms::Button^ buttonExit;
		System::Collections::Generic::List<String^>^ _validationErrors;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->label_MenuAuthorization = (gcnew System::Windows::Forms::Label());
			this->label_ChoiceAccess = (gcnew System::Windows::Forms::Label());
			this->buttonAdmin = (gcnew System::Windows::Forms::Button());
			this->buttonUser = (gcnew System::Windows::Forms::Button());
			this->buttonInfo = (gcnew System::Windows::Forms::Button());
			this->buttonExit = (gcnew System::Windows::Forms::Button()); // Добавим кнопку выхода
			this->SuspendLayout();

			// label_MenuAuthorization
			this->label_MenuAuthorization->Cursor = System::Windows::Forms::Cursors::Default;
			this->label_MenuAuthorization->Location = System::Drawing::Point(264, 84);
			this->label_MenuAuthorization->Name = L"label_MenuAuthorization";
			this->label_MenuAuthorization->Size = System::Drawing::Size(169, 26);
			this->label_MenuAuthorization->TabIndex = 4;
			this->label_MenuAuthorization->Text = L"ИСА Автобусный парк";
			this->label_MenuAuthorization->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label_MenuAuthorization->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, FontStyle::Bold);

			// label_ChoiceAccess
			this->label_ChoiceAccess->Location = System::Drawing::Point(265, 149);
			this->label_ChoiceAccess->Name = L"label_ChoiceAccess";
			this->label_ChoiceAccess->Size = System::Drawing::Size(168, 26);
			this->label_ChoiceAccess->TabIndex = 3;
			this->label_ChoiceAccess->Text = L"Выберите режим работы";
			this->label_ChoiceAccess->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;

			// buttonAdmin
			this->buttonAdmin->BackColor = System::Drawing::Color::LightGreen;
			this->buttonAdmin->FlatAppearance->BorderColor = System::Drawing::Color::DarkGreen;
			this->buttonAdmin->FlatAppearance->BorderSize = 2;
			this->buttonAdmin->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->buttonAdmin->Location = System::Drawing::Point(143, 212);
			this->buttonAdmin->Name = L"buttonAdmin";
			this->buttonAdmin->Size = System::Drawing::Size(150, 50);
			this->buttonAdmin->TabIndex = 2;
			this->buttonAdmin->Text = L"Режим администратора";
			this->buttonAdmin->UseVisualStyleBackColor = false;
			this->buttonAdmin->Click += gcnew System::EventHandler(this, &StartForm::buttonAdmin_Click);
			this->buttonAdmin->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, FontStyle::Bold);

			// buttonUser
			this->buttonUser->BackColor = System::Drawing::Color::LightGreen;
			this->buttonUser->FlatAppearance->BorderColor = System::Drawing::Color::DarkGreen;
			this->buttonUser->FlatAppearance->BorderSize = 2;
			this->buttonUser->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->buttonUser->Location = System::Drawing::Point(395, 212);
			this->buttonUser->Name = L"buttonUser";
			this->buttonUser->Size = System::Drawing::Size(150, 50);
			this->buttonUser->TabIndex = 1;
			this->buttonUser->Text = L"Режим пользователя";
			this->buttonUser->UseVisualStyleBackColor = false;
			this->buttonUser->Click += gcnew System::EventHandler(this, &StartForm::buttonUser_Click);
			this->buttonUser->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, FontStyle::Bold);

			// buttonInfo
			this->buttonInfo->BackColor = System::Drawing::Color::LightBlue;
			this->buttonInfo->FlatAppearance->BorderColor = System::Drawing::Color::Blue;
			this->buttonInfo->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->buttonInfo->Location = System::Drawing::Point(573, 12);
			this->buttonInfo->Name = L"buttonInfo";
			this->buttonInfo->Size = System::Drawing::Size(100, 30);
			this->buttonInfo->TabIndex = 0;
			this->buttonInfo->Text = L"Справка";
			this->buttonInfo->UseVisualStyleBackColor = false;
			this->buttonInfo->Click += gcnew System::EventHandler(this, &StartForm::buttonInfo_Click);

			// buttonExit
			this->buttonExit->BackColor = System::Drawing::Color::LightCoral;
			this->buttonExit->FlatAppearance->BorderColor = System::Drawing::Color::DarkRed;
			this->buttonExit->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->buttonExit->Location = System::Drawing::Point(12, 320);
			this->buttonExit->Name = L"buttonExit";
			this->buttonExit->Size = System::Drawing::Size(100, 30);
			this->buttonExit->TabIndex = 5;
			this->buttonExit->Text = L"Выход";
			this->buttonExit->UseVisualStyleBackColor = false;
			this->buttonExit->Click += gcnew System::EventHandler(this, &StartForm::buttonExit_Click);

			// StartForm
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::SeaGreen;
			this->ClientSize = System::Drawing::Size(685, 365);
			this->Controls->Add(this->buttonExit);
			this->Controls->Add(this->buttonInfo);
			this->Controls->Add(this->buttonUser);
			this->Controls->Add(this->buttonAdmin);
			this->Controls->Add(this->label_ChoiceAccess);
			this->Controls->Add(this->label_MenuAuthorization);
			this->Name = L"StartForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"ИСА Автобусный автопарк - Главное меню";
			this->ResumeLayout(false);
		}
#pragma endregion

	private:
		System::Void buttonAdmin_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void buttonUser_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void buttonInfo_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void buttonExit_Click(System::Object^ sender, System::EventArgs^ e);
	};
}