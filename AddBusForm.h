// AddBusForm.h
#pragma once

#include "Bus.hpp"
#include "BusList.hpp"
#include "BusValidator.hpp"

namespace InfSystBusStation {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    /// <summary>
    /// Форма для добавления автобуса
    /// </summary>
    public ref class AddBusForm : public System::Windows::Forms::Form {
    public:
        event System::EventHandler^ DataAdded;

    public:
        AddBusForm(void) {
            InitializeComponent();
            busList = nullptr;
            InitializeForm();
        }

    protected:
        ~AddBusForm() {
            if (components) {
                delete components;
            }
        }

    private:
        BusList^ busList;  // Правильное название - BusList
        System::ComponentModel::Container^ components;

        void InitializeForm() {
            // Очищаем поля
            BrandBox->Clear();
            ModelBox->Clear();
            CountPlaceBox->Clear();
            BusNumBox->Clear();
            TechSostBox->Clear();
            DateTOAddBox->Clear();

            // Устанавливаем фокус
            BrandBox->Focus();
        }

    public:
        // Метод для установки списка автобусов
        void SetBusList(BusList^ list) {
            busList = list;
        }

        // Элементы формы
    public:
        System::Windows::Forms::MaskedTextBox^ DateTOAddBox;
        System::Windows::Forms::Label^ fio_add_label;
        System::Windows::Forms::Label^ label1;
        System::Windows::Forms::Label^ pol_add_label;
        System::Windows::Forms::TextBox^ CountPlaceBox;
        System::Windows::Forms::Label^ faculty_add_label;
        System::Windows::Forms::TextBox^ TechSostBox;
        System::Windows::Forms::Label^ label2;
        System::Windows::Forms::Button^ AddBusButton;
        System::Windows::Forms::Button^ BackAddBus;
        System::Windows::Forms::Label^ label5;
        System::Windows::Forms::TextBox^ BrandBox;
        System::Windows::Forms::TextBox^ ModelBox;
        System::Windows::Forms::Label^ label3;
        System::Windows::Forms::MaskedTextBox^ BusNumBox;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void) {
            this->DateTOAddBox = (gcnew System::Windows::Forms::MaskedTextBox());
            this->fio_add_label = (gcnew System::Windows::Forms::Label());
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->pol_add_label = (gcnew System::Windows::Forms::Label());
            this->CountPlaceBox = (gcnew System::Windows::Forms::TextBox());
            this->faculty_add_label = (gcnew System::Windows::Forms::Label());
            this->TechSostBox = (gcnew System::Windows::Forms::TextBox());
            this->label2 = (gcnew System::Windows::Forms::Label());
            this->AddBusButton = (gcnew System::Windows::Forms::Button());
            this->BackAddBus = (gcnew System::Windows::Forms::Button());
            this->label5 = (gcnew System::Windows::Forms::Label());
            this->BrandBox = (gcnew System::Windows::Forms::TextBox());
            this->ModelBox = (gcnew System::Windows::Forms::TextBox());
            this->label3 = (gcnew System::Windows::Forms::Label());
            this->BusNumBox = (gcnew System::Windows::Forms::MaskedTextBox());
            this->SuspendLayout();

            // DateTOAddBox
            this->DateTOAddBox->Location = System::Drawing::Point(84, 293);
            this->DateTOAddBox->Mask = L"00/00/0000";
            this->DateTOAddBox->Name = L"DateTOAddBox";
            this->DateTOAddBox->Size = System::Drawing::Size(86, 22);
            this->DateTOAddBox->TabIndex = 4;
            this->DateTOAddBox->ValidatingType = System::DateTime::typeid;

            // fio_add_label
            this->fio_add_label->AutoSize = true;
            this->fio_add_label->Location = System::Drawing::Point(81, 84);
            this->fio_add_label->Name = L"fio_add_label";
            this->fio_add_label->Size = System::Drawing::Size(46, 16);
            this->fio_add_label->TabIndex = 2;
            this->fio_add_label->Text = L"Марка";

            // label1
            this->label1->AutoSize = true;
            this->label1->Location = System::Drawing::Point(84, 255);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(215, 16);
            this->label1->TabIndex = 3;
            this->label1->Text = L"Дата прохождения последнего ТО";

            // pol_add_label
            this->pol_add_label->AutoSize = true;
            this->pol_add_label->Location = System::Drawing::Point(87, 164);
            this->pol_add_label->Name = L"pol_add_label";
            this->pol_add_label->Size = System::Drawing::Size(54, 16);
            this->pol_add_label->TabIndex = 4;
            this->pol_add_label->Text = L"Модель";

            // CountPlaceBox
            this->CountPlaceBox->Location = System::Drawing::Point(84, 383);
            this->CountPlaceBox->Name = L"CountPlaceBox";
            this->CountPlaceBox->Size = System::Drawing::Size(86, 22);
            this->CountPlaceBox->TabIndex = 6;

            // faculty_add_label
            this->faculty_add_label->AutoSize = true;
            this->faculty_add_label->Location = System::Drawing::Point(81, 348);
            this->faculty_add_label->Name = L"faculty_add_label";
            this->faculty_add_label->Size = System::Drawing::Size(112, 16);
            this->faculty_add_label->TabIndex = 7;
            this->faculty_add_label->Text = L"Количество мест";

            // TechSostBox
            this->TechSostBox->Location = System::Drawing::Point(418, 127);
            this->TechSostBox->Name = L"TechSostBox";
            this->TechSostBox->Size = System::Drawing::Size(120, 22);
            this->TechSostBox->TabIndex = 2;

            // label2
            this->label2->AutoSize = true;
            this->label2->Location = System::Drawing::Point(415, 84);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(163, 16);
            this->label2->TabIndex = 10;
            this->label2->Text = L"Техническое состояние";

            // AddBusButton
            this->AddBusButton->BackColor = System::Drawing::SystemColors::InactiveCaption;
            this->AddBusButton->Location = System::Drawing::Point(604, 396);
            this->AddBusButton->Name = L"AddBusButton";
            this->AddBusButton->Size = System::Drawing::Size(95, 32);
            this->AddBusButton->TabIndex = 7;
            this->AddBusButton->Text = L"Добавить";
            this->AddBusButton->UseVisualStyleBackColor = false;
            this->AddBusButton->Click += gcnew System::EventHandler(this, &AddBusForm::AddBusButton_Click);

            // BackAddBus
            this->BackAddBus->BackColor = System::Drawing::SystemColors::InactiveCaption;
            this->BackAddBus->Location = System::Drawing::Point(604, 446);
            this->BackAddBus->Name = L"BackAddBus";
            this->BackAddBus->Size = System::Drawing::Size(95, 33);
            this->BackAddBus->TabIndex = 8;
            this->BackAddBus->Text = L"Назад";
            this->BackAddBus->UseVisualStyleBackColor = false;
            this->BackAddBus->Click += gcnew System::EventHandler(this, &AddBusForm::BackAddBus_Click);

            // label5
            this->label5->AutoSize = true;
            this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label5->Location = System::Drawing::Point(87, 23);
            this->label5->Name = L"label5";
            this->label5->Size = System::Drawing::Size(527, 20);
            this->label5->TabIndex = 17;
            this->label5->Text = L"Внесите данные об автобусе для добавления в список";

            // BrandBox
            this->BrandBox->Location = System::Drawing::Point(84, 127);
            this->BrandBox->Name = L"BrandBox";
            this->BrandBox->Size = System::Drawing::Size(111, 22);
            this->BrandBox->TabIndex = 0;

            // ModelBox
            this->ModelBox->Location = System::Drawing::Point(84, 207);
            this->ModelBox->Name = L"ModelBox";
            this->ModelBox->Size = System::Drawing::Size(111, 22);
            this->ModelBox->TabIndex = 1;

            // label3
            this->label3->AutoSize = true;
            this->label3->Location = System::Drawing::Point(415, 164);
            this->label3->Name = L"label3";
            this->label3->Size = System::Drawing::Size(96, 16);
            this->label3->TabIndex = 23;
            this->label3->Text = L"Код автобуса";

            // BusNumBox
            this->BusNumBox->Location = System::Drawing::Point(418, 207);
            this->BusNumBox->Mask = L"L/000/LL";
            this->BusNumBox->Name = L"BusNumBox";
            this->BusNumBox->Size = System::Drawing::Size(100, 22);
            this->BusNumBox->TabIndex = 3;

            // AddBusForm
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->BackColor = System::Drawing::SystemColors::AppWorkspace;
            this->ClientSize = System::Drawing::Size(754, 506);
            this->Controls->Add(this->BusNumBox);
            this->Controls->Add(this->label3);
            this->Controls->Add(this->ModelBox);
            this->Controls->Add(this->BrandBox);
            this->Controls->Add(this->label5);
            this->Controls->Add(this->BackAddBus);
            this->Controls->Add(this->AddBusButton);
            this->Controls->Add(this->label2);
            this->Controls->Add(this->TechSostBox);
            this->Controls->Add(this->faculty_add_label);
            this->Controls->Add(this->CountPlaceBox);
            this->Controls->Add(this->pol_add_label);
            this->Controls->Add(this->label1);
            this->Controls->Add(this->fio_add_label);
            this->Controls->Add(this->DateTOAddBox);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->MaximizeBox = false;
            this->MinimizeBox = false;
            this->Name = L"AddBusForm";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
            this->Text = L"Добавить автобус";
            this->ResumeLayout(false);
            this->PerformLayout();
        }
#pragma endregion

    public:
        System::Void AddBusButton_Click(System::Object^ sender, System::EventArgs^ e);

    private:
        System::Void BackAddBus_Click(System::Object^ sender, System::EventArgs^ e) {
            this->Close();
        }
    };
}