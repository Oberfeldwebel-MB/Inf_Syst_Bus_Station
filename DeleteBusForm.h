// DeleteBusForm.h
#pragma once

#include "BusList.hpp"


namespace InfSystBusStation {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    /// <summary>
    /// Форма для удаления автобуса
    /// </summary>
    public ref class DeleteBusForm : public System::Windows::Forms::Form
    {
    public:
        DeleteBusForm(BusList^ busList);  // Только объявление
        ~DeleteBusForm();

    private:
        BusList^ busList;
        System::ComponentModel::Container^ components;

        // Элементы формы
    private:
        System::Windows::Forms::Label^ label1;
        System::Windows::Forms::ComboBox^ busComboBox;
        System::Windows::Forms::Button^ deleteButton;
        System::Windows::Forms::Button^ cancelButton;
        System::Windows::Forms::Label^ infoLabel;
        System::Windows::Forms::GroupBox^ busInfoGroup;
        System::Windows::Forms::Label^ brandLabel;
        System::Windows::Forms::Label^ modelLabel;
        System::Windows::Forms::Label^ placesLabel;
        System::Windows::Forms::Label^ conditionLabel;
        System::Windows::Forms::Label^ maintenanceLabel;
        System::Windows::Forms::Label^ statusLabel;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->busComboBox = (gcnew System::Windows::Forms::ComboBox());
            this->deleteButton = (gcnew System::Windows::Forms::Button());
            this->cancelButton = (gcnew System::Windows::Forms::Button());
            this->infoLabel = (gcnew System::Windows::Forms::Label());
            this->busInfoGroup = (gcnew System::Windows::Forms::GroupBox());
            this->brandLabel = (gcnew System::Windows::Forms::Label());
            this->modelLabel = (gcnew System::Windows::Forms::Label());
            this->placesLabel = (gcnew System::Windows::Forms::Label());
            this->conditionLabel = (gcnew System::Windows::Forms::Label());
            this->maintenanceLabel = (gcnew System::Windows::Forms::Label());
            this->statusLabel = (gcnew System::Windows::Forms::Label());
            this->busInfoGroup->SuspendLayout();
            this->SuspendLayout();

            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label1->Location = System::Drawing::Point(12, 20);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(268, 20);
            this->label1->TabIndex = 0;
            this->label1->Text = L"Выберите автобус для удаления:";

            // 
            // busComboBox
            // 
            this->busComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->busComboBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->busComboBox->FormattingEnabled = true;
            this->busComboBox->Location = System::Drawing::Point(16, 50);
            this->busComboBox->Name = L"busComboBox";
            this->busComboBox->Size = System::Drawing::Size(400, 28);
            this->busComboBox->TabIndex = 1;
            this->busComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &DeleteBusForm::busComboBox_SelectedIndexChanged);

            // 
            // deleteButton
            // 
            this->deleteButton->BackColor = System::Drawing::Color::LightCoral;
            this->deleteButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->deleteButton->Location = System::Drawing::Point(250, 350);
            this->deleteButton->Name = L"deleteButton";
            this->deleteButton->Size = System::Drawing::Size(166, 40);
            this->deleteButton->TabIndex = 2;
            this->deleteButton->Text = L"Удалить";
            this->deleteButton->UseVisualStyleBackColor = false;
            this->deleteButton->Click += gcnew System::EventHandler(this, &DeleteBusForm::deleteButton_Click);

            // 
            // cancelButton
            // 
            this->cancelButton->BackColor = System::Drawing::SystemColors::InactiveCaption;
            this->cancelButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->cancelButton->Location = System::Drawing::Point(16, 350);
            this->cancelButton->Name = L"cancelButton";
            this->cancelButton->Size = System::Drawing::Size(166, 40);
            this->cancelButton->TabIndex = 3;
            this->cancelButton->Text = L"Отмена";
            this->cancelButton->UseVisualStyleBackColor = false;
            this->cancelButton->Click += gcnew System::EventHandler(this, &DeleteBusForm::cancelButton_Click);

            // 
            // infoLabel
            // 
            this->infoLabel->AutoSize = true;
            this->infoLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->infoLabel->ForeColor = System::Drawing::Color::DarkRed;
            this->infoLabel->Location = System::Drawing::Point(16, 85);
            this->infoLabel->Name = L"infoLabel";
            this->infoLabel->Size = System::Drawing::Size(354, 18);
            this->infoLabel->TabIndex = 4;
            this->infoLabel->Text = L"Выберите автобус для просмотра информации";

            // 
            // busInfoGroup
            // 
            this->busInfoGroup->Controls->Add(this->statusLabel);
            this->busInfoGroup->Controls->Add(this->maintenanceLabel);
            this->busInfoGroup->Controls->Add(this->conditionLabel);
            this->busInfoGroup->Controls->Add(this->placesLabel);
            this->busInfoGroup->Controls->Add(this->modelLabel);
            this->busInfoGroup->Controls->Add(this->brandLabel);
            this->busInfoGroup->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->busInfoGroup->Location = System::Drawing::Point(16, 115);
            this->busInfoGroup->Name = L"busInfoGroup";
            this->busInfoGroup->Size = System::Drawing::Size(400, 220);
            this->busInfoGroup->TabIndex = 5;
            this->busInfoGroup->TabStop = false;
            this->busInfoGroup->Text = L"Информация об автобусе";

            // 
            // brandLabel
            // 
            this->brandLabel->AutoSize = true;
            this->brandLabel->Location = System::Drawing::Point(10, 30);
            this->brandLabel->Name = L"brandLabel";
            this->brandLabel->Size = System::Drawing::Size(52, 18);
            this->brandLabel->TabIndex = 6;
            this->brandLabel->Text = L"Марка:";

            // 
            // modelLabel
            // 
            this->modelLabel->AutoSize = true;
            this->modelLabel->Location = System::Drawing::Point(10, 60);
            this->modelLabel->Name = L"modelLabel";
            this->modelLabel->Size = System::Drawing::Size(58, 18);
            this->modelLabel->TabIndex = 7;
            this->modelLabel->Text = L"Модель:";

            // 
            // placesLabel
            // 
            this->placesLabel->AutoSize = true;
            this->placesLabel->Location = System::Drawing::Point(10, 90);
            this->placesLabel->Name = L"placesLabel";
            this->placesLabel->Size = System::Drawing::Size(104, 18);
            this->placesLabel->TabIndex = 8;
            this->placesLabel->Text = L"Количество мест:";

            // 
            // conditionLabel
            // 
            this->conditionLabel->AutoSize = true;
            this->conditionLabel->Location = System::Drawing::Point(10, 120);
            this->conditionLabel->Name = L"conditionLabel";
            this->conditionLabel->Size = System::Drawing::Size(159, 18);
            this->conditionLabel->TabIndex = 9;
            this->conditionLabel->Text = L"Техническое состояние:";

            // 
            // maintenanceLabel
            // 
            this->maintenanceLabel->AutoSize = true;
            this->maintenanceLabel->Location = System::Drawing::Point(10, 150);
            this->maintenanceLabel->Name = L"maintenanceLabel";
            this->maintenanceLabel->Size = System::Drawing::Size(98, 18);
            this->maintenanceLabel->TabIndex = 10;
            this->maintenanceLabel->Text = L"Последнее ТО:";

            // 
            // statusLabel
            // 
            this->statusLabel->AutoSize = true;
            this->statusLabel->Location = System::Drawing::Point(10, 180);
            this->statusLabel->Name = L"statusLabel";
            this->statusLabel->Size = System::Drawing::Size(56, 18);
            this->statusLabel->TabIndex = 11;
            this->statusLabel->Text = L"Статус:";

            // 
            // DeleteBusForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->BackColor = System::Drawing::SystemColors::InactiveCaption;
            this->ClientSize = System::Drawing::Size(432, 403);
            this->Controls->Add(this->busInfoGroup);
            this->Controls->Add(this->infoLabel);
            this->Controls->Add(this->cancelButton);
            this->Controls->Add(this->deleteButton);
            this->Controls->Add(this->busComboBox);
            this->Controls->Add(this->label1);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->MaximizeBox = false;
            this->MinimizeBox = false;
            this->Name = L"DeleteBusForm";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
            this->Text = L"Удаление автобуса";
            this->busInfoGroup->ResumeLayout(false);
            this->busInfoGroup->PerformLayout();
            this->ResumeLayout(false);
            this->PerformLayout();
        }
#pragma endregion

    private:
        // Метод для загрузки кодов автобусов в ComboBox
        void LoadBusCodes();

        // Метод для обновления информации о выбранном автобусе
        void UpdateBusInfo(Bus^ bus);

        // Метод для очистки информации об автобусе
        void ClearBusInfo();

    private:
        // Обработчики событий
        System::Void deleteButton_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void cancelButton_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void busComboBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
    };
}