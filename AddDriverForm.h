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
	public ref class AddDriverForm : public System::Windows::Forms::Form
	{
	public: event System::EventHandler^ DataAdded;

	public:
		AddDriverForm(void)
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
		~AddDriverForm()
		{
			if (components)
			{
				delete components;
			}
		}
	public: System::Windows::Forms::MaskedTextBox^ data_add;
	protected:

	public: System::Windows::Forms::MaskedTextBox^ FIO_add;
	protected:

	public: System::Windows::Forms::Label^ fio_add_label;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ pol_add_label;
	public: System::Windows::Forms::CheckedListBox^ pol_add;
	private:



	private: System::Windows::Forms::Label^ faculty_add_label;






	private: System::Windows::Forms::Label^ label2;

	private: System::Windows::Forms::Button^ add_button;

	private: System::Windows::Forms::Button^ back_add;

	private: System::Windows::Forms::Label^ label4;



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
	private: System::Windows::Forms::NumericUpDown^ ratingNumericUpDown;
	private: System::Windows::Forms::Label^ label5;



	public: System::Windows::Forms::MaskedTextBox^ maskedTextBox1;
	private:
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
			this->FIO_add = (gcnew System::Windows::Forms::MaskedTextBox());
			this->fio_add_label = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->pol_add_label = (gcnew System::Windows::Forms::Label());
			this->pol_add = (gcnew System::Windows::Forms::CheckedListBox());
			this->faculty_add_label = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->add_button = (gcnew System::Windows::Forms::Button());
			this->back_add = (gcnew System::Windows::Forms::Button());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->ratingNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->maskedTextBox1 = (gcnew System::Windows::Forms::MaskedTextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ratingNumericUpDown))->BeginInit();
			this->SuspendLayout();
			// 
			// data_add
			// 
			this->data_add->Location = System::Drawing::Point(84, 293);
			this->data_add->Mask = L"0000/000000";
			this->data_add->Name = L"data_add";
			this->data_add->Size = System::Drawing::Size(86, 22);
			this->data_add->TabIndex = 0;
			this->data_add->ValidatingType = System::DateTime::typeid;
			// 
			// FIO_add
			// 
			this->FIO_add->Location = System::Drawing::Point(84, 127);
			this->FIO_add->Mask = L">L.L. A<AAAAAAAAAA";
			this->FIO_add->Name = L"FIO_add";
			this->FIO_add->Size = System::Drawing::Size(111, 22);
			this->FIO_add->TabIndex = 1;
			// 
			// fio_add_label
			// 
			this->fio_add_label->Location = System::Drawing::Point(81, 84);
			this->fio_add_label->Name = L"fio_add_label";
			this->fio_add_label->Size = System::Drawing::Size(89, 23);
			this->fio_add_label->TabIndex = 2;
			this->fio_add_label->Text = L"ФИО";
			// 
			// label1
			// 
			this->label1->Location = System::Drawing::Point(84, 255);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(165, 35);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Серия и номер паспорта";
			// 
			// pol_add_label
			// 
			this->pol_add_label->Location = System::Drawing::Point(87, 164);
			this->pol_add_label->Name = L"pol_add_label";
			this->pol_add_label->Size = System::Drawing::Size(108, 23);
			this->pol_add_label->TabIndex = 4;
			this->pol_add_label->Text = L"Пол";
			// 
			// pol_add
			// 
			this->pol_add->FormattingEnabled = true;
			this->pol_add->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"М", L"Ж" });
			this->pol_add->Location = System::Drawing::Point(87, 186);
			this->pol_add->Name = L"pol_add";
			this->pol_add->Size = System::Drawing::Size(83, 55);
			this->pol_add->TabIndex = 5;
			this->pol_add->ItemCheck += gcnew System::Windows::Forms::ItemCheckEventHandler(this, &AddDriverForm::pol_add_ItemCheck);
			// 
			// faculty_add_label
			// 
			this->faculty_add_label->Location = System::Drawing::Point(81, 342);
			this->faculty_add_label->Name = L"faculty_add_label";
			this->faculty_add_label->Size = System::Drawing::Size(111, 23);
			this->faculty_add_label->TabIndex = 7;
			this->faculty_add_label->Text = L"Номер ВУ ";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(415, 84);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(0, 16);
			this->label2->TabIndex = 10;
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
			this->add_button->Click += gcnew System::EventHandler(this, &AddDriverForm::add_button_Click);
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
			this->back_add->Click += gcnew System::EventHandler(this, &AddDriverForm::back_add_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(421, 91);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(71, 16);
			this->label4->TabIndex = 15;
			this->label4->Text = L"Зарплата";
			// 
			// ratingNumericUpDown
			// 
			this->ratingNumericUpDown->Location = System::Drawing::Point(423, 128);
			this->ratingNumericUpDown->Name = L"ratingNumericUpDown";
			this->ratingNumericUpDown->Size = System::Drawing::Size(120, 22);
			this->ratingNumericUpDown->TabIndex = 16;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label5->Location = System::Drawing::Point(87, 23);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(441, 20);
			this->label5->TabIndex = 17;
			this->label5->Text = L"Внесите данные о водителе для добавления ";
			// 
			// maskedTextBox1
			// 
			this->maskedTextBox1->Location = System::Drawing::Point(84, 384);
			this->maskedTextBox1->Mask = L"00/00/000000";
			this->maskedTextBox1->Name = L"maskedTextBox1";
			this->maskedTextBox1->Size = System::Drawing::Size(86, 22);
			this->maskedTextBox1->TabIndex = 21;
			this->maskedTextBox1->ValidatingType = System::DateTime::typeid;
			// 
			// AddDriverForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::AppWorkspace;
			this->ClientSize = System::Drawing::Size(754, 506);
			this->Controls->Add(this->maskedTextBox1);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->ratingNumericUpDown);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->back_add);
			this->Controls->Add(this->add_button);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->faculty_add_label);
			this->Controls->Add(this->pol_add);
			this->Controls->Add(this->pol_add_label);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->fio_add_label);
			this->Controls->Add(this->FIO_add);
			this->Controls->Add(this->data_add);
			this->Name = L"AddDriverForm";
			this->Text = L"Добавить строку";
			this->Load += gcnew System::EventHandler(this, &AddDriverForm::add_form_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ratingNumericUpDown))->EndInit();
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
