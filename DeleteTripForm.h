// DeleteTripForm.h
#pragma once

#include "TripList.hpp"

namespace InfSystBusStation {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    /// <summary>
    /// Форма для удаления поездки
    /// </summary>
    public ref class DeleteTripForm : public System::Windows::Forms::Form
    {
    public:
        DeleteTripForm(TripList^ tripList) {
            InitializeComponent();
            this->tripList = tripList;
            LoadTripRoutes();
        }

    protected:
        ~DeleteTripForm() {
            if (components) {
                delete components;
            }
        }

    private:
        TripList^ tripList;
        System::ComponentModel::Container^ components;

        // Элементы формы
    private:
        System::Windows::Forms::Label^ label1;
        System::Windows::Forms::ComboBox^ tripComboBox;
        System::Windows::Forms::Button^ deleteButton;
        System::Windows::Forms::Button^ cancelButton;
        System::Windows::Forms::Label^ infoLabel;
        System::Windows::Forms::GroupBox^ tripInfoGroup;
        System::Windows::Forms::Label^ routeLabel;
        System::Windows::Forms::Label^ dateLabel;
        System::Windows::Forms::Label^ timeLabel;
        System::Windows::Forms::Label^ priceLabel;
        System::Windows::Forms::Label^ busLabel;
        System::Windows::Forms::Label^ driverLabel;
        System::Windows::Forms::Label^ statusLabel;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->tripComboBox = (gcnew System::Windows::Forms::ComboBox());
            this->deleteButton = (gcnew System::Windows::Forms::Button());
            this->cancelButton = (gcnew System::Windows::Forms::Button());
            this->infoLabel = (gcnew System::Windows::Forms::Label());
            this->tripInfoGroup = (gcnew System::Windows::Forms::GroupBox());
            this->routeLabel = (gcnew System::Windows::Forms::Label());
            this->dateLabel = (gcnew System::Windows::Forms::Label());
            this->timeLabel = (gcnew System::Windows::Forms::Label());
            this->priceLabel = (gcnew System::Windows::Forms::Label());
            this->busLabel = (gcnew System::Windows::Forms::Label());
            this->driverLabel = (gcnew System::Windows::Forms::Label());
            this->statusLabel = (gcnew System::Windows::Forms::Label());
            this->tripInfoGroup->SuspendLayout();
            this->SuspendLayout();

            // label1
            this->label1->AutoSize = true;
            this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label1->Location = System::Drawing::Point(12, 20);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(269, 20);
            this->label1->TabIndex = 0;
            this->label1->Text = L"Выберите поездку для удаления:";

            // tripComboBox
            this->tripComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->tripComboBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->tripComboBox->FormattingEnabled = true;
            this->tripComboBox->Location = System::Drawing::Point(16, 50);
            this->tripComboBox->Name = L"tripComboBox";
            this->tripComboBox->Size = System::Drawing::Size(400, 28);
            this->tripComboBox->TabIndex = 1;
            this->tripComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &DeleteTripForm::tripComboBox_SelectedIndexChanged);

            // deleteButton
            this->deleteButton->BackColor = System::Drawing::Color::LightCoral;
            this->deleteButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->deleteButton->Location = System::Drawing::Point(250, 380);
            this->deleteButton->Name = L"deleteButton";
            this->deleteButton->Size = System::Drawing::Size(166, 40);
            this->deleteButton->TabIndex = 2;
            this->deleteButton->Text = L"Удалить";
            this->deleteButton->UseVisualStyleBackColor = false;
            this->deleteButton->Click += gcnew System::EventHandler(this, &DeleteTripForm::deleteButton_Click);

            // cancelButton
            this->cancelButton->BackColor = System::Drawing::SystemColors::InactiveCaption;
            this->cancelButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->cancelButton->Location = System::Drawing::Point(16, 380);
            this->cancelButton->Name = L"cancelButton";
            this->cancelButton->Size = System::Drawing::Size(166, 40);
            this->cancelButton->TabIndex = 3;
            this->cancelButton->Text = L"Отмена";
            this->cancelButton->UseVisualStyleBackColor = false;
            this->cancelButton->Click += gcnew System::EventHandler(this, &DeleteTripForm::cancelButton_Click);

            // infoLabel
            this->infoLabel->AutoSize = true;
            this->infoLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->infoLabel->ForeColor = System::Drawing::Color::DarkRed;
            this->infoLabel->Location = System::Drawing::Point(16, 85);
            this->infoLabel->Name = L"infoLabel";
            this->infoLabel->Size = System::Drawing::Size(362, 18);
            this->infoLabel->TabIndex = 4;
            this->infoLabel->Text = L"Выберите поездку для просмотра информации";

            // tripInfoGroup
            this->tripInfoGroup->Controls->Add(this->statusLabel);
            this->tripInfoGroup->Controls->Add(this->driverLabel);
            this->tripInfoGroup->Controls->Add(this->busLabel);
            this->tripInfoGroup->Controls->Add(this->priceLabel);
            this->tripInfoGroup->Controls->Add(this->timeLabel);
            this->tripInfoGroup->Controls->Add(this->dateLabel);
            this->tripInfoGroup->Controls->Add(this->routeLabel);
            this->tripInfoGroup->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->tripInfoGroup->Location = System::Drawing::Point(16, 115);
            this->tripInfoGroup->Name = L"tripInfoGroup";
            this->tripInfoGroup->Size = System::Drawing::Size(400, 250);
            this->tripInfoGroup->TabIndex = 5;
            this->tripInfoGroup->TabStop = false;
            this->tripInfoGroup->Text = L"Информация о поездке";

            // routeLabel
            this->routeLabel->AutoSize = true;
            this->routeLabel->Location = System::Drawing::Point(10, 30);
            this->routeLabel->Name = L"routeLabel";
            this->routeLabel->Size = System::Drawing::Size(64, 18);
            this->routeLabel->TabIndex = 6;
            this->routeLabel->Text = L"Маршрут:";

            // dateLabel
            this->dateLabel->AutoSize = true;
            this->dateLabel->Location = System::Drawing::Point(10, 60);
            this->dateLabel->Name = L"dateLabel";
            this->dateLabel->Size = System::Drawing::Size(45, 18);
            this->dateLabel->TabIndex = 7;
            this->dateLabel->Text = L"Дата:";

            // timeLabel
            this->timeLabel->AutoSize = true;
            this->timeLabel->Location = System::Drawing::Point(10, 90);
            this->timeLabel->Name = L"timeLabel";
            this->timeLabel->Size = System::Drawing::Size(54, 18);
            this->timeLabel->TabIndex = 8;
            this->timeLabel->Text = L"Время:";

            // priceLabel
            this->priceLabel->AutoSize = true;
            this->priceLabel->Location = System::Drawing::Point(10, 120);
            this->priceLabel->Name = L"priceLabel";
            this->priceLabel->Size = System::Drawing::Size(45, 18);
            this->priceLabel->TabIndex = 9;
            this->priceLabel->Text = L"Цена:";

            // busLabel
            this->busLabel->AutoSize = true;
            this->busLabel->Location = System::Drawing::Point(10, 150);
            this->busLabel->Name = L"busLabel";
            this->busLabel->Size = System::Drawing::Size(76, 18);
            this->busLabel->TabIndex = 10;
            this->busLabel->Text = L"Автобус:";

            // driverLabel
            this->driverLabel->AutoSize = true;
            this->driverLabel->Location = System::Drawing::Point(10, 180);
            this->driverLabel->Name = L"driverLabel";
            this->driverLabel->Size = System::Drawing::Size(74, 18);
            this->driverLabel->TabIndex = 11;
            this->driverLabel->Text = L"Водитель:";

            // statusLabel
            this->statusLabel->AutoSize = true;
            this->statusLabel->Location = System::Drawing::Point(10, 210);
            this->statusLabel->Name = L"statusLabel";
            this->statusLabel->Size = System::Drawing::Size(56, 18);
            this->statusLabel->TabIndex = 12;
            this->statusLabel->Text = L"Статус:";

            // DeleteTripForm
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->BackColor = System::Drawing::SystemColors::InactiveCaption;
            this->ClientSize = System::Drawing::Size(432, 433);
            this->Controls->Add(this->tripInfoGroup);
            this->Controls->Add(this->infoLabel);
            this->Controls->Add(this->cancelButton);
            this->Controls->Add(this->deleteButton);
            this->Controls->Add(this->tripComboBox);
            this->Controls->Add(this->label1);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->MaximizeBox = false;
            this->MinimizeBox = false;
            this->Name = L"DeleteTripForm";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
            this->Text = L"Удаление поездки";
            this->tripInfoGroup->ResumeLayout(false);
            this->tripInfoGroup->PerformLayout();
            this->ResumeLayout(false);
            this->PerformLayout();
        }
#pragma endregion

    private:
        // Метод для загрузки маршрутов поездок в ComboBox
        void LoadTripRoutes();

        // Метод для обновления информации о выбранной поездке
        void UpdateTripInfo(Trip^ trip);

    private:
        // Обработчики событий
        System::Void deleteButton_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void cancelButton_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void tripComboBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
    };
}