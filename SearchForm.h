#pragma once

namespace Деканат {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для zapros_form
	/// </summary>
	public ref class zapros_form : public System::Windows::Forms::Form
	{
	public:
		zapros_form(void)
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
		~zapros_form()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::MaskedTextBox^ search_FIO_box;

	private: System::Windows::Forms::CheckBox^ FIO_checkBox;
	public: System::Windows::Forms::CheckedListBox^ search_pol_box;
	private:

	private:

	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::CheckBox^ pol_checkBox;
	public: System::Windows::Forms::MaskedTextBox^ search_data;
	private:

	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::CheckBox^ search_data_checkBox;
	public: System::Windows::Forms::TextBox^ search_faculty_box;
	private:

	private:


	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::CheckBox^ faculty_checkBox;
	public: System::Windows::Forms::TextBox^ search_grupp_box;
	private:

	private: System::Windows::Forms::CheckBox^ grupp_checkBox;
	private: System::Windows::Forms::CheckBox^ rate_checkBox;
	private: System::Windows::Forms::CheckBox^ soz_act_checkBox;

	public:


	private: System::Windows::Forms::NumericUpDown^ new_rating_box;
	public: System::Windows::Forms::CheckedListBox^ search_soz_act_box;
	private:

	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ Рейтинг;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Button^ back_from_ch_str;
	private: System::Windows::Forms::Button^ search_button;
	private: System::Windows::Forms::Label^ label7;

	public:
		// Данные для поиска
		String^ SearchFIO;
		String^ SearchPol;
		String^ SearchDate;
		String^ SearchFaculty;
		String^ SearchGrupp;
		Decimal SearchRating;
		String^ SearchSozAct;

		// Флаги, указывающие, какие поля участвуют в поиске
		bool UseFIO = false;
		bool UsePol = false;
		bool UseDate = false;
		bool UseFaculty = false;
		bool UseGrupp = false;
		bool UseRating = false;
		bool UseSozAct = false;


	public: System::Windows::Forms::RadioButton^ rate_bol_zad;
	public: System::Windows::Forms::RadioButton^ rate_rav_zad;
	public: System::Windows::Forms::RadioButton^ rate_men_zad;
	public: System::Windows::Forms::GroupBox^ rate_grupp_box;
	public: System::Windows::Forms::GroupBox^ soz_grupp_box;
	public: System::Windows::Forms::RadioButton^ soz_men_zad;
	public: System::Windows::Forms::RadioButton^ soz_rav_zad;
	public: System::Windows::Forms::RadioButton^ soz_bol_zad;
	public: System::Windows::Forms::GroupBox^ date_grupp;

	public: System::Windows::Forms::RadioButton^ date_bol_zad;
	public: System::Windows::Forms::RadioButton^ date_men_zad;

	public: System::Windows::Forms::RadioButton^ date_rav_zad;



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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(zapros_form::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->search_FIO_box = (gcnew System::Windows::Forms::MaskedTextBox());
			this->FIO_checkBox = (gcnew System::Windows::Forms::CheckBox());
			this->search_pol_box = (gcnew System::Windows::Forms::CheckedListBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->pol_checkBox = (gcnew System::Windows::Forms::CheckBox());
			this->search_data = (gcnew System::Windows::Forms::MaskedTextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->search_data_checkBox = (gcnew System::Windows::Forms::CheckBox());
			this->search_faculty_box = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->faculty_checkBox = (gcnew System::Windows::Forms::CheckBox());
			this->search_grupp_box = (gcnew System::Windows::Forms::TextBox());
			this->grupp_checkBox = (gcnew System::Windows::Forms::CheckBox());
			this->rate_checkBox = (gcnew System::Windows::Forms::CheckBox());
			this->soz_act_checkBox = (gcnew System::Windows::Forms::CheckBox());
			this->new_rating_box = (gcnew System::Windows::Forms::NumericUpDown());
			this->search_soz_act_box = (gcnew System::Windows::Forms::CheckedListBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->Рейтинг = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->back_from_ch_str = (gcnew System::Windows::Forms::Button());
			this->search_button = (gcnew System::Windows::Forms::Button());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->rate_bol_zad = (gcnew System::Windows::Forms::RadioButton());
			this->rate_rav_zad = (gcnew System::Windows::Forms::RadioButton());
			this->rate_men_zad = (gcnew System::Windows::Forms::RadioButton());
			this->rate_grupp_box = (gcnew System::Windows::Forms::GroupBox());
			this->soz_grupp_box = (gcnew System::Windows::Forms::GroupBox());
			this->soz_men_zad = (gcnew System::Windows::Forms::RadioButton());
			this->soz_rav_zad = (gcnew System::Windows::Forms::RadioButton());
			this->soz_bol_zad = (gcnew System::Windows::Forms::RadioButton());
			this->date_grupp = (gcnew System::Windows::Forms::GroupBox());
			this->date_bol_zad = (gcnew System::Windows::Forms::RadioButton());
			this->date_men_zad = (gcnew System::Windows::Forms::RadioButton());
			this->date_rav_zad = (gcnew System::Windows::Forms::RadioButton());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->new_rating_box))->BeginInit();
			this->rate_grupp_box->SuspendLayout();
			this->soz_grupp_box->SuspendLayout();
			this->date_grupp->SuspendLayout();
			this->SuspendLayout();
			// 
			// label1
			// 
			resources->ApplyResources(this->label1, L"label1");
			this->label1->ForeColor = System::Drawing::SystemColors::ControlText;
			this->label1->Name = L"label1";
			// 
			// search_FIO_box
			// 
			resources->ApplyResources(this->search_FIO_box, L"search_FIO_box");
			this->search_FIO_box->Name = L"search_FIO_box";
			// 
			// FIO_checkBox
			// 
			resources->ApplyResources(this->FIO_checkBox, L"FIO_checkBox");
			this->FIO_checkBox->Name = L"FIO_checkBox";
			this->FIO_checkBox->UseVisualStyleBackColor = true;
			// 
			// search_pol_box
			// 
			this->search_pol_box->FormattingEnabled = true;
			this->search_pol_box->Items->AddRange(gcnew cli::array< System::Object^  >(2) {
				resources->GetString(L"search_pol_box.Items"),
					resources->GetString(L"search_pol_box.Items1")
			});
			resources->ApplyResources(this->search_pol_box, L"search_pol_box");
			this->search_pol_box->Name = L"search_pol_box";
			this->search_pol_box->ItemCheck += gcnew System::Windows::Forms::ItemCheckEventHandler(this, &zapros_form::search_pol_box_ItemCheck);
			// 
			// label2
			// 
			resources->ApplyResources(this->label2, L"label2");
			this->label2->ForeColor = System::Drawing::Color::Black;
			this->label2->Name = L"label2";
			// 
			// pol_checkBox
			// 
			resources->ApplyResources(this->pol_checkBox, L"pol_checkBox");
			this->pol_checkBox->Name = L"pol_checkBox";
			this->pol_checkBox->UseVisualStyleBackColor = true;
			// 
			// search_data
			// 
			resources->ApplyResources(this->search_data, L"search_data");
			this->search_data->Name = L"search_data";
			this->search_data->ValidatingType = System::DateTime::typeid;
			// 
			// label3
			// 
			resources->ApplyResources(this->label3, L"label3");
			this->label3->ForeColor = System::Drawing::Color::Black;
			this->label3->Name = L"label3";
			// 
			// search_data_checkBox
			// 
			resources->ApplyResources(this->search_data_checkBox, L"search_data_checkBox");
			this->search_data_checkBox->Name = L"search_data_checkBox";
			this->search_data_checkBox->UseVisualStyleBackColor = true;
			// 
			// search_faculty_box
			// 
			resources->ApplyResources(this->search_faculty_box, L"search_faculty_box");
			this->search_faculty_box->Name = L"search_faculty_box";
			// 
			// label4
			// 
			resources->ApplyResources(this->label4, L"label4");
			this->label4->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->label4->Name = L"label4";
			// 
			// faculty_checkBox
			// 
			resources->ApplyResources(this->faculty_checkBox, L"faculty_checkBox");
			this->faculty_checkBox->Name = L"faculty_checkBox";
			this->faculty_checkBox->UseVisualStyleBackColor = true;
			// 
			// search_grupp_box
			// 
			resources->ApplyResources(this->search_grupp_box, L"search_grupp_box");
			this->search_grupp_box->Name = L"search_grupp_box";
			// 
			// grupp_checkBox
			// 
			resources->ApplyResources(this->grupp_checkBox, L"grupp_checkBox");
			this->grupp_checkBox->Name = L"grupp_checkBox";
			this->grupp_checkBox->UseVisualStyleBackColor = true;
			// 
			// rate_checkBox
			// 
			resources->ApplyResources(this->rate_checkBox, L"rate_checkBox");
			this->rate_checkBox->Name = L"rate_checkBox";
			this->rate_checkBox->UseVisualStyleBackColor = true;
			// 
			// soz_act_checkBox
			// 
			resources->ApplyResources(this->soz_act_checkBox, L"soz_act_checkBox");
			this->soz_act_checkBox->Name = L"soz_act_checkBox";
			this->soz_act_checkBox->UseVisualStyleBackColor = true;
			// 
			// new_rating_box
			// 
			resources->ApplyResources(this->new_rating_box, L"new_rating_box");
			this->new_rating_box->Name = L"new_rating_box";
			// 
			// search_soz_act_box
			// 
			this->search_soz_act_box->FormattingEnabled = true;
			this->search_soz_act_box->Items->AddRange(gcnew cli::array< System::Object^  >(3) {
				resources->GetString(L"search_soz_act_box.Items"),
					resources->GetString(L"search_soz_act_box.Items1"), resources->GetString(L"search_soz_act_box.Items2")
			});
			resources->ApplyResources(this->search_soz_act_box, L"search_soz_act_box");
			this->search_soz_act_box->Name = L"search_soz_act_box";
			this->search_soz_act_box->ItemCheck += gcnew System::Windows::Forms::ItemCheckEventHandler(this, &zapros_form::search_soz_act_box_ItemCheck);
			// 
			// label5
			// 
			resources->ApplyResources(this->label5, L"label5");
			this->label5->Name = L"label5";
			// 
			// Рейтинг
			// 
			resources->ApplyResources(this->Рейтинг, L"Рейтинг");
			this->Рейтинг->Name = L"Рейтинг";
			// 
			// label6
			// 
			resources->ApplyResources(this->label6, L"label6");
			this->label6->Name = L"label6";
			// 
			// back_from_ch_str
			// 
			this->back_from_ch_str->BackColor = System::Drawing::SystemColors::InactiveCaption;
			resources->ApplyResources(this->back_from_ch_str, L"back_from_ch_str");
			this->back_from_ch_str->Name = L"back_from_ch_str";
			this->back_from_ch_str->UseVisualStyleBackColor = false;
			this->back_from_ch_str->Click += gcnew System::EventHandler(this, &zapros_form::back_from_ch_str_Click);
			// 
			// search_button
			// 
			this->search_button->BackColor = System::Drawing::SystemColors::InactiveCaption;
			resources->ApplyResources(this->search_button, L"search_button");
			this->search_button->Name = L"search_button";
			this->search_button->UseVisualStyleBackColor = false;
			this->search_button->Click += gcnew System::EventHandler(this, &zapros_form::search_button_Click);
			// 
			// label7
			// 
			resources->ApplyResources(this->label7, L"label7");
			this->label7->Name = L"label7";
			// 
			// rate_bol_zad
			// 
			resources->ApplyResources(this->rate_bol_zad, L"rate_bol_zad");
			this->rate_bol_zad->Name = L"rate_bol_zad";
			this->rate_bol_zad->TabStop = true;
			this->rate_bol_zad->UseVisualStyleBackColor = true;
			// 
			// rate_rav_zad
			// 
			resources->ApplyResources(this->rate_rav_zad, L"rate_rav_zad");
			this->rate_rav_zad->Name = L"rate_rav_zad";
			this->rate_rav_zad->TabStop = true;
			this->rate_rav_zad->UseVisualStyleBackColor = true;
			// 
			// rate_men_zad
			// 
			resources->ApplyResources(this->rate_men_zad, L"rate_men_zad");
			this->rate_men_zad->Name = L"rate_men_zad";
			this->rate_men_zad->TabStop = true;
			this->rate_men_zad->UseVisualStyleBackColor = true;
			// 
			// rate_grupp_box
			// 
			this->rate_grupp_box->Controls->Add(this->rate_bol_zad);
			this->rate_grupp_box->Controls->Add(this->rate_men_zad);
			this->rate_grupp_box->Controls->Add(this->rate_rav_zad);
			resources->ApplyResources(this->rate_grupp_box, L"rate_grupp_box");
			this->rate_grupp_box->Name = L"rate_grupp_box";
			this->rate_grupp_box->TabStop = false;
			// 
			// soz_grupp_box
			// 
			this->soz_grupp_box->Controls->Add(this->soz_men_zad);
			this->soz_grupp_box->Controls->Add(this->soz_rav_zad);
			this->soz_grupp_box->Controls->Add(this->soz_bol_zad);
			resources->ApplyResources(this->soz_grupp_box, L"soz_grupp_box");
			this->soz_grupp_box->Name = L"soz_grupp_box";
			this->soz_grupp_box->TabStop = false;
			// 
			// soz_men_zad
			// 
			resources->ApplyResources(this->soz_men_zad, L"soz_men_zad");
			this->soz_men_zad->Name = L"soz_men_zad";
			this->soz_men_zad->TabStop = true;
			this->soz_men_zad->UseVisualStyleBackColor = true;
			// 
			// soz_rav_zad
			// 
			resources->ApplyResources(this->soz_rav_zad, L"soz_rav_zad");
			this->soz_rav_zad->Name = L"soz_rav_zad";
			this->soz_rav_zad->TabStop = true;
			this->soz_rav_zad->UseVisualStyleBackColor = true;
			// 
			// soz_bol_zad
			// 
			resources->ApplyResources(this->soz_bol_zad, L"soz_bol_zad");
			this->soz_bol_zad->Name = L"soz_bol_zad";
			this->soz_bol_zad->TabStop = true;
			this->soz_bol_zad->UseVisualStyleBackColor = true;
			// 
			// date_grupp
			// 
			this->date_grupp->Controls->Add(this->date_bol_zad);
			this->date_grupp->Controls->Add(this->date_men_zad);
			this->date_grupp->Controls->Add(this->date_rav_zad);
			resources->ApplyResources(this->date_grupp, L"date_grupp");
			this->date_grupp->Name = L"date_grupp";
			this->date_grupp->TabStop = false;
			// 
			// date_bol_zad
			// 
			resources->ApplyResources(this->date_bol_zad, L"date_bol_zad");
			this->date_bol_zad->Name = L"date_bol_zad";
			this->date_bol_zad->TabStop = true;
			this->date_bol_zad->UseVisualStyleBackColor = true;
			// 
			// date_men_zad
			// 
			resources->ApplyResources(this->date_men_zad, L"date_men_zad");
			this->date_men_zad->Name = L"date_men_zad";
			this->date_men_zad->TabStop = true;
			this->date_men_zad->UseVisualStyleBackColor = true;
			// 
			// date_rav_zad
			// 
			resources->ApplyResources(this->date_rav_zad, L"date_rav_zad");
			this->date_rav_zad->Name = L"date_rav_zad";
			this->date_rav_zad->TabStop = true;
			this->date_rav_zad->UseVisualStyleBackColor = true;
			// 
			// zapros_form
			// 
			resources->ApplyResources(this, L"$this");
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Silver;
			this->Controls->Add(this->date_grupp);
			this->Controls->Add(this->soz_grupp_box);
			this->Controls->Add(this->rate_grupp_box);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->search_button);
			this->Controls->Add(this->back_from_ch_str);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->Рейтинг);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->search_soz_act_box);
			this->Controls->Add(this->new_rating_box);
			this->Controls->Add(this->soz_act_checkBox);
			this->Controls->Add(this->rate_checkBox);
			this->Controls->Add(this->grupp_checkBox);
			this->Controls->Add(this->search_grupp_box);
			this->Controls->Add(this->faculty_checkBox);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->search_faculty_box);
			this->Controls->Add(this->search_data_checkBox);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->search_data);
			this->Controls->Add(this->pol_checkBox);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->search_pol_box);
			this->Controls->Add(this->FIO_checkBox);
			this->Controls->Add(this->search_FIO_box);
			this->Controls->Add(this->label1);
			this->Name = L"zapros_form";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->new_rating_box))->EndInit();
			this->rate_grupp_box->ResumeLayout(false);
			this->rate_grupp_box->PerformLayout();
			this->soz_grupp_box->ResumeLayout(false);
			this->soz_grupp_box->PerformLayout();
			this->date_grupp->ResumeLayout(false);
			this->date_grupp->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void search_button_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void back_from_ch_str_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Close();
	}
	private: System::Void rate_bol_zad_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void search_pol_box_ItemCheck(System::Object^ sender, System::Windows::Forms::ItemCheckEventArgs^ e);

	private: System::Void search_soz_act_box_ItemCheck(System::Object^ sender, System::Windows::Forms::ItemCheckEventArgs^ e);
	};
}
