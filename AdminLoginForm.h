// AdminLoginForm.h
#pragma once
#include "Admin.hpp"

namespace InfSystBusStation {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class AdminLoginForm : public System::Windows::Forms::Form {
    public:
        // Конструктор принимает существующий Admin
        AdminLoginForm(Admin^ admin)
        {
            InitializeComponent();
            this->admin = admin;  // Сохраняем ссылку

            // Предустановленные значения для теста
            this->PassFioBox->Text = admin->GetFullName();
            this->PolPassBox->SetItemChecked(0, true); // Мужской
            this->PassportPassBox->Text = L"4500/123456";
            this->EMAILBox->Text = admin->GetEmail();
            this->PhonePassBox->Text = L"+79001234567";
            this->textBoxPassword->Text = L"admin123";  // Пароль по умолчанию
        }

  
        property bool IsAuthenticated {
            bool get() { return isAuthenticated; }
        }

    protected:
        ~AdminLoginForm() {
            if (components) delete components;
        }

    private:
        System::ComponentModel::Container^ components;
        Admin^ admin;  
        bool isAuthenticated = false;

        // Элементы формы
    public:
        System::Windows::Forms::MaskedTextBox^ PassFioBox;
        System::Windows::Forms::CheckedListBox^ PolPassBox;
        System::Windows::Forms::MaskedTextBox^ PassportPassBox;
        System::Windows::Forms::TextBox^ EMAILBox;
        System::Windows::Forms::MaskedTextBox^ PhonePassBox;
        System::Windows::Forms::TextBox^ textBoxPassword;   // Поле для пароля

        System::Windows::Forms::Label^ label1;
        System::Windows::Forms::Label^ label2;
        System::Windows::Forms::Label^ label3;
        System::Windows::Forms::Label^ label4;
        System::Windows::Forms::Label^ label5;
        System::Windows::Forms::Label^ label7;  // Для пароля

        System::Windows::Forms::Button^ SaveButton;
        System::Windows::Forms::Button^ BackButton;
        System::Windows::Forms::Button^ buttonChangePassword;

    private:

        void InitializeComponent(void) {
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

            // Новые элементы (только пароль)
            this->textBoxPassword = (gcnew System::Windows::Forms::TextBox());
            this->label7 = (gcnew System::Windows::Forms::Label());
            this->buttonChangePassword = (gcnew System::Windows::Forms::Button());

            this->SuspendLayout();

            // ========== ОСНОВНЫЕ ЭЛЕМЕНТЫ ==========
            // PassFioBox
            this->PassFioBox->Location = System::Drawing::Point(64, 107);
            this->PassFioBox->Mask = L"L/L/LLLLLLLLLLLLLLLLL";
            this->PassFioBox->Name = L"PassFioBox";
            this->PassFioBox->Size = System::Drawing::Size(123, 22);
            this->PassFioBox->TabIndex = 0;

            // PolPassBox
            this->PolPassBox->CheckOnClick = true;
            this->PolPassBox->FormattingEnabled = true;
            this->PolPassBox->Items->AddRange(gcnew cli::array< System::Object^  >(2) {
                L"Мужской", L"Женский"
            });
            this->PolPassBox->Location = System::Drawing::Point(64, 187);
            this->PolPassBox->Name = L"PolPassBox";
            this->PolPassBox->Size = System::Drawing::Size(108, 55);
            this->PolPassBox->TabIndex = 2;

            // PassportPassBox
            this->PassportPassBox->Location = System::Drawing::Point(64, 316);
            this->PassportPassBox->Mask = L"0000/000000";
            this->PassportPassBox->Name = L"PassportPassBox";
            this->PassportPassBox->Size = System::Drawing::Size(82, 22);
            this->PassportPassBox->TabIndex = 3;
            this->PassportPassBox->ValidatingType = System::DateTime::typeid;

            // EMAILBox
            this->EMAILBox->Location = System::Drawing::Point(341, 107);
            this->EMAILBox->Name = L"EMAILBox";
            this->EMAILBox->Size = System::Drawing::Size(111, 22);
            this->EMAILBox->TabIndex = 4;

            // label1
            this->label1->AutoSize = true;
            this->label1->Location = System::Drawing::Point(61, 158);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(33, 16);
            this->label1->TabIndex = 6;
            this->label1->Text = L"Пол";

            // label2
            this->label2->AutoSize = true;
            this->label2->Location = System::Drawing::Point(61, 70);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(38, 16);
            this->label2->TabIndex = 7;
            this->label2->Text = L"ФИО";

            // label3
            this->label3->AutoSize = true;
            this->label3->Location = System::Drawing::Point(61, 273);
            this->label3->Name = L"label3";
            this->label3->Size = System::Drawing::Size(167, 16);
            this->label3->TabIndex = 8;
            this->label3->Text = L"Серия и номер паспорта";

            // label4
            this->label4->AutoSize = true;
            this->label4->Location = System::Drawing::Point(349, 70);
            this->label4->Name = L"label4";
            this->label4->Size = System::Drawing::Size(46, 16);
            this->label4->TabIndex = 9;
            this->label4->Text = L"EMAIL";

            // label5
            this->label5->AutoSize = true;
            this->label5->Location = System::Drawing::Point(338, 171);
            this->label5->Name = L"label5";
            this->label5->Size = System::Drawing::Size(121, 16);
            this->label5->TabIndex = 10;
            this->label5->Text = L"Номер Телефона";

            // PhonePassBox
            this->PhonePassBox->Location = System::Drawing::Point(341, 220);
            this->PhonePassBox->Mask = L"+00000000000";
            this->PhonePassBox->Name = L"PhonePassBox";
            this->PhonePassBox->Size = System::Drawing::Size(103, 22);
            this->PhonePassBox->TabIndex = 11;
            this->PhonePassBox->ValidatingType = System::DateTime::typeid;

            // SaveButton
            this->SaveButton->BackColor = System::Drawing::Color::LightGreen;
            this->SaveButton->Location = System::Drawing::Point(434, 372);
            this->SaveButton->Name = L"SaveButton";
            this->SaveButton->Size = System::Drawing::Size(102, 30);
            this->SaveButton->TabIndex = 12;
            this->SaveButton->Text = L"Войти";
            this->SaveButton->UseVisualStyleBackColor = false;
            this->SaveButton->Click += gcnew System::EventHandler(this,
                &AdminLoginForm::LoginButton_Click);

            // BackButton
            this->BackButton->BackColor = System::Drawing::Color::LightCoral;
            this->BackButton->Location = System::Drawing::Point(44, 372);
            this->BackButton->Name = L"BackButton";
            this->BackButton->Size = System::Drawing::Size(102, 30);
            this->BackButton->TabIndex = 13;
            this->BackButton->Text = L"Назад";
            this->BackButton->UseVisualStyleBackColor = false;
            this->BackButton->Click += gcnew System::EventHandler(this,
                &AdminLoginForm::BackButton_Click);

            // ========== ЭЛЕМЕНТЫ ПАРОЛЯ ==========
            // textBoxPassword
            this->textBoxPassword->Location = System::Drawing::Point(341, 316);
            this->textBoxPassword->Name = L"textBoxPassword";
            this->textBoxPassword->Size = System::Drawing::Size(111, 22);
            this->textBoxPassword->TabIndex = 16;
            this->textBoxPassword->UseSystemPasswordChar = true;

            // label7
            this->label7->AutoSize = true;
            this->label7->Location = System::Drawing::Point(338, 273);
            this->label7->Name = L"label7";
            this->label7->Size = System::Drawing::Size(61, 16);
            this->label7->TabIndex = 17;
            this->label7->Text = L"Пароль";

            // buttonChangePassword
            this->buttonChangePassword->BackColor = System::Drawing::Color::LightBlue;
            this->buttonChangePassword->Location = System::Drawing::Point(250, 372);
            this->buttonChangePassword->Name = L"buttonChangePassword";
            this->buttonChangePassword->Size = System::Drawing::Size(130, 30);
            this->buttonChangePassword->TabIndex = 18;
            this->buttonChangePassword->Text = L"Сменить пароль";
            this->buttonChangePassword->UseVisualStyleBackColor = false;
            this->buttonChangePassword->Click += gcnew System::EventHandler(this,
                &AdminLoginForm::ChangePasswordButton_Click);

            // AdminLoginForm
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->BackColor = System::Drawing::Color::LightGray;
            this->ClientSize = System::Drawing::Size(585, 450);
            this->Controls->Add(this->buttonChangePassword);
            this->Controls->Add(this->label7);
            this->Controls->Add(this->textBoxPassword);
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
            this->Name = L"AdminLoginForm";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->Text = L"Вход администратора";
            this->ResumeLayout(false);
            this->PerformLayout();
        }

    private:
        // Обработчики событий
        System::Void LoginButton_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void BackButton_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void ChangePasswordButton_Click(System::Object^ sender, System::EventArgs^ e);
    };
}