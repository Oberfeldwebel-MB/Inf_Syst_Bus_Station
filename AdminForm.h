// AdminForm.h
#pragma once

#include "Admin.hpp"
#include "TimingForm.h"
#include "DriversListForm.h"
#include "BusListForm.h"
#include "StartForm.h"

namespace InfSystBusStation {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    /// <summary>
    /// Главная форма администратора
    /// </summary>
    public ref class AdminForm : public System::Windows::Forms::Form
    {
    public:
        AdminForm(Admin^ admin)
        {
            InitializeComponent();
            this->admin = admin;
            this->Text = L"Панель администратора - " + admin->GetFullName();
            admin->InitializeSystem();
        }

    protected:
        ~AdminForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        Admin^ admin;  // <-- Храним ссылку на Admin
        System::Windows::Forms::Label^ labelTitle;
        System::Windows::Forms::Button^ buttonSchedule;
        System::Windows::Forms::Button^ buttonDrivers;
        System::Windows::Forms::Button^ buttonBuses;
        System::Windows::Forms::Button^ buttonLogout;
        System::Windows::Forms::Button^ buttonBack;

    private:
        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->labelTitle = (gcnew System::Windows::Forms::Label());
            this->buttonSchedule = (gcnew System::Windows::Forms::Button());
            this->buttonDrivers = (gcnew System::Windows::Forms::Button());
            this->buttonBuses = (gcnew System::Windows::Forms::Button());
            this->buttonLogout = (gcnew System::Windows::Forms::Button());
            this->buttonBack = (gcnew System::Windows::Forms::Button());
            this->SuspendLayout();
            // 
            // labelTitle
            // 
            this->labelTitle->AutoSize = true;
            this->labelTitle->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16, System::Drawing::FontStyle::Bold));
            this->labelTitle->Location = System::Drawing::Point(214, 21);
            this->labelTitle->Name = L"labelTitle";
            this->labelTitle->Size = System::Drawing::Size(344, 31);
            this->labelTitle->TabIndex = 0;
            this->labelTitle->Text = L"Панель администратора";
            this->labelTitle->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
            // 
            // buttonSchedule
            // 
            this->buttonSchedule->BackColor = System::Drawing::Color::LightSkyBlue;
            this->buttonSchedule->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->buttonSchedule->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
            this->buttonSchedule->Location = System::Drawing::Point(214, 74);
            this->buttonSchedule->Name = L"buttonSchedule";
            this->buttonSchedule->Size = System::Drawing::Size(344, 50);
            this->buttonSchedule->TabIndex = 1;
            this->buttonSchedule->Text = L"📅 Управление расписанием";
            this->buttonSchedule->UseVisualStyleBackColor = false;
            this->buttonSchedule->Click += gcnew System::EventHandler(this, &AdminForm::buttonSchedule_Click);
            // 
            // buttonDrivers
            // 
            this->buttonDrivers->BackColor = System::Drawing::Color::LightGreen;
            this->buttonDrivers->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->buttonDrivers->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
            this->buttonDrivers->Location = System::Drawing::Point(214, 147);
            this->buttonDrivers->Name = L"buttonDrivers";
            this->buttonDrivers->Size = System::Drawing::Size(344, 50);
            this->buttonDrivers->TabIndex = 2;
            this->buttonDrivers->Text = L"👨‍✈️ Управление водителями";
            this->buttonDrivers->UseVisualStyleBackColor = false;
            this->buttonDrivers->Click += gcnew System::EventHandler(this, &AdminForm::buttonDrivers_Click);
            // 
            // buttonBuses
            // 
            this->buttonBuses->BackColor = System::Drawing::Color::LightGoldenrodYellow;
            this->buttonBuses->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->buttonBuses->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
            this->buttonBuses->Location = System::Drawing::Point(214, 203);
            this->buttonBuses->Name = L"buttonBuses";
            this->buttonBuses->Size = System::Drawing::Size(344, 50);
            this->buttonBuses->TabIndex = 3;
            this->buttonBuses->Text = L"🚌 Управление автобусами";
            this->buttonBuses->UseVisualStyleBackColor = false;
            this->buttonBuses->Click += gcnew System::EventHandler(this, &AdminForm::buttonBuses_Click);
            // 
            // buttonLogout
            // 
            this->buttonLogout->BackColor = System::Drawing::Color::LightCoral;
            this->buttonLogout->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->buttonLogout->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
            this->buttonLogout->Location = System::Drawing::Point(557, 389);
            this->buttonLogout->Name = L"buttonLogout";
            this->buttonLogout->Size = System::Drawing::Size(150, 54);
            this->buttonLogout->TabIndex = 4;
            this->buttonLogout->Text = L"Выйти из системы";
            this->buttonLogout->UseVisualStyleBackColor = false;
            this->buttonLogout->Click += gcnew System::EventHandler(this, &AdminForm::buttonLogout_Click);
            // 
            // buttonBack
            // 
            this->buttonBack->BackColor = System::Drawing::Color::LightGray;
            this->buttonBack->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->buttonBack->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
            this->buttonBack->Location = System::Drawing::Point(12, 399);
            this->buttonBack->Name = L"buttonBack";
            this->buttonBack->Size = System::Drawing::Size(150, 35);
            this->buttonBack->TabIndex = 5;
            this->buttonBack->Text = L"← На главную";
            this->buttonBack->UseVisualStyleBackColor = false;
            this->buttonBack->Click += gcnew System::EventHandler(this, &AdminForm::buttonBack_Click);
            // 
            // AdminForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->BackColor = System::Drawing::Color::White;
            this->ClientSize = System::Drawing::Size(719, 455);
            this->Controls->Add(this->buttonBack);
            this->Controls->Add(this->buttonLogout);
            this->Controls->Add(this->buttonBuses);
            this->Controls->Add(this->buttonDrivers);
            this->Controls->Add(this->buttonSchedule);
            this->Controls->Add(this->labelTitle);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->MaximizeBox = false;
            this->Name = L"AdminForm";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->Text = L"Панель администратора";
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion

    private:
        // Обработчики событий
        System::Void buttonSchedule_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void buttonDrivers_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void buttonBuses_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void buttonLogout_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void buttonBack_Click(System::Object^ sender, System::EventArgs^ e);
    };
}