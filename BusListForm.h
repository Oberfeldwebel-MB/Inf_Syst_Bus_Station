// BusListForm.h
#pragma once

#include "BusList.hpp"

namespace InfSystBusStation {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::Collections::Generic;

    public ref class BusListForm : public System::Windows::Forms::Form {
    public:
        BusListForm(BusList^ busList) {
            InitializeComponent();
            this->busList = busList;
            UpdateDataGridView();
        }

    protected:
        ~BusListForm() {
            if (components) {
                delete components;
            }
        }

    private:
        BusList^ busList;
        System::ComponentModel::Container^ components;

        // Элементы формы
    private:
        System::Windows::Forms::MenuStrip^ menuStrip;
        System::Windows::Forms::ToolStripMenuItem^ addBusMenuItem;
        System::Windows::Forms::ToolStripMenuItem^ deleteBusMenuItem;
        System::Windows::Forms::ToolStripMenuItem^ backMenuItem;

        System::Windows::Forms::DataGridView^ busesDataGridView;
        System::Windows::Forms::DataGridViewCheckBoxColumn^ selectColumn; // Новая колонка
        System::Windows::Forms::DataGridViewTextBoxColumn^ numColumn;
        System::Windows::Forms::DataGridViewTextBoxColumn^ codeColumn;
        System::Windows::Forms::DataGridViewTextBoxColumn^ brandColumn;
        System::Windows::Forms::DataGridViewTextBoxColumn^ modelColumn;
        System::Windows::Forms::DataGridViewTextBoxColumn^ placesColumn;
        System::Windows::Forms::DataGridViewTextBoxColumn^ conditionColumn;
        System::Windows::Forms::DataGridViewTextBoxColumn^ lastMaintenanceColumn;
        System::Windows::Forms::DataGridViewTextBoxColumn^ statusColumn;

        System::Windows::Forms::Label^ busesCountLabel;
        System::Windows::Forms::Label^ availableLabel;
        System::Windows::Forms::Button^ btnRefresh;
        System::Windows::Forms::Button^ btnSendToMaintenance; // Новая кнопка
        System::Windows::Forms::Label^ label1;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->menuStrip = (gcnew System::Windows::Forms::MenuStrip());
            this->addBusMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->deleteBusMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->backMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->busesDataGridView = (gcnew System::Windows::Forms::DataGridView());
            this->selectColumn = (gcnew System::Windows::Forms::DataGridViewCheckBoxColumn());
            this->numColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->codeColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->brandColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->modelColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->placesColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->conditionColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->lastMaintenanceColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->statusColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->busesCountLabel = (gcnew System::Windows::Forms::Label());
            this->availableLabel = (gcnew System::Windows::Forms::Label());
            this->btnRefresh = (gcnew System::Windows::Forms::Button());
            this->btnSendToMaintenance = (gcnew System::Windows::Forms::Button());
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->menuStrip->SuspendLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->busesDataGridView))->BeginInit();
            this->SuspendLayout();
            // 
            // menuStrip
            // 
            this->menuStrip->BackColor = System::Drawing::SystemColors::ActiveBorder;
            this->menuStrip->ImageScalingSize = System::Drawing::Size(20, 20);
            this->menuStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
                this->addBusMenuItem, this->deleteBusMenuItem,
                    this->backMenuItem
            });
            this->menuStrip->Location = System::Drawing::Point(0, 0);
            this->menuStrip->Name = L"menuStrip";
            this->menuStrip->Size = System::Drawing::Size(1139, 28);
            this->menuStrip->TabIndex = 0;
            this->menuStrip->Text = L"menuStrip1";
            // 
            // addBusMenuItem
            // 
            this->addBusMenuItem->Name = L"addBusMenuItem";
            this->addBusMenuItem->Size = System::Drawing::Size(148, 24);
            this->addBusMenuItem->Text = L"Добавить автобус";
            this->addBusMenuItem->Click += gcnew System::EventHandler(this, &BusListForm::AddBus_Click);
            // 
            // deleteBusMenuItem
            // 
            this->deleteBusMenuItem->Name = L"deleteBusMenuItem";
            this->deleteBusMenuItem->Size = System::Drawing::Size(137, 24);
            this->deleteBusMenuItem->Text = L"Удалить автобус";
            this->deleteBusMenuItem->Click += gcnew System::EventHandler(this, &BusListForm::DeleteBus_Click);
            // 
            // backMenuItem
            // 
            this->backMenuItem->Name = L"backMenuItem";
            this->backMenuItem->Size = System::Drawing::Size(65, 24);
            this->backMenuItem->Text = L"Назад";
            this->backMenuItem->Click += gcnew System::EventHandler(this, &BusListForm::Back_Click);
            // 
            // busesDataGridView
            // 
            this->busesDataGridView->AllowUserToAddRows = false;
            this->busesDataGridView->AllowUserToDeleteRows = false;
            this->busesDataGridView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
            this->busesDataGridView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(9) {
                this->selectColumn,
                    this->numColumn, this->codeColumn, this->brandColumn, this->modelColumn, this->placesColumn, this->conditionColumn, this->lastMaintenanceColumn,
                    this->statusColumn
            });
            this->busesDataGridView->Location = System::Drawing::Point(12, 44);
            this->busesDataGridView->Name = L"busesDataGridView";
            this->busesDataGridView->RowHeadersWidth = 51;
            this->busesDataGridView->RowTemplate->Height = 24;
            this->busesDataGridView->Size = System::Drawing::Size(1115, 350);
            this->busesDataGridView->TabIndex = 1;
            // 
            // selectColumn
            // 
            this->selectColumn->HeaderText = L"Выбрать";
            this->selectColumn->MinimumWidth = 6;
            this->selectColumn->Name = L"selectColumn";
            this->selectColumn->Width = 70;
            // 
            // numColumn
            // 
            this->numColumn->HeaderText = L"№";
            this->numColumn->MinimumWidth = 6;
            this->numColumn->Name = L"numColumn";
            this->numColumn->ReadOnly = true;
            this->numColumn->Width = 50;
            // 
            // codeColumn
            // 
            this->codeColumn->HeaderText = L"Код автобуса";
            this->codeColumn->MinimumWidth = 6;
            this->codeColumn->Name = L"codeColumn";
            this->codeColumn->ReadOnly = true;
            this->codeColumn->Width = 120;
            // 
            // brandColumn
            // 
            this->brandColumn->HeaderText = L"Марка";
            this->brandColumn->MinimumWidth = 6;
            this->brandColumn->Name = L"brandColumn";
            this->brandColumn->ReadOnly = true;
            this->brandColumn->Width = 120;
            // 
            // modelColumn
            // 
            this->modelColumn->HeaderText = L"Модель";
            this->modelColumn->MinimumWidth = 6;
            this->modelColumn->Name = L"modelColumn";
            this->modelColumn->ReadOnly = true;
            this->modelColumn->Width = 120;
            // 
            // placesColumn
            // 
            this->placesColumn->HeaderText = L"Количество мест";
            this->placesColumn->MinimumWidth = 6;
            this->placesColumn->Name = L"placesColumn";
            this->placesColumn->ReadOnly = true;
            this->placesColumn->Width = 120;
            // 
            // conditionColumn
            // 
            this->conditionColumn->HeaderText = L"Техническое состояние";
            this->conditionColumn->MinimumWidth = 6;
            this->conditionColumn->Name = L"conditionColumn";
            this->conditionColumn->ReadOnly = true;
            this->conditionColumn->Width = 150;
            // 
            // lastMaintenanceColumn
            // 
            this->lastMaintenanceColumn->HeaderText = L"Последнее ТО";
            this->lastMaintenanceColumn->MinimumWidth = 6;
            this->lastMaintenanceColumn->Name = L"lastMaintenanceColumn";
            this->lastMaintenanceColumn->ReadOnly = true;
            this->lastMaintenanceColumn->Width = 120;
            // 
            // statusColumn
            // 
            this->statusColumn->HeaderText = L"Статус";
            this->statusColumn->MinimumWidth = 6;
            this->statusColumn->Name = L"statusColumn";
            this->statusColumn->ReadOnly = true;
            // 
            // busesCountLabel
            // 
            this->busesCountLabel->AutoSize = true;
            this->busesCountLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold));
            this->busesCountLabel->Location = System::Drawing::Point(12, 400);
            this->busesCountLabel->Name = L"busesCountLabel";
            this->busesCountLabel->Size = System::Drawing::Size(187, 20);
            this->busesCountLabel->TabIndex = 2;
            this->busesCountLabel->Text = L"Всего автобусов: 0";
            // 
            // availableLabel
            // 
            this->availableLabel->AutoSize = true;
            this->availableLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold));
            this->availableLabel->Location = System::Drawing::Point(12, 430);
            this->availableLabel->Name = L"availableLabel";
            this->availableLabel->Size = System::Drawing::Size(119, 20);
            this->availableLabel->TabIndex = 3;
            this->availableLabel->Text = L"Доступно: 0";
            // 
            // btnRefresh
            // 
            this->btnRefresh->Location = System::Drawing::Point(866, 400);
            this->btnRefresh->Name = L"btnRefresh";
            this->btnRefresh->Size = System::Drawing::Size(118, 30);
            this->btnRefresh->TabIndex = 4;
            this->btnRefresh->Text = L"Обновить список";
            this->btnRefresh->UseVisualStyleBackColor = true;
            this->btnRefresh->Click += gcnew System::EventHandler(this, &BusListForm::Refresh_Click);
            // 
            // btnSendToMaintenance
            // 
            this->btnSendToMaintenance->Location = System::Drawing::Point(1009, 400);
            this->btnSendToMaintenance->Name = L"btnSendToMaintenance";
            this->btnSendToMaintenance->Size = System::Drawing::Size(118, 50);
            this->btnSendToMaintenance->TabIndex = 5;
            this->btnSendToMaintenance->Text = L"Отправить на ТО";
            this->btnSendToMaintenance->UseVisualStyleBackColor = true;
            this->btnSendToMaintenance->Click += gcnew System::EventHandler(this, &BusListForm::SendToMaintenance_Click);
            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Italic));
            this->label1->Location = System::Drawing::Point(12, 460);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(430, 20);
            this->label1->TabIndex = 6;
            this->label1->Text = L"Для добавления или удаления используйте меню";
            // 
            // BusListForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->BackColor = System::Drawing::SystemColors::InactiveCaption;
            this->ClientSize = System::Drawing::Size(1139, 490);
            this->Controls->Add(this->label1);
            this->Controls->Add(this->btnSendToMaintenance);
            this->Controls->Add(this->btnRefresh);
            this->Controls->Add(this->availableLabel);
            this->Controls->Add(this->busesCountLabel);
            this->Controls->Add(this->busesDataGridView);
            this->Controls->Add(this->menuStrip);
            this->MainMenuStrip = this->menuStrip;
            this->Name = L"BusListForm";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->Text = L"Список автобусов";
            this->menuStrip->ResumeLayout(false);
            this->menuStrip->PerformLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->busesDataGridView))->EndInit();
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion

    public:
        void UpdateDataGridView();

    private:
        // Обработчики событий
        System::Void AddBus_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void DeleteBus_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void Back_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void Refresh_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void SendToMaintenance_Click(System::Object^ sender, System::EventArgs^ e); 
    };
}