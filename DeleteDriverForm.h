#pragma once

#include "DriversList.hpp"

namespace InfSystBusStation {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    /// <summary>
    /// Форма для удаления водителя
    /// </summary>
    public ref class DeleteDriverForm : public System::Windows::Forms::Form
    {
    public:
        DeleteDriverForm(DriversList^ driversList) {
            InitializeComponent();
            this->driversList = driversList;
            LoadDriverNames();
        }

    protected:
        ~DeleteDriverForm() {
            if (components) {
                delete components;
            }
        }

    private:
        DriversList^ driversList;
        System::ComponentModel::Container^ components;

        // Элементы формы
    private:
        System::Windows::Forms::Label^ label1;
        System::Windows::Forms::ComboBox^ driverComboBox;
        System::Windows::Forms::Button^ deleteButton;
        System::Windows::Forms::Button^ cancelButton;
        System::Windows::Forms::Label^ infoLabel;
        System::Windows::Forms::GroupBox^ driverInfoGroup;
        System::Windows::Forms::Label^ licenseLabel;
        System::Windows::Forms::Label^ passportLabel;
        System::Windows::Forms::Label^ salaryLabel;
        System::Windows::Forms::Label^ statusLabel;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->driverComboBox = (gcnew System::Windows::Forms::ComboBox());
            this->deleteButton = (gcnew System::Windows::Forms::Button());
            this->cancelButton = (gcnew System::Windows::Forms::Button());
            this->infoLabel = (gcnew System::Windows::Forms::Label());
            this->driverInfoGroup = (gcnew System::Windows::Forms::GroupBox());
            this->statusLabel = (gcnew System::Windows::Forms::Label());
            this->salaryLabel = (gcnew System::Windows::Forms::Label());
            this->passportLabel = (gcnew System::Windows::Forms::Label());
            this->licenseLabel = (gcnew System::Windows::Forms::Label());
            this->driverInfoGroup->SuspendLayout();
            this->SuspendLayout();
            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label1->Location = System::Drawing::Point(12, 20);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(240, 20);
            this->label1->TabIndex = 0;
            this->label1->Text = L"Выберите водителя для удаления:";
            // 
            // driverComboBox
            // 
            this->driverComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->driverComboBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->driverComboBox->FormattingEnabled = true;
            this->driverComboBox->Location = System::Drawing::Point(16, 50);
            this->driverComboBox->Name = L"driverComboBox";
            this->driverComboBox->Size = System::Drawing::Size(400, 28);
            this->driverComboBox->TabIndex = 1;
            this->driverComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &DeleteDriverForm::driverComboBox_SelectedIndexChanged);
            // 
            // deleteButton
            // 
            this->deleteButton->BackColor = System::Drawing::Color::LightCoral;
            this->deleteButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->deleteButton->Location = System::Drawing::Point(250, 300);
            this->deleteButton->Name = L"deleteButton";
            this->deleteButton->Size = System::Drawing::Size(166, 40);
            this->deleteButton->TabIndex = 2;
            this->deleteButton->Text = L"Удалить";
            this->deleteButton->UseVisualStyleBackColor = false;
            this->deleteButton->Click += gcnew System::EventHandler(this, &DeleteDriverForm::deleteButton_Click);
            // 
            // cancelButton
            // 
            this->cancelButton->BackColor = System::Drawing::SystemColors::InactiveCaption;
            this->cancelButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->cancelButton->Location = System::Drawing::Point(16, 300);
            this->cancelButton->Name = L"cancelButton";
            this->cancelButton->Size = System::Drawing::Size(166, 40);
            this->cancelButton->TabIndex = 3;
            this->cancelButton->Text = L"Отмена";
            this->cancelButton->UseVisualStyleBackColor = false;
            this->cancelButton->Click += gcnew System::EventHandler(this, &DeleteDriverForm::cancelButton_Click);
            // 
            // infoLabel
            // 
            this->infoLabel->AutoSize = true;
            this->infoLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->infoLabel->ForeColor = System::Drawing::Color::DarkRed;
            this->infoLabel->Location = System::Drawing::Point(16, 85);
            this->infoLabel->Name = L"infoLabel";
            this->infoLabel->Size = System::Drawing::Size(331, 18);
            this->infoLabel->TabIndex = 4;
            this->infoLabel->Text = L"Выберите водителя для просмотра информации";
            // 
            // driverInfoGroup
            // 
            this->driverInfoGroup->Controls->Add(this->statusLabel);
            this->driverInfoGroup->Controls->Add(this->salaryLabel);
            this->driverInfoGroup->Controls->Add(this->passportLabel);
            this->driverInfoGroup->Controls->Add(this->licenseLabel);
            this->driverInfoGroup->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->driverInfoGroup->Location = System::Drawing::Point(16, 115);
            this->driverInfoGroup->Name = L"driverInfoGroup";
            this->driverInfoGroup->Size = System::Drawing::Size(400, 170);
            this->driverInfoGroup->TabIndex = 5;
            this->driverInfoGroup->TabStop = false;
            this->driverInfoGroup->Text = L"Информация о водителе";
            // 
            // statusLabel
            // 
            this->statusLabel->AutoSize = true;
            this->statusLabel->Location = System::Drawing::Point(10, 140);
            this->statusLabel->Name = L"statusLabel";
            this->statusLabel->Size = System::Drawing::Size(55, 18);
            this->statusLabel->TabIndex = 9;
            this->statusLabel->Text = L"Статус:";
            // 
            // salaryLabel
            // 
            this->salaryLabel->AutoSize = true;
            this->salaryLabel->Location = System::Drawing::Point(10, 110);
            this->salaryLabel->Name = L"salaryLabel";
            this->salaryLabel->Size = System::Drawing::Size(68, 18);
            this->salaryLabel->TabIndex = 8;
            this->salaryLabel->Text = L"Зарплата:";
            // 
            // passportLabel
            // 
            this->passportLabel->AutoSize = true;
            this->passportLabel->Location = System::Drawing::Point(10, 80);
            this->passportLabel->Name = L"passportLabel";
            this->passportLabel->Size = System::Drawing::Size(66, 18);
            this->passportLabel->TabIndex = 7;
            this->passportLabel->Text = L"Паспорт:";
            // 
            // licenseLabel
            // 
            this->licenseLabel->AutoSize = true;
            this->licenseLabel->Location = System::Drawing::Point(10, 50);
            this->licenseLabel->Name = L"licenseLabel";
            this->licenseLabel->Size = System::Drawing::Size(122, 18);
            this->licenseLabel->TabIndex = 6;
            this->licenseLabel->Text = L"Водительские права:";
            // 
            // DeleteDriverForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->BackColor = System::Drawing::SystemColors::InactiveCaption;
            this->ClientSize = System::Drawing::Size(432, 353);
            this->Controls->Add(this->driverInfoGroup);
            this->Controls->Add(this->infoLabel);
            this->Controls->Add(this->cancelButton);
            this->Controls->Add(this->deleteButton);
            this->Controls->Add(this->driverComboBox);
            this->Controls->Add(this->label1);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->MaximizeBox = false;
            this->MinimizeBox = false;
            this->Name = L"DeleteDriverForm";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
            this->Text = L"Удаление водителя";
            this->driverInfoGroup->ResumeLayout(false);
            this->driverInfoGroup->PerformLayout();
            this->ResumeLayout(false);
            this->PerformLayout();
        }
#pragma endregion

    private:
        // Метод для загрузки имен водителей в ComboBox
        void LoadDriverNames();

        // Метод для обновления информации о выбранном водителе
        void UpdateDriverInfo(Driver^ driver);

    private:
        // Обработчики событий
        System::Void deleteButton_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void cancelButton_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void driverComboBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
    };
}