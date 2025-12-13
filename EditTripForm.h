// EditTripForm.h
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

    public ref class EditTripForm : public System::Windows::Forms::Form {
    public:
        EditTripForm(TripList^ tripList, BusList^ busList, DriversList^ driverList) {
            InitializeComponent();
            this->tripList = tripList;
            this->busList = busList;
            this->driverList = driverList;
        }

    protected:
        ~EditTripForm() {
            if (components) {
                delete components;
            }
        }

    private:
        TripList^ tripList;
        BusList^ busList;
        DriversList^ driverList;
        Trip^ currentTrip;
        System::ComponentModel::Container^ components;

        // Поля для хранения новых данных
    public:
        String^ NewStartPoint;
        String^ NewFinishPoint;
        String^ NewDepDate;
        String^ NewArrDate;
        int NewPrice;
        Driver^ NewDriver;
        Bus^ NewBus;

        int tripIndex;

        // CheckBox для выбора полей к редактированию
    public:
        System::Windows::Forms::CheckBox^ startPointCheckBox;
        System::Windows::Forms::CheckBox^ finishPointCheckBox;
        System::Windows::Forms::CheckBox^ depDateCheckBox;
        System::Windows::Forms::CheckBox^ arrDateCheckBox;
        System::Windows::Forms::CheckBox^ priceCheckBox;
        System::Windows::Forms::CheckBox^ driverCheckBox;
        System::Windows::Forms::CheckBox^ busCheckBox;

        // Поля ввода
    public:
        System::Windows::Forms::TextBox^ startPointBox;
        System::Windows::Forms::TextBox^ finishPointBox;
        System::Windows::Forms::MaskedTextBox^ depDateBox;
        System::Windows::Forms::MaskedTextBox^ arrDateBox;
        System::Windows::Forms::TextBox^ priceBox;
        System::Windows::Forms::ComboBox^ driverComboBox;
        System::Windows::Forms::ComboBox^ busComboBox;

        // Методы
    private:
        void LoadTripInfo();
        void LoadDriverComboBox();
        void LoadBusComboBox();

#pragma region Windows Form Designer generated code
        void InitializeComponent(void) {
            this->startPointCheckBox = (gcnew System::Windows::Forms::CheckBox());
            this->finishPointCheckBox = (gcnew System::Windows::Forms::CheckBox());
            this->depDateCheckBox = (gcnew System::Windows::Forms::CheckBox());
            this->arrDateCheckBox = (gcnew System::Windows::Forms::CheckBox());
            this->priceCheckBox = (gcnew System::Windows::Forms::CheckBox());
            this->driverCheckBox = (gcnew System::Windows::Forms::CheckBox());
            this->busCheckBox = (gcnew System::Windows::Forms::CheckBox());
            this->startPointBox = (gcnew System::Windows::Forms::TextBox());
            this->finishPointBox = (gcnew System::Windows::Forms::TextBox());
            this->depDateBox = (gcnew System::Windows::Forms::MaskedTextBox());
            this->arrDateBox = (gcnew System::Windows::Forms::MaskedTextBox());
            this->priceBox = (gcnew System::Windows::Forms::TextBox());
            this->driverComboBox = (gcnew System::Windows::Forms::ComboBox());
            this->busComboBox = (gcnew System::Windows::Forms::ComboBox());
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->label2 = (gcnew System::Windows::Forms::Label());
            this->label3 = (gcnew System::Windows::Forms::Label());
            this->label4 = (gcnew System::Windows::Forms::Label());
            this->label5 = (gcnew System::Windows::Forms::Label());
            this->label6 = (gcnew System::Windows::Forms::Label());
            this->label7 = (gcnew System::Windows::Forms::Label());
            this->tripIndexBox = (gcnew System::Windows::Forms::TextBox());
            this->label8 = (gcnew System::Windows::Forms::Label());
            this->btnLoad = (gcnew System::Windows::Forms::Button());
            this->btnEdit = (gcnew System::Windows::Forms::Button());
            this->btnCancel = (gcnew System::Windows::Forms::Button());
            this->label9 = (gcnew System::Windows::Forms::Label());
            this->currentInfoLabel = (gcnew System::Windows::Forms::Label());
            this->SuspendLayout();
            // 
            // startPointCheckBox
            // 
            this->startPointCheckBox->AutoSize = true;
            this->startPointCheckBox->Location = System::Drawing::Point(402, 104);
            this->startPointCheckBox->Name = L"startPointCheckBox";
            this->startPointCheckBox->Size = System::Drawing::Size(18, 17);
            this->startPointCheckBox->TabIndex = 0;
            // 
            // finishPointCheckBox
            // 
            this->finishPointCheckBox->AutoSize = true;
            this->finishPointCheckBox->Location = System::Drawing::Point(402, 145);
            this->finishPointCheckBox->Name = L"finishPointCheckBox";
            this->finishPointCheckBox->Size = System::Drawing::Size(18, 17);
            this->finishPointCheckBox->TabIndex = 1;
            // 
            // depDateCheckBox
            // 
            this->depDateCheckBox->AutoSize = true;
            this->depDateCheckBox->Location = System::Drawing::Point(402, 185);
            this->depDateCheckBox->Name = L"depDateCheckBox";
            this->depDateCheckBox->Size = System::Drawing::Size(18, 17);
            this->depDateCheckBox->TabIndex = 2;
            // 
            // arrDateCheckBox
            // 
            this->arrDateCheckBox->AutoSize = true;
            this->arrDateCheckBox->Location = System::Drawing::Point(402, 225);
            this->arrDateCheckBox->Name = L"arrDateCheckBox";
            this->arrDateCheckBox->Size = System::Drawing::Size(18, 17);
            this->arrDateCheckBox->TabIndex = 3;
            // 
            // priceCheckBox
            // 
            this->priceCheckBox->AutoSize = true;
            this->priceCheckBox->Location = System::Drawing::Point(402, 265);
            this->priceCheckBox->Name = L"priceCheckBox";
            this->priceCheckBox->Size = System::Drawing::Size(18, 17);
            this->priceCheckBox->TabIndex = 4;
            // 
            // driverCheckBox
            // 
            this->driverCheckBox->AutoSize = true;
            this->driverCheckBox->Location = System::Drawing::Point(402, 307);
            this->driverCheckBox->Name = L"driverCheckBox";
            this->driverCheckBox->Size = System::Drawing::Size(18, 17);
            this->driverCheckBox->TabIndex = 5;
            // 
            // busCheckBox
            // 
            this->busCheckBox->AutoSize = true;
            this->busCheckBox->Location = System::Drawing::Point(402, 344);
            this->busCheckBox->Name = L"busCheckBox";
            this->busCheckBox->Size = System::Drawing::Size(18, 17);
            this->busCheckBox->TabIndex = 6;
            // 
            // startPointBox
            // 
            this->startPointBox->Enabled = false;
            this->startPointBox->Location = System::Drawing::Point(208, 103);
            this->startPointBox->Name = L"startPointBox";
            this->startPointBox->Size = System::Drawing::Size(180, 22);
            this->startPointBox->TabIndex = 7;
            // 
            // finishPointBox
            // 
            this->finishPointBox->Enabled = false;
            this->finishPointBox->Location = System::Drawing::Point(208, 140);
            this->finishPointBox->Name = L"finishPointBox";
            this->finishPointBox->Size = System::Drawing::Size(180, 22);
            this->finishPointBox->TabIndex = 8;
            // 
            // depDateBox
            // 
            this->depDateBox->Enabled = false;
            this->depDateBox->Location = System::Drawing::Point(208, 180);
            this->depDateBox->Mask = L"00/00/0000 90:00";
            this->depDateBox->Name = L"depDateBox";
            this->depDateBox->Size = System::Drawing::Size(180, 22);
            this->depDateBox->TabIndex = 9;
            this->depDateBox->ValidatingType = System::DateTime::typeid;
            // 
            // arrDateBox
            // 
            this->arrDateBox->Enabled = false;
            this->arrDateBox->Location = System::Drawing::Point(208, 221);
            this->arrDateBox->Mask = L"00/00/0000 90:00";
            this->arrDateBox->Name = L"arrDateBox";
            this->arrDateBox->Size = System::Drawing::Size(180, 22);
            this->arrDateBox->TabIndex = 10;
            this->arrDateBox->ValidatingType = System::DateTime::typeid;
            // 
            // priceBox
            // 
            this->priceBox->Enabled = false;
            this->priceBox->Location = System::Drawing::Point(208, 260);
            this->priceBox->Name = L"priceBox";
            this->priceBox->Size = System::Drawing::Size(180, 22);
            this->priceBox->TabIndex = 11;
            // 
            // driverComboBox
            // 
            this->driverComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->driverComboBox->Enabled = false;
            this->driverComboBox->FormattingEnabled = true;
            this->driverComboBox->Location = System::Drawing::Point(208, 303);
            this->driverComboBox->Name = L"driverComboBox";
            this->driverComboBox->Size = System::Drawing::Size(180, 24);
            this->driverComboBox->TabIndex = 12;
            // 
            // busComboBox
            // 
            this->busComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->busComboBox->Enabled = false;
            this->busComboBox->FormattingEnabled = true;
            this->busComboBox->Location = System::Drawing::Point(208, 340);
            this->busComboBox->Name = L"busComboBox";
            this->busComboBox->Size = System::Drawing::Size(180, 24);
            this->busComboBox->TabIndex = 13;
            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->Location = System::Drawing::Point(20, 103);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(136, 16);
            this->label1->TabIndex = 14;
            this->label1->Text = L"Пункт отправления";
            // 
            // label2
            // 
            this->label2->AutoSize = true;
            this->label2->Location = System::Drawing::Point(20, 143);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(113, 16);
            this->label2->TabIndex = 15;
            this->label2->Text = L"Пункт прибытия";
            // 
            // label3
            // 
            this->label3->AutoSize = true;
            this->label3->Location = System::Drawing::Point(20, 183);
            this->label3->Name = L"label3";
            this->label3->Size = System::Drawing::Size(182, 16);
            this->label3->TabIndex = 16;
            this->label3->Text = L"Дата и время отправления";
            // 
            // label4
            // 
            this->label4->AutoSize = true;
            this->label4->Location = System::Drawing::Point(20, 223);
            this->label4->Name = L"label4";
            this->label4->Size = System::Drawing::Size(159, 16);
            this->label4->TabIndex = 17;
            this->label4->Text = L"Дата и время прибытия";
            // 
            // label5
            // 
            this->label5->AutoSize = true;
            this->label5->Location = System::Drawing::Point(20, 263);
            this->label5->Name = L"label5";
            this->label5->Size = System::Drawing::Size(40, 16);
            this->label5->TabIndex = 18;
            this->label5->Text = L"Цена";
            // 
            // label6
            // 
            this->label6->AutoSize = true;
            this->label6->Location = System::Drawing::Point(20, 303);
            this->label6->Name = L"label6";
            this->label6->Size = System::Drawing::Size(70, 16);
            this->label6->TabIndex = 19;
            this->label6->Text = L"Водитель";
            // 
            // label7
            // 
            this->label7->AutoSize = true;
            this->label7->Location = System::Drawing::Point(20, 343);
            this->label7->Name = L"label7";
            this->label7->Size = System::Drawing::Size(62, 16);
            this->label7->TabIndex = 20;
            this->label7->Text = L"Автобус";
            // 
            // tripIndexBox
            // 
            this->tripIndexBox->Location = System::Drawing::Point(288, 60);
            this->tripIndexBox->Name = L"tripIndexBox";
            this->tripIndexBox->Size = System::Drawing::Size(100, 22);
            this->tripIndexBox->TabIndex = 21;
            // 
            // label8
            // 
            this->label8->AutoSize = true;
            this->label8->Location = System::Drawing::Point(20, 63);
            this->label8->Name = L"label8";
            this->label8->Size = System::Drawing::Size(136, 16);
            this->label8->TabIndex = 22;
            this->label8->Text = L"Номер поездки (№):";
            // 
            // btnLoad
            // 
            this->btnLoad->BackColor = System::Drawing::SystemColors::InactiveCaption;
            this->btnLoad->Location = System::Drawing::Point(415, 58);
            this->btnLoad->Name = L"btnLoad";
            this->btnLoad->Size = System::Drawing::Size(90, 26);
            this->btnLoad->TabIndex = 23;
            this->btnLoad->Text = L"Загрузить";
            this->btnLoad->UseVisualStyleBackColor = false;
            this->btnLoad->Click += gcnew System::EventHandler(this, &EditTripForm::btnLoad_Click);
            // 
            // btnEdit
            // 
            this->btnEdit->BackColor = System::Drawing::Color::LightGreen;
            this->btnEdit->Location = System::Drawing::Point(150, 400);
            this->btnEdit->Name = L"btnEdit";
            this->btnEdit->Size = System::Drawing::Size(120, 40);
            this->btnEdit->TabIndex = 24;
            this->btnEdit->Text = L"Применить изменения";
            this->btnEdit->UseVisualStyleBackColor = false;
            this->btnEdit->Click += gcnew System::EventHandler(this, &EditTripForm::btnEdit_Click);
            // 
            // btnCancel
            // 
            this->btnCancel->BackColor = System::Drawing::SystemColors::InactiveCaption;
            this->btnCancel->Location = System::Drawing::Point(300, 400);
            this->btnCancel->Name = L"btnCancel";
            this->btnCancel->Size = System::Drawing::Size(120, 40);
            this->btnCancel->TabIndex = 25;
            this->btnCancel->Text = L"Отмена";
            this->btnCancel->UseVisualStyleBackColor = false;
            this->btnCancel->Click += gcnew System::EventHandler(this, &EditTripForm::btnCancel_Click);
            // 
            // label9
            // 
            this->label9->AutoSize = true;
            this->label9->Location = System::Drawing::Point(482, 99);
            this->label9->Name = L"label9";
            this->label9->Size = System::Drawing::Size(205, 16);
            this->label9->TabIndex = 26;
            this->label9->Text = L"Отметьте поля для изменения";
            // 
            // currentInfoLabel
            // 
            this->currentInfoLabel->AutoSize = true;
            this->currentInfoLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold));
            this->currentInfoLabel->Location = System::Drawing::Point(20, 20);
            this->currentInfoLabel->Name = L"currentInfoLabel";
            this->currentInfoLabel->Size = System::Drawing::Size(289, 20);
            this->currentInfoLabel->TabIndex = 27;
            this->currentInfoLabel->Text = L"Текущая поездка: не выбрана";
            // 
            // EditTripForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->BackColor = System::Drawing::Color::Silver;
            this->ClientSize = System::Drawing::Size(782, 460);
            this->Controls->Add(this->currentInfoLabel);
            this->Controls->Add(this->label9);
            this->Controls->Add(this->btnCancel);
            this->Controls->Add(this->btnEdit);
            this->Controls->Add(this->btnLoad);
            this->Controls->Add(this->label8);
            this->Controls->Add(this->tripIndexBox);
            this->Controls->Add(this->label7);
            this->Controls->Add(this->label6);
            this->Controls->Add(this->label5);
            this->Controls->Add(this->label4);
            this->Controls->Add(this->label3);
            this->Controls->Add(this->label2);
            this->Controls->Add(this->label1);
            this->Controls->Add(this->busComboBox);
            this->Controls->Add(this->driverComboBox);
            this->Controls->Add(this->priceBox);
            this->Controls->Add(this->arrDateBox);
            this->Controls->Add(this->depDateBox);
            this->Controls->Add(this->finishPointBox);
            this->Controls->Add(this->startPointBox);
            this->Controls->Add(this->busCheckBox);
            this->Controls->Add(this->driverCheckBox);
            this->Controls->Add(this->priceCheckBox);
            this->Controls->Add(this->arrDateCheckBox);
            this->Controls->Add(this->depDateCheckBox);
            this->Controls->Add(this->finishPointCheckBox);
            this->Controls->Add(this->startPointCheckBox);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->MaximizeBox = false;
            this->MinimizeBox = false;
            this->Name = L"EditTripForm";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
            this->Text = L"Редактирование поездки";
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion

    private:
        System::Windows::Forms::TextBox^ tripIndexBox;
        System::Windows::Forms::Label^ label1;
        System::Windows::Forms::Label^ label2;
        System::Windows::Forms::Label^ label3;
        System::Windows::Forms::Label^ label4;
        System::Windows::Forms::Label^ label5;
        System::Windows::Forms::Label^ label6;
        System::Windows::Forms::Label^ label7;
        System::Windows::Forms::Label^ label8;
        System::Windows::Forms::Button^ btnLoad;
        System::Windows::Forms::Button^ btnEdit;
        System::Windows::Forms::Button^ btnCancel;
        System::Windows::Forms::Label^ label9;
        System::Windows::Forms::Label^ currentInfoLabel;

        // Обработчики событий
    private:
        System::Void btnLoad_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void btnEdit_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void btnCancel_Click(System::Object^ sender, System::EventArgs^ e);

        // Обработчики CheckBox для активации полей
    private:
        System::Void startPointCheckBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
        System::Void finishPointCheckBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
        System::Void depDateCheckBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
        System::Void arrDateCheckBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
        System::Void priceCheckBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
        System::Void driverCheckBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
        System::Void busCheckBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
    };
}