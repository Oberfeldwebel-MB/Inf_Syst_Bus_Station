#pragma once

#include "User.hpp"
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

    public ref class PassengerForm : public System::Windows::Forms::Form {
    public:
        // Конструктор с 3 списками
        PassengerForm(TripList^ tripList, BusList^ busList, DriversList^ driverList) {
            InitializeComponent();
            this->tripList = tripList;
            this->busList = busList;
            this->driverList = driverList;
            createdUser = nullptr;
        }

        property User^ CreatedUser {
            User^ get() { return createdUser; }
        }

    protected:
        ~PassengerForm() {
            if (components) delete components;
        }



        System::ComponentModel::Container^ components;
    private: System::Windows::Forms::MaskedTextBox^ PassFioBox;
    public: System::Windows::Forms::CheckedListBox^ PolPassBox;
    public: System::Windows::Forms::MaskedTextBox^ PassportPassBox;
    public: System::Windows::Forms::TextBox^ EMAILBox;


    private: System::Windows::Forms::Label^ label1;
    private: System::Windows::Forms::Label^ label2;
    private: System::Windows::Forms::Label^ label3;
    private: System::Windows::Forms::Label^ label4;
    private: System::Windows::Forms::Label^ label5;
    public: System::Windows::Forms::MaskedTextBox^ PhonePassBox;
    private: System::Windows::Forms::Button^ SaveButton;
    private: System::Windows::Forms::Button^ BackButton;
    public:

    private:

    private:
    public:

    public:
    private:

        User^ createdUser;  // Изменено на User^
        TripList^ tripList;    // Добавить
        BusList^ busList;      // Добавить
        DriversList^ driverList; // Добавить

        void InitializeComponent(void) {
            // Ваш оригинальный код InitializeComponent БЕЗ ИЗМЕНЕНИЙ
            this->PassFioBox = (gcnew System::Windows::Forms::MaskedTextBox());
            this->PolPassBox = (gcnew System::Windows::Forms::CheckedListBox());
            this->PassportPassBox = (gcnew System::Windows::Forms::MaskedTextBox());
            this->EMAILBox = (gcnew System::Windows::Forms::TextBox());
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->label2 = (gcnew System::Windows::Forms::Label());
            this->label3 = (gcnew System::Windows::Forms::Label());
            this->label4 = (gcnew System::Windows::Forms::Label());
            this->label5 = (gcnew System::Windows::Forms::Label());
            this->PhonePassBox = (gcnew System::Windows::Forms::MaskedTextBox());
            this->SaveButton = (gcnew System::Windows::Forms::Button());
            this->BackButton = (gcnew System::Windows::Forms::Button());
            this->SuspendLayout();
            // 
            // PassFioBox
            // 
            this->PassFioBox->Location = System::Drawing::Point(64, 107);
            this->PassFioBox->Mask = L"L/L/LLLLLLLLLLLLLLLLL";
            this->PassFioBox->Name = L"PassFioBox";
            this->PassFioBox->Size = System::Drawing::Size(123, 22);
            this->PassFioBox->TabIndex = 0;
            // 
            // PolPassBox
            // 
            this->PolPassBox->CheckOnClick = true;
            this->PolPassBox->FormattingEnabled = true;
            this->PolPassBox->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Мужской", L"Женский" });
            this->PolPassBox->Location = System::Drawing::Point(64, 187);
            this->PolPassBox->Name = L"PolPassBox";
            this->PolPassBox->Size = System::Drawing::Size(108, 55);
            this->PolPassBox->TabIndex = 2;
            // 
            // PassportPassBox
            // 
            this->PassportPassBox->Location = System::Drawing::Point(64, 316);
            this->PassportPassBox->Mask = L"0000/000000";
            this->PassportPassBox->Name = L"PassportPassBox";
            this->PassportPassBox->Size = System::Drawing::Size(82, 22);
            this->PassportPassBox->TabIndex = 3;
            this->PassportPassBox->ValidatingType = System::DateTime::typeid;
            // 
            // EMAILBox
            // 
            this->EMAILBox->Location = System::Drawing::Point(341, 107);
            this->EMAILBox->Name = L"EMAILBox";
            this->EMAILBox->Size = System::Drawing::Size(111, 22);
            this->EMAILBox->TabIndex = 4;
            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->Location = System::Drawing::Point(61, 158);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(33, 16);
            this->label1->TabIndex = 6;
            this->label1->Text = L"Пол";
            // 
            // label2
            // 
            this->label2->AutoSize = true;
            this->label2->Location = System::Drawing::Point(61, 70);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(38, 16);
            this->label2->TabIndex = 7;
            this->label2->Text = L"ФИО";
            // 
            // label3
            // 
            this->label3->AutoSize = true;
            this->label3->Location = System::Drawing::Point(61, 273);
            this->label3->Name = L"label3";
            this->label3->Size = System::Drawing::Size(167, 16);
            this->label3->TabIndex = 8;
            this->label3->Text = L"Серия и номер паспорта";
            // 
            // label4
            // 
            this->label4->AutoSize = true;
            this->label4->Location = System::Drawing::Point(349, 70);
            this->label4->Name = L"label4";
            this->label4->Size = System::Drawing::Size(46, 16);
            this->label4->TabIndex = 9;
            this->label4->Text = L"EMAIL";
            // 
            // label5
            // 
            this->label5->AutoSize = true;
            this->label5->Location = System::Drawing::Point(338, 171);
            this->label5->Name = L"label5";
            this->label5->Size = System::Drawing::Size(121, 16);
            this->label5->TabIndex = 10;
            this->label5->Text = L"Номер Телефона";
            // 
            // PhonePassBox
            // 
            this->PhonePassBox->Location = System::Drawing::Point(341, 220);
            this->PhonePassBox->Mask = L"+00000000000";
            this->PhonePassBox->Name = L"PhonePassBox";
            this->PhonePassBox->Size = System::Drawing::Size(103, 22);
            this->PhonePassBox->TabIndex = 11;
            this->PhonePassBox->ValidatingType = System::DateTime::typeid;
            // 
            // SaveButton
            // 
            this->SaveButton->Location = System::Drawing::Point(434, 372);
            this->SaveButton->Name = L"SaveButton";
            this->SaveButton->Size = System::Drawing::Size(102, 23);
            this->SaveButton->TabIndex = 12;
            this->SaveButton->Text = L"Сохранить";
            this->SaveButton->UseVisualStyleBackColor = true;
            this->SaveButton->Click += gcnew System::EventHandler(this, &PassengerForm::SaveButton_Click);
            // 
            // BackButton
            // 
            this->BackButton->Location = System::Drawing::Point(44, 372);
            this->BackButton->Name = L"BackButton";
            this->BackButton->Size = System::Drawing::Size(102, 23);
            this->BackButton->TabIndex = 13;
            this->BackButton->Text = L"Назад";
            this->BackButton->UseVisualStyleBackColor = true;
            this->BackButton->Click += gcnew System::EventHandler(this, &PassengerForm::BackButton_Click);
            // 
            // PassengerForm
            // 
            this->ClientSize = System::Drawing::Size(585, 435);
            this->Controls->Add(this->BackButton);
            this->Controls->Add(this->SaveButton);
            this->Controls->Add(this->PhonePassBox);
            this->Controls->Add(this->label5);
            this->Controls->Add(this->label4);
            this->Controls->Add(this->label3);
            this->Controls->Add(this->label2);
            this->Controls->Add(this->label1);
            this->Controls->Add(this->EMAILBox);
            this->Controls->Add(this->PassportPassBox);
            this->Controls->Add(this->PolPassBox);
            this->Controls->Add(this->PassFioBox);
            this->Name = L"PassengerForm";
            this->Text = L"Данные пассажира";
            this->ResumeLayout(false);
            this->PerformLayout();

        }


    private: System::Void SaveButton_Click(System::Object^ sender, System::EventArgs^ e);
    private: System::Void BackButton_Click(System::Object^ sender, System::EventArgs^ e);
    };
}