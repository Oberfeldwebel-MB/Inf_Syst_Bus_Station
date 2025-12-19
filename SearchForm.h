#pragma once

#include "TripList.hpp"
#include "BusList.hpp"
#include "DriversList.hpp"

namespace InfSystBusStation {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::Collections::Generic;

    public ref class SearchForm : public System::Windows::Forms::Form {
    public:
        SearchForm::SearchForm(TripList^ tripList, BusList^ busList, DriversList^ driverList) {
            InitializeComponent();
            this->tripList = tripList;
            this->busList = busList;
            this->driverList = driverList;
            this->searchResults = nullptr;
            InitializeForm();
            LoadDriverComboBox(); 
            LoadBusComboBox();     
        }

        property List<Trip^>^ SearchResults {
            List<Trip^>^ get() { return searchResults; }
        }

    protected:
        ~SearchForm() {
            if (components) {
                delete components;
            }
        }

    private:
        TripList^ tripList;
        BusList^ busList;
        DriversList^ driverList;
        List<Trip^>^ searchResults;

    private:
        System::Windows::Forms::CheckBox^ checkStartBox;
    private: System::Windows::Forms::CheckBox^ checkFinishBox;
    private: System::Windows::Forms::CheckBox^ checkDateStartBox;
    private: System::Windows::Forms::CheckBox^ checkDateFinishBox;
    private: System::Windows::Forms::CheckBox^ checkPriceBox;
    private: System::Windows::Forms::CheckBox^ checkDriverBox;
    private: System::Windows::Forms::CheckBox^ checkBusBox;

           System::ComponentModel::Container^ components;

           void InitializeForm() {
               // Очищаем поля
               StartPointBox->Clear();
               FinishPointBox->Clear();
               DepDateBox->Clear();
               ArrDateBox->Clear();
               PriceBox->Clear();
               driverComboBox->SelectedIndex = -1;
               busComboBox->SelectedIndex = -1;

               // Отключаем поля по умолчанию
               StartPointBox->Enabled = false;
               FinishPointBox->Enabled = false;
               DepDateBox->Enabled = false;
               ArrDateBox->Enabled = false;
               PriceBox->Enabled = false;
               driverComboBox->Enabled = false;
               busComboBox->Enabled = false;

               // Устанавливаем фокус
               checkStartBox->Focus();
           }

    public:
        // Методы для установки списков
        void SetTripList(TripList^ list) {
            tripList = list;
        }

        void SetBusList(BusList^ list) {
            busList = list;
            LoadBusComboBox();
        }

        void SetDriverList(DriversList^ list) {
            driverList = list;
            LoadDriverComboBox();
        }

        // Элементы формы
    public:
        System::Windows::Forms::MaskedTextBox^ DepDateBox;
        System::Windows::Forms::Label^ fio_add_label;
        System::Windows::Forms::Label^ label1;
        System::Windows::Forms::Label^ pol_add_label;
        System::Windows::Forms::Label^ faculty_add_label;
        System::Windows::Forms::Label^ label2;
        System::Windows::Forms::Button^ SearchFormButton;
        System::Windows::Forms::Button^ back_add;
        System::Windows::Forms::Label^ label4;
        System::Windows::Forms::TextBox^ PriceBox;
        System::Windows::Forms::Label^ label5;
        System::Windows::Forms::MaskedTextBox^ ArrDateBox;
        System::Windows::Forms::TextBox^ StartPointBox;
        System::Windows::Forms::TextBox^ FinishPointBox;

        // элементы для выбора водителя и автобуса
        System::Windows::Forms::Label^ driverLabel;
        System::Windows::Forms::ComboBox^ driverComboBox;
        System::Windows::Forms::Label^ busLabel;
        System::Windows::Forms::ComboBox^ busComboBox;

    private:
        // Методы загрузки ComboBox
        void LoadDriverComboBox();
        void LoadBusComboBox();

#pragma region Windows Form Designer generated code
        void InitializeComponent(void) {
            this->DepDateBox = (gcnew System::Windows::Forms::MaskedTextBox());
            this->fio_add_label = (gcnew System::Windows::Forms::Label());
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->pol_add_label = (gcnew System::Windows::Forms::Label());
            this->faculty_add_label = (gcnew System::Windows::Forms::Label());
            this->label2 = (gcnew System::Windows::Forms::Label());
            this->SearchFormButton = (gcnew System::Windows::Forms::Button());
            this->back_add = (gcnew System::Windows::Forms::Button());
            this->label4 = (gcnew System::Windows::Forms::Label());
            this->PriceBox = (gcnew System::Windows::Forms::TextBox());
            this->label5 = (gcnew System::Windows::Forms::Label());
            this->ArrDateBox = (gcnew System::Windows::Forms::MaskedTextBox());
            this->StartPointBox = (gcnew System::Windows::Forms::TextBox());
            this->FinishPointBox = (gcnew System::Windows::Forms::TextBox());
            this->driverLabel = (gcnew System::Windows::Forms::Label());
            this->driverComboBox = (gcnew System::Windows::Forms::ComboBox());
            this->busLabel = (gcnew System::Windows::Forms::Label());
            this->busComboBox = (gcnew System::Windows::Forms::ComboBox());
            this->checkStartBox = (gcnew System::Windows::Forms::CheckBox());
            this->checkFinishBox = (gcnew System::Windows::Forms::CheckBox());
            this->checkDateStartBox = (gcnew System::Windows::Forms::CheckBox());
            this->checkDateFinishBox = (gcnew System::Windows::Forms::CheckBox());
            this->checkPriceBox = (gcnew System::Windows::Forms::CheckBox());
            this->checkDriverBox = (gcnew System::Windows::Forms::CheckBox());
            this->checkBusBox = (gcnew System::Windows::Forms::CheckBox());
            this->SuspendLayout();
            // 
            // DepDateBox
            // 
            this->DepDateBox->Location = System::Drawing::Point(84, 293);
            this->DepDateBox->Mask = L"00/00/0000 90:00";
            this->DepDateBox->Name = L"DepDateBox";
            this->DepDateBox->Size = System::Drawing::Size(150, 22);
            this->DepDateBox->TabIndex = 3;
            this->DepDateBox->ValidatingType = System::DateTime::typeid;
            this->DepDateBox->Enabled = false;
            // 
            // fio_add_label
            // 
            this->fio_add_label->AutoSize = true;
            this->fio_add_label->Location = System::Drawing::Point(81, 84);
            this->fio_add_label->Name = L"fio_add_label";
            this->fio_add_label->Size = System::Drawing::Size(136, 16);
            this->fio_add_label->TabIndex = 2;
            this->fio_add_label->Text = L"Пункт отправления";
            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->Location = System::Drawing::Point(84, 255);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(182, 16);
            this->label1->TabIndex = 3;
            this->label1->Text = L"Дата и время отправления";
            // 
            // pol_add_label
            // 
            this->pol_add_label->AutoSize = true;
            this->pol_add_label->Location = System::Drawing::Point(87, 164);
            this->pol_add_label->Name = L"pol_add_label";
            this->pol_add_label->Size = System::Drawing::Size(113, 16);
            this->pol_add_label->TabIndex = 4;
            this->pol_add_label->Text = L"Пункт прибытия";
            // 
            // faculty_add_label
            // 
            this->faculty_add_label->AutoSize = true;
            this->faculty_add_label->Location = System::Drawing::Point(81, 342);
            this->faculty_add_label->Name = L"faculty_add_label";
            this->faculty_add_label->Size = System::Drawing::Size(159, 16);
            this->faculty_add_label->TabIndex = 7;
            this->faculty_add_label->Text = L"Дата и время прибытия";
            // 
            // label2
            // 
            this->label2->AutoSize = true;
            this->label2->Location = System::Drawing::Point(415, 84);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(0, 16);
            this->label2->TabIndex = 10;
            // 
            // SearchFormButton
            // 
            this->SearchFormButton->BackColor = System::Drawing::SystemColors::InactiveCaption;
            this->SearchFormButton->Location = System::Drawing::Point(604, 396);
            this->SearchFormButton->Name = L"SearchFormButton";
            this->SearchFormButton->Size = System::Drawing::Size(95, 32);
            this->SearchFormButton->TabIndex = 8;
            this->SearchFormButton->Text = L"Найти";
            this->SearchFormButton->UseVisualStyleBackColor = false;
            this->SearchFormButton->Click += gcnew System::EventHandler(this, &SearchForm::SearchButton_Click);
            // 
            // back_add
            // 
            this->back_add->BackColor = System::Drawing::SystemColors::InactiveCaption;
            this->back_add->Location = System::Drawing::Point(604, 446);
            this->back_add->Name = L"back_add";
            this->back_add->Size = System::Drawing::Size(95, 33);
            this->back_add->TabIndex = 9;
            this->back_add->Text = L"Назад";
            this->back_add->UseVisualStyleBackColor = false;
            this->back_add->Click += gcnew System::EventHandler(this, &SearchForm::back_add_Click);
            // 
            // label4
            // 
            this->label4->AutoSize = true;
            this->label4->Location = System::Drawing::Point(421, 91);
            this->label4->Name = L"label4";
            this->label4->Size = System::Drawing::Size(40, 16);
            this->label4->TabIndex = 15;
            this->label4->Text = L"Цена";
            // 
            // PriceBox
            // 
            this->PriceBox->Location = System::Drawing::Point(423, 128);
            this->PriceBox->Name = L"PriceBox";
            this->PriceBox->Size = System::Drawing::Size(120, 22);
            this->PriceBox->TabIndex = 4;
            this->PriceBox->Enabled = false;
            // 
            // label5
            // 
            this->label5->AutoSize = true;
            this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label5->Location = System::Drawing::Point(87, 23);
            this->label5->Name = L"label5";
            this->label5->Size = System::Drawing::Size(428, 20);
            this->label5->TabIndex = 17;
            this->label5->Text = L"Введите критерии поиска поездок";
            // 
            // ArrDateBox
            // 
            this->ArrDateBox->Location = System::Drawing::Point(84, 384);
            this->ArrDateBox->Mask = L"00/00/0000 90:00";
            this->ArrDateBox->Name = L"ArrDateBox";
            this->ArrDateBox->Size = System::Drawing::Size(150, 22);
            this->ArrDateBox->TabIndex = 5;
            this->ArrDateBox->ValidatingType = System::DateTime::typeid;
            this->ArrDateBox->Enabled = false;
            // 
            // StartPointBox
            // 
            this->StartPointBox->Location = System::Drawing::Point(84, 127);
            this->StartPointBox->Name = L"StartPointBox";
            this->StartPointBox->Size = System::Drawing::Size(150, 22);
            this->StartPointBox->TabIndex = 0;
            this->StartPointBox->Enabled = false;
            // 
            // FinishPointBox
            // 
            this->FinishPointBox->Location = System::Drawing::Point(84, 206);
            this->FinishPointBox->Name = L"FinishPointBox";
            this->FinishPointBox->Size = System::Drawing::Size(150, 22);
            this->FinishPointBox->TabIndex = 1;
            this->FinishPointBox->Enabled = false;
            // 
            // driverLabel
            // 
            this->driverLabel->AutoSize = true;
            this->driverLabel->Location = System::Drawing::Point(421, 164);
            this->driverLabel->Name = L"driverLabel";
            this->driverLabel->Size = System::Drawing::Size(70, 16);
            this->driverLabel->TabIndex = 24;
            this->driverLabel->Text = L"Водитель";
            // 
            // driverComboBox
            // 
            this->driverComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->driverComboBox->FormattingEnabled = true;
            this->driverComboBox->Location = System::Drawing::Point(423, 206);
            this->driverComboBox->Name = L"driverComboBox";
            this->driverComboBox->Size = System::Drawing::Size(200, 24);
            this->driverComboBox->TabIndex = 6;
            this->driverComboBox->Enabled = false;
            // 
            // busLabel
            // 
            this->busLabel->AutoSize = true;
            this->busLabel->Location = System::Drawing::Point(421, 255);
            this->busLabel->Name = L"busLabel";
            this->busLabel->Size = System::Drawing::Size(62, 16);
            this->busLabel->TabIndex = 26;
            this->busLabel->Text = L"Автобус";
            // 
            // busComboBox
            // 
            this->busComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->busComboBox->FormattingEnabled = true;
            this->busComboBox->Location = System::Drawing::Point(423, 293);
            this->busComboBox->Name = L"busComboBox";
            this->busComboBox->Size = System::Drawing::Size(200, 24);
            this->busComboBox->TabIndex = 7;
            this->busComboBox->Enabled = false;
            // 
            // checkStartBox
            // 
            this->checkStartBox->AutoSize = true;
            this->checkStartBox->Location = System::Drawing::Point(32, 83);
            this->checkStartBox->Name = L"checkStartBox";
            this->checkStartBox->Size = System::Drawing::Size(18, 17);
            this->checkStartBox->TabIndex = 27;
            this->checkStartBox->UseVisualStyleBackColor = true;
            this->checkStartBox->CheckedChanged += gcnew System::EventHandler(this, &SearchForm::checkStartBox_CheckedChanged);
            // 
            // checkFinishBox
            // 
            this->checkFinishBox->AutoSize = true;
            this->checkFinishBox->Location = System::Drawing::Point(32, 163);
            this->checkFinishBox->Name = L"checkFinishBox";
            this->checkFinishBox->Size = System::Drawing::Size(18, 17);
            this->checkFinishBox->TabIndex = 28;
            this->checkFinishBox->UseVisualStyleBackColor = true;
            this->checkFinishBox->CheckedChanged += gcnew System::EventHandler(this, &SearchForm::checkFinishBox_CheckedChanged);
            // 
            // checkDateStartBox
            // 
            this->checkDateStartBox->AutoSize = true;
            this->checkDateStartBox->Location = System::Drawing::Point(32, 256);
            this->checkDateStartBox->Name = L"checkDateStartBox";
            this->checkDateStartBox->Size = System::Drawing::Size(18, 17);
            this->checkDateStartBox->TabIndex = 29;
            this->checkDateStartBox->UseVisualStyleBackColor = true;
            this->checkDateStartBox->CheckedChanged += gcnew System::EventHandler(this, &SearchForm::checkDateStartBox_CheckedChanged);
            // 
            // checkDateFinishBox
            // 
            this->checkDateFinishBox->AutoSize = true;
            this->checkDateFinishBox->Location = System::Drawing::Point(32, 341);
            this->checkDateFinishBox->Name = L"checkDateFinishBox";
            this->checkDateFinishBox->Size = System::Drawing::Size(18, 17);
            this->checkDateFinishBox->TabIndex = 30;
            this->checkDateFinishBox->UseVisualStyleBackColor = true;
            this->checkDateFinishBox->CheckedChanged += gcnew System::EventHandler(this, &SearchForm::checkDateFinishBox_CheckedChanged);
            // 
            // checkPriceBox
            // 
            this->checkPriceBox->AutoSize = true;
            this->checkPriceBox->Location = System::Drawing::Point(380, 90);
            this->checkPriceBox->Name = L"checkPriceBox";
            this->checkPriceBox->Size = System::Drawing::Size(18, 17);
            this->checkPriceBox->TabIndex = 31;
            this->checkPriceBox->UseVisualStyleBackColor = true;
            this->checkPriceBox->CheckedChanged += gcnew System::EventHandler(this, &SearchForm::checkPriceBox_CheckedChanged);
            // 
            // checkDriverBox
            // 
            this->checkDriverBox->AutoSize = true;
            this->checkDriverBox->Location = System::Drawing::Point(380, 163);
            this->checkDriverBox->Name = L"checkDriverBox";
            this->checkDriverBox->Size = System::Drawing::Size(18, 17);
            this->checkDriverBox->TabIndex = 32;
            this->checkDriverBox->UseVisualStyleBackColor = true;
            this->checkDriverBox->CheckedChanged += gcnew System::EventHandler(this, &SearchForm::checkDriverBox_CheckedChanged);
            // 
            // checkBusBox
            // 
            this->checkBusBox->AutoSize = true;
            this->checkBusBox->Location = System::Drawing::Point(380, 254);
            this->checkBusBox->Name = L"checkBusBox";
            this->checkBusBox->Size = System::Drawing::Size(18, 17);
            this->checkBusBox->TabIndex = 33;
            this->checkBusBox->UseVisualStyleBackColor = true;
            this->checkBusBox->CheckedChanged += gcnew System::EventHandler(this, &SearchForm::checkBusBox_CheckedChanged);
            // 
            // SearchForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->BackColor = System::Drawing::SystemColors::AppWorkspace;
            this->ClientSize = System::Drawing::Size(754, 506);
            this->Controls->Add(this->checkBusBox);
            this->Controls->Add(this->checkDriverBox);
            this->Controls->Add(this->checkPriceBox);
            this->Controls->Add(this->checkDateFinishBox);
            this->Controls->Add(this->checkDateStartBox);
            this->Controls->Add(this->checkFinishBox);
            this->Controls->Add(this->checkStartBox);
            this->Controls->Add(this->busComboBox);
            this->Controls->Add(this->busLabel);
            this->Controls->Add(this->driverComboBox);
            this->Controls->Add(this->driverLabel);
            this->Controls->Add(this->FinishPointBox);
            this->Controls->Add(this->StartPointBox);
            this->Controls->Add(this->ArrDateBox);
            this->Controls->Add(this->label5);
            this->Controls->Add(this->PriceBox);
            this->Controls->Add(this->label4);
            this->Controls->Add(this->back_add);
            this->Controls->Add(this->SearchFormButton);
            this->Controls->Add(this->label2);
            this->Controls->Add(this->faculty_add_label);
            this->Controls->Add(this->pol_add_label);
            this->Controls->Add(this->label1);
            this->Controls->Add(this->fio_add_label);
            this->Controls->Add(this->DepDateBox);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->MaximizeBox = false;
            this->MinimizeBox = false;
            this->Name = L"SearchForm";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
            this->Text = L"Поиск поездок";
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion

    public:
        System::Void SearchButton_Click(System::Object^ sender, System::EventArgs^ e);

    private:
        System::Void back_add_Click(System::Object^ sender, System::EventArgs^ e);

        // Обработчики чекбоксов
        System::Void checkStartBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
        System::Void checkFinishBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
        System::Void checkDateStartBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
        System::Void checkDateFinishBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
        System::Void checkPriceBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
        System::Void checkDriverBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
        System::Void checkBusBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
    };
}