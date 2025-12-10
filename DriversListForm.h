#pragma once

#include "DriversList.hpp"
#include "AddDriverForm.h"
#include "DeleteDriverForm.h"

namespace InfSystBusStation {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::Collections::Generic;

    /// <summary>
    /// Форма для управления списком водителей
    /// </summary>
    public ref class DriversListForm : public System::Windows::Forms::Form
    {
    public:
        DriversListForm(DriversList^ driversList) {
            InitializeComponent();
            this->driverList = driversList;
            UpdateDataGridView();
        }

    protected:
        ~DriversListForm() {
            if (components) {
                delete components;
            }
        }

    private:
        DriversList^ driverList;
        System::ComponentModel::Container^ components;

        // Элементы формы
    private:
        System::Windows::Forms::MenuStrip^ driversMenuStrip;
        System::Windows::Forms::ToolStripMenuItem^ addDriverMenuItem;
        System::Windows::Forms::ToolStripMenuItem^ deleteDriverMenuItem;
        System::Windows::Forms::ToolStripMenuItem^ backMenuItem;

        System::Windows::Forms::DataGridView^ driversDataGridView;
        System::Windows::Forms::DataGridViewTextBoxColumn^ numColumn;
        System::Windows::Forms::DataGridViewTextBoxColumn^ fioColumn;
        System::Windows::Forms::DataGridViewTextBoxColumn^ genderColumn;
        System::Windows::Forms::DataGridViewTextBoxColumn^ licenseColumn;
        System::Windows::Forms::DataGridViewTextBoxColumn^ passportColumn;
        System::Windows::Forms::DataGridViewTextBoxColumn^ salaryColumn;
        System::Windows::Forms::DataGridViewTextBoxColumn^ statusColumn;
        System::Windows::Forms::Label^ driversCountLabel;
        System::Windows::Forms::Button^ btnRefresh;
        System::Windows::Forms::ContextMenuStrip^ contextMenuStrip;
        System::Windows::Forms::ToolStripMenuItem^ deleteContextMenuItem;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->driversMenuStrip = (gcnew System::Windows::Forms::MenuStrip());
            this->addDriverMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->deleteDriverMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->backMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->driversDataGridView = (gcnew System::Windows::Forms::DataGridView());
            this->numColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->fioColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->genderColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->licenseColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->passportColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->salaryColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->statusColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->driversCountLabel = (gcnew System::Windows::Forms::Label());
            this->btnRefresh = (gcnew System::Windows::Forms::Button());
            this->contextMenuStrip = (gcnew System::Windows::Forms::ContextMenuStrip());
            this->deleteContextMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->driversMenuStrip->SuspendLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->driversDataGridView))->BeginInit();
            this->contextMenuStrip->SuspendLayout();
            this->SuspendLayout();
            // 
            // driversMenuStrip
            // 
            this->driversMenuStrip->BackColor = System::Drawing::SystemColors::ActiveBorder;
            this->driversMenuStrip->ImageScalingSize = System::Drawing::Size(20, 20);
            this->driversMenuStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
                this->addDriverMenuItem, this->deleteDriverMenuItem, this->backMenuItem
            });
            this->driversMenuStrip->Location = System::Drawing::Point(0, 0);
            this->driversMenuStrip->Name = L"driversMenuStrip";
            this->driversMenuStrip->Size = System::Drawing::Size(1200, 28);
            this->driversMenuStrip->TabIndex = 0;
            // 
            // addDriverMenuItem
            // 
            this->addDriverMenuItem->Name = L"addDriverMenuItem";
            this->addDriverMenuItem->Size = System::Drawing::Size(149, 24);
            this->addDriverMenuItem->Text = L"Добавить водителя";
            this->addDriverMenuItem->Click += gcnew System::EventHandler(this, &DriversListForm::AddDriver_Click);
            // 
            // deleteDriverMenuItem
            // 
            this->deleteDriverMenuItem->Name = L"deleteDriverMenuItem";
            this->deleteDriverMenuItem->Size = System::Drawing::Size(138, 24);
            this->deleteDriverMenuItem->Text = L"Удалить водителя";
            this->deleteDriverMenuItem->Click += gcnew System::EventHandler(this, &DriversListForm::DeleteDriver_Click);
            // 
            // backMenuItem
            // 
            this->backMenuItem->Name = L"backMenuItem";
            this->backMenuItem->Size = System::Drawing::Size(65, 24);
            this->backMenuItem->Text = L"Назад";
            this->backMenuItem->Click += gcnew System::EventHandler(this, &DriversListForm::Back_Click);
            // 
            // driversDataGridView
            // 
            this->driversDataGridView->AllowUserToAddRows = false;
            this->driversDataGridView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
            this->driversDataGridView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(7) {
                this->numColumn,
                    this->fioColumn, this->genderColumn, this->licenseColumn, this->passportColumn,
                    this->salaryColumn, this->statusColumn
            });
            this->driversDataGridView->ContextMenuStrip = this->contextMenuStrip;
            this->driversDataGridView->Location = System::Drawing::Point(12, 40);
            this->driversDataGridView->Name = L"driversDataGridView";
            this->driversDataGridView->ReadOnly = true;
            this->driversDataGridView->RowHeadersWidth = 51;
            this->driversDataGridView->RowTemplate->Height = 24;
            this->driversDataGridView->Size = System::Drawing::Size(1176, 380);
            this->driversDataGridView->TabIndex = 1;
            this->driversDataGridView->CellDoubleClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &DriversListForm::driversDataGridView_CellDoubleClick);
            // 
            // numColumn
            // 
            this->numColumn->HeaderText = L"№";
            this->numColumn->MinimumWidth = 6;
            this->numColumn->Name = L"numColumn";
            this->numColumn->ReadOnly = true;
            this->numColumn->Width = 50;
            // 
            // fioColumn
            // 
            this->fioColumn->HeaderText = L"ФИО";
            this->fioColumn->MinimumWidth = 6;
            this->fioColumn->Name = L"fioColumn";
            this->fioColumn->ReadOnly = true;
            this->fioColumn->Width = 200;
            // 
            // genderColumn
            // 
            this->genderColumn->HeaderText = L"Пол";
            this->genderColumn->MinimumWidth = 6;
            this->genderColumn->Name = L"genderColumn";
            this->genderColumn->ReadOnly = true;
            this->genderColumn->Width = 60;
            // 
            // licenseColumn
            // 
            this->licenseColumn->HeaderText = L"Водительские права";
            this->licenseColumn->MinimumWidth = 6;
            this->licenseColumn->Name = L"licenseColumn";
            this->licenseColumn->ReadOnly = true;
            this->licenseColumn->Width = 150;
            // 
            // passportColumn
            // 
            this->passportColumn->HeaderText = L"Паспортные данные";
            this->passportColumn->MinimumWidth = 6;
            this->passportColumn->Name = L"passportColumn";
            this->passportColumn->ReadOnly = true;
            this->passportColumn->Width = 150;
            // 
            // salaryColumn
            // 
            this->salaryColumn->HeaderText = L"Зарплата";
            this->salaryColumn->MinimumWidth = 6;
            this->salaryColumn->Name = L"salaryColumn";
            this->salaryColumn->ReadOnly = true;
            this->salaryColumn->Width = 100;
            // 
            // statusColumn
            // 
            this->statusColumn->HeaderText = L"Статус";
            this->statusColumn->MinimumWidth = 6;
            this->statusColumn->Name = L"statusColumn";
            this->statusColumn->ReadOnly = true;
            this->statusColumn->Width = 120;
            // 
            // driversCountLabel
            // 
            this->driversCountLabel->AutoSize = true;
            this->driversCountLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->driversCountLabel->Location = System::Drawing::Point(12, 430);
            this->driversCountLabel->Name = L"driversCountLabel";
            this->driversCountLabel->Size = System::Drawing::Size(165, 20);
            this->driversCountLabel->TabIndex = 2;
            this->driversCountLabel->Text = L"Всего водителей: 0";
            // 
            // btnRefresh
            // 
            this->btnRefresh->Location = System::Drawing::Point(1070, 425);
            this->btnRefresh->Name = L"btnRefresh";
            this->btnRefresh->Size = System::Drawing::Size(118, 30);
            this->btnRefresh->TabIndex = 3;
            this->btnRefresh->Text = L"Обновить";
            this->btnRefresh->UseVisualStyleBackColor = true;
            this->btnRefresh->Click += gcnew System::EventHandler(this, &DriversListForm::Refresh_Click);
            // 
            // contextMenuStrip
            // 
            this->contextMenuStrip->ImageScalingSize = System::Drawing::Size(20, 20);
            this->contextMenuStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->deleteContextMenuItem });
            this->contextMenuStrip->Name = L"contextMenuStrip";
            this->contextMenuStrip->Size = System::Drawing::Size(138, 28);
            // 
            // deleteContextMenuItem
            // 
            this->deleteContextMenuItem->Name = L"deleteContextMenuItem";
            this->deleteContextMenuItem->Size = System::Drawing::Size(137, 24);
            this->deleteContextMenuItem->Text = L"Удалить";
            this->deleteContextMenuItem->Click += gcnew System::EventHandler(this, &DriversListForm::DeleteContextMenu_Click);
            // 
            // DriversListForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->BackColor = System::Drawing::SystemColors::InactiveCaption;
            this->ClientSize = System::Drawing::Size(1200, 470);
            this->Controls->Add(this->btnRefresh);
            this->Controls->Add(this->driversCountLabel);
            this->Controls->Add(this->driversDataGridView);
            this->Controls->Add(this->driversMenuStrip);
            this->MainMenuStrip = this->driversMenuStrip;
            this->Name = L"DriversListForm";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->Text = L"Список водителей";
            this->driversMenuStrip->ResumeLayout(false);
            this->driversMenuStrip->PerformLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->driversDataGridView))->EndInit();
            this->contextMenuStrip->ResumeLayout(false);
            this->ResumeLayout(false);
            this->PerformLayout();
        }
#pragma endregion

    public:
        // Метод для обновления DataGridView
        void UpdateDataGridView();

    private:
        // Обработчики событий
        System::Void AddDriver_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void DeleteDriver_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void Back_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void Refresh_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void DeleteContextMenu_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void driversDataGridView_CellDoubleClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e);
    };
}