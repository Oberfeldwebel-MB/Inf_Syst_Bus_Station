// AddDriverForm.h
#pragma once

#include "DriversList.hpp"
#include "DriverValidator.hpp"

namespace InfSystBusStation {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    /// <summary>
    /// Форма для добавления водителя
    /// </summary>
    public ref class AddDriverForm : public System::Windows::Forms::Form
    {
    public:
        event EventHandler^ DataAdded;

    public:
        AddDriverForm(void)
        {
            InitializeComponent();
            driverList = nullptr;
            InitializeForm();
        }

    protected:
        ~AddDriverForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        DriversList^ driverList;
        System::ComponentModel::Container^ components;

        // Инициализация формы
        void InitializeForm()
        {
            ratingNumericUpDown->Value = 30000;


            FIO_add->Clear();
            maskedTextBox1->Clear();
            data_add->Clear();
            pol_add->SetItemChecked(0, false);
            pol_add->SetItemChecked(1, false);

 
            FIO_add->Focus();
        }

    public:
        // Метод для установки списка водителей
        void SetDriverList(DriversList^ list) {
            driverList = list;
        }

        // Элементы формы
    public:
        System::Windows::Forms::MaskedTextBox^ data_add;
        System::Windows::Forms::MaskedTextBox^ FIO_add;
        System::Windows::Forms::Label^ fio_add_label;
        System::Windows::Forms::Label^ pol_add_label;
        System::Windows::Forms::CheckedListBox^ pol_add;
        System::Windows::Forms::Label^ faculty_add_label;
        System::Windows::Forms::Button^ AddButtonDriver;
        System::Windows::Forms::Button^ BackButDriver;
        System::Windows::Forms::NumericUpDown^ ratingNumericUpDown;
        System::Windows::Forms::Label^ label4;
        System::Windows::Forms::Label^ label5;
        System::Windows::Forms::MaskedTextBox^ maskedTextBox1;

    private:
        System::Windows::Forms::Label^ label1;
        System::Windows::Forms::Label^ label2;

#pragma region Windows Form Designer generated code
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
            this->AddButtonDriver = (gcnew System::Windows::Forms::Button());
            this->BackButDriver = (gcnew System::Windows::Forms::Button());
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
            this->data_add->TabIndex = 2;
            this->data_add->ValidatingType = System::DateTime::typeid;
            // 
            // FIO_add
            // 
            this->FIO_add->Location = System::Drawing::Point(84, 127);
            this->FIO_add->Mask = L">L.L. A<AAAAAAAAAA";
            this->FIO_add->Name = L"FIO_add";
            this->FIO_add->Size = System::Drawing::Size(111, 22);
            this->FIO_add->TabIndex = 0;
            // 
            // fio_add_label
            // 
            this->fio_add_label->AutoSize = true;
            this->fio_add_label->Location = System::Drawing::Point(81, 84);
            this->fio_add_label->Name = L"fio_add_label";
            this->fio_add_label->Size = System::Drawing::Size(42, 16);
            this->fio_add_label->TabIndex = 2;
            this->fio_add_label->Text = L"ФИО";
            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->Location = System::Drawing::Point(84, 255);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(165, 16);
            this->label1->TabIndex = 3;
            this->label1->Text = L"Серия и номер паспорта";
            // 
            // pol_add_label
            // 
            this->pol_add_label->AutoSize = true;
            this->pol_add_label->Location = System::Drawing::Point(87, 164);
            this->pol_add_label->Name = L"pol_add_label";
            this->pol_add_label->Size = System::Drawing::Size(30, 16);
            this->pol_add_label->TabIndex = 4;
            this->pol_add_label->Text = L"Пол";
            // 
            // pol_add
            // 
            this->pol_add->CheckOnClick = true;
            this->pol_add->FormattingEnabled = true;
            this->pol_add->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Мужской", L"Женский" });
            this->pol_add->Location = System::Drawing::Point(87, 186);
            this->pol_add->Name = L"pol_add";
            this->pol_add->Size = System::Drawing::Size(108, 55);
            this->pol_add->TabIndex = 1;
            this->pol_add->ItemCheck += gcnew System::Windows::Forms::ItemCheckEventHandler(this, &AddDriverForm::pol_add_ItemCheck);
            // 
            // faculty_add_label
            // 
            this->faculty_add_label->AutoSize = true;
            this->faculty_add_label->Location = System::Drawing::Point(81, 342);
            this->faculty_add_label->Name = L"faculty_add_label";
            this->faculty_add_label->Size = System::Drawing::Size(87, 16);
            this->faculty_add_label->TabIndex = 7;
            this->faculty_add_label->Text = L"Номер ВУ";
            // 
            // label2
            // 
            this->label2->AutoSize = true;
            this->label2->Location = System::Drawing::Point(415, 84);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(0, 16);
            this->label2->TabIndex = 10;
            // 
            // AddButtonDriver
            // 
            this->AddButtonDriver->BackColor = System::Drawing::SystemColors::InactiveCaption;
            this->AddButtonDriver->Location = System::Drawing::Point(604, 396);
            this->AddButtonDriver->Name = L"AddButtonDriver";
            this->AddButtonDriver->Size = System::Drawing::Size(95, 32);
            this->AddButtonDriver->TabIndex = 4;
            this->AddButtonDriver->Text = L"Добавить";
            this->AddButtonDriver->UseVisualStyleBackColor = false;
            this->AddButtonDriver->Click += gcnew System::EventHandler(this, &AddDriverForm::AddButtonDriver_Click);
            // 
            // BackButDriver
            // 
            this->BackButDriver->BackColor = System::Drawing::SystemColors::InactiveCaption;
            this->BackButDriver->Location = System::Drawing::Point(604, 446);
            this->BackButDriver->Name = L"BackButDriver";
            this->BackButDriver->Size = System::Drawing::Size(95, 33);
            this->BackButDriver->TabIndex = 5;
            this->BackButDriver->Text = L"Назад";
            this->BackButDriver->UseVisualStyleBackColor = false;
            this->BackButDriver->Click += gcnew System::EventHandler(this, &AddDriverForm::BackButDriver_Click);
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
            this->ratingNumericUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000000, 0, 0, 0 });
            this->ratingNumericUpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10000, 0, 0, 0 });
            this->ratingNumericUpDown->Name = L"ratingNumericUpDown";
            this->ratingNumericUpDown->Size = System::Drawing::Size(120, 22);
            this->ratingNumericUpDown->TabIndex = 3;
            this->ratingNumericUpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 30000, 0, 0, 0 });
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
            this->maskedTextBox1->Mask = L"AA000000";
            this->maskedTextBox1->Name = L"maskedTextBox1";
            this->maskedTextBox1->Size = System::Drawing::Size(86, 22);
            this->maskedTextBox1->TabIndex = 6;
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
            this->Controls->Add(this->BackButDriver);
            this->Controls->Add(this->AddButtonDriver);
            this->Controls->Add(this->label2);
            this->Controls->Add(this->faculty_add_label);
            this->Controls->Add(this->pol_add);
            this->Controls->Add(this->pol_add_label);
            this->Controls->Add(this->label1);
            this->Controls->Add(this->fio_add_label);
            this->Controls->Add(this->FIO_add);
            this->Controls->Add(this->data_add);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->MaximizeBox = false;
            this->MinimizeBox = false;
            this->Name = L"AddDriverForm";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
            this->Text = L"Добавить водителя";
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ratingNumericUpDown))->EndInit();
            this->ResumeLayout(false);
            this->PerformLayout();
        }
#pragma endregion

    public:
        System::Void AddButtonDriver_Click(System::Object^ sender, System::EventArgs^ e);

    private:
        System::Void AddDriverForm::BackButDriver_Click(System::Object^ sender, System::EventArgs^ e) {
       
            this->Close();

        }

        System::Void pol_add_ItemCheck(System::Object^ sender, System::Windows::Forms::ItemCheckEventArgs^ e) {
            CheckedListBox^ listBox = (CheckedListBox^)sender;

            if (e->NewValue == CheckState::Checked) {
                for (int i = 0; i < listBox->Items->Count; i++) {
                    if (i != e->Index) {
                        listBox->SetItemChecked(i, false);
                    }
                }
            }
        }
    };
}