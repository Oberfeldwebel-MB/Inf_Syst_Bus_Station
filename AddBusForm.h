#pragma once

namespace InfSystBusStation {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для add_form
	/// </summary>
	public ref class add_form : public System::Windows::Forms::Form
	{
	public: event System::EventHandler^ DataAdded;

	public:
		add_form(void)
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
		~add_form()
		{
			if (components)
			{
				delete components;
			}
		}
	public: System::Windows::Forms::MaskedTextBox^ data_add;
	protected:


	protected:

	public: System::Windows::Forms::Label^ fio_add_label;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ pol_add_label;
	public: System::Windows::Forms::TextBox^ CountPlaceBox;
	private:

	private:



	private: System::Windows::Forms::Label^ faculty_add_label;
	public: System::Windows::Forms::TextBox^ TechSostBox;
	private:






	private: System::Windows::Forms::Label^ label2;

	private: System::Windows::Forms::Button^ add_button;

	private: System::Windows::Forms::Button^ back_add;





	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container^ components;
	public:
		String^ FIO;
		String^ Pol;
		String^ Data_Str;
		String^ Faculty;
		String^ Grupp;
		String^ SozAct;

	private: System::Windows::Forms::Label^ label5;



	public: System::Windows::Forms::TextBox^ BrandBox;
	private:
	public: System::Windows::Forms::TextBox^ ModelBox;
	public:
		Decimal Rating;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->data_add = (gcnew System::Windows::Forms::MaskedTextBox());
			this->fio_add_label = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->pol_add_label = (gcnew System::Windows::Forms::Label());
			this->CountPlaceBox = (gcnew System::Windows::Forms::TextBox());
			this->faculty_add_label = (gcnew System::Windows::Forms::Label());
			this->TechSostBox = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->add_button = (gcnew System::Windows::Forms::Button());
			this->back_add = (gcnew System::Windows::Forms::Button());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->BrandBox = (gcnew System::Windows::Forms::TextBox());
			this->ModelBox = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// data_add
			// 
			this->data_add->Location = System::Drawing::Point(84, 293);
			this->data_add->Mask = L"00/00/0000";
			this->data_add->Name = L"data_add";
			this->data_add->Size = System::Drawing::Size(86, 22);
			this->data_add->TabIndex = 0;
			this->data_add->ValidatingType = System::DateTime::typeid;
			// 
			// fio_add_label
			// 
			this->fio_add_label->Location = System::Drawing::Point(81, 84);
			this->fio_add_label->Name = L"fio_add_label";
			this->fio_add_label->Size = System::Drawing::Size(89, 23);
			this->fio_add_label->TabIndex = 2;
			this->fio_add_label->Text = L"Марка";
			// 
			// label1
			// 
			this->label1->Location = System::Drawing::Point(84, 255);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(168, 35);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Дата прохождения последнего ТО";
			// 
			// pol_add_label
			// 
			this->pol_add_label->Location = System::Drawing::Point(87, 164);
			this->pol_add_label->Name = L"pol_add_label";
			this->pol_add_label->Size = System::Drawing::Size(108, 23);
			this->pol_add_label->TabIndex = 4;
			this->pol_add_label->Text = L"Модель";
			// 
			// CountPlaceBox
			// 
			this->CountPlaceBox->Location = System::Drawing::Point(84, 383);
			this->CountPlaceBox->Name = L"CountPlaceBox";
			this->CountPlaceBox->Size = System::Drawing::Size(86, 22);
			this->CountPlaceBox->TabIndex = 6;
			// 
			// faculty_add_label
			// 
			this->faculty_add_label->Location = System::Drawing::Point(81, 348);
			this->faculty_add_label->Name = L"faculty_add_label";
			this->faculty_add_label->Size = System::Drawing::Size(124, 32);
			this->faculty_add_label->TabIndex = 7;
			this->faculty_add_label->Text = L"Количество мест";
			// 
			// TechSostBox
			// 
			this->TechSostBox->Location = System::Drawing::Point(418, 127);
			this->TechSostBox->Name = L"TechSostBox";
			this->TechSostBox->Size = System::Drawing::Size(120, 22);
			this->TechSostBox->TabIndex = 8;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(415, 84);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(163, 16);
			this->label2->TabIndex = 10;
			this->label2->Text = L"Техническое состояние";
			// 
			// add_button
			// 
			this->add_button->BackColor = System::Drawing::SystemColors::InactiveCaption;
			this->add_button->Location = System::Drawing::Point(604, 396);
			this->add_button->Name = L"add_button";
			this->add_button->Size = System::Drawing::Size(95, 32);
			this->add_button->TabIndex = 12;
			this->add_button->Text = L"Добавить";
			this->add_button->UseVisualStyleBackColor = false;
			this->add_button->Click += gcnew System::EventHandler(this, &add_form::add_button_Click);
			// 
			// back_add
			// 
			this->back_add->BackColor = System::Drawing::SystemColors::InactiveCaption;
			this->back_add->Location = System::Drawing::Point(604, 446);
			this->back_add->Name = L"back_add";
			this->back_add->Size = System::Drawing::Size(95, 33);
			this->back_add->TabIndex = 13;
			this->back_add->Text = L"Назад";
			this->back_add->UseVisualStyleBackColor = false;
			this->back_add->Click += gcnew System::EventHandler(this, &add_form::back_add_Click);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label5->Location = System::Drawing::Point(87, 23);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(527, 20);
			this->label5->TabIndex = 17;
			this->label5->Text = L"Внесите данные об автобусе для добавления в список";
			// 
			// BrandBox
			// 
			this->BrandBox->Location = System::Drawing::Point(84, 127);
			this->BrandBox->Name = L"BrandBox";
			this->BrandBox->Size = System::Drawing::Size(86, 22);
			this->BrandBox->TabIndex = 21;
			// 
			// ModelBox
			// 
			this->ModelBox->Location = System::Drawing::Point(84, 207);
			this->ModelBox->Name = L"ModelBox";
			this->ModelBox->Size = System::Drawing::Size(86, 22);
			this->ModelBox->TabIndex = 22;
			// 
			// add_form
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::AppWorkspace;
			this->ClientSize = System::Drawing::Size(754, 506);
			this->Controls->Add(this->ModelBox);
			this->Controls->Add(this->BrandBox);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->back_add);
			this->Controls->Add(this->add_button);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->TechSostBox);
			this->Controls->Add(this->faculty_add_label);
			this->Controls->Add(this->CountPlaceBox);
			this->Controls->Add(this->pol_add_label);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->fio_add_label);
			this->Controls->Add(this->data_add);
			this->Name = L"add_form";
			this->Text = L"Добавить строку";
			this->Load += gcnew System::EventHandler(this, &add_form::add_form_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}

#pragma endregion
	public: System::Void add_button_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void back_add_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Close();
	}
	private: System::Void pol_add_ItemCheck(System::Object^ sender, System::Windows::Forms::ItemCheckEventArgs^ e) {
		CheckedListBox^ listBox = (CheckedListBox^)sender;

		// Если пользователь пытается выбрать новый пункт
		if (e->NewValue == CheckState::Checked) {
			// Снимаем галочки со всех остальных пунктов
			for (int i = 0; i < listBox->Items->Count; i++) {
				if (i != e->Index) {
					listBox->SetItemChecked(i, false);
				}
			}
		}
	}

	private: System::Void add_soz_act_ItemCheck(System::Object^ sender, System::Windows::Forms::ItemCheckEventArgs^ e) {
		CheckedListBox^ listBox = (CheckedListBox^)sender;

		// Если пользователь пытается выбрать новый пункт
		if (e->NewValue == CheckState::Checked) {
			// Снимаем галочки со всех остальных пунктов
			for (int i = 0; i < listBox->Items->Count; i++) {
				if (i != e->Index) {
					listBox->SetItemChecked(i, false);
				}
			}
		}
	}
	private: System::Void add_form_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	};
}
