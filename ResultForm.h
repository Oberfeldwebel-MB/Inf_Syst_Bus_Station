#pragma once

#include "TripList.hpp"
#include "AddTripForm.h"
#include "DeleteTripForm.h"

namespace InfSystBusStation {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::Collections::Generic;

    public ref class TimingForm : public System::Windows::Forms::Form {
    public:
        TimingForm(TripList^ tripList, BusList^ busList, DriversList^ driverList) {
            InitializeComponent();
            this->tripList = tripList;
            this->busList = busList;
            this->driverList = driverList;
            UpdateDataGridView();
        }

    protected:
        ~TimingForm() {
            if (components) {
                delete components;
            }
        }

    private:
        TripList^ tripList;
        BusList^ busList;
        DriversList^ driverList;
        System::ComponentModel::Container^ components;

        // Элементы формы
    private:
        System::Windows::Forms::MenuStrip^ menuStrip;
        System::Windows::Forms::ToolStripMenuItem^ addTripMenuItem;
        System::Windows::Forms::ToolStripMenuItem^ deleteTripMenuItem;
        System::Windows::Forms::ToolStripMenuItem^ editTripMenuItem;
        System::Windows::Forms::ToolStripMenuItem^ searchMenuItem;
        System::Windows::Forms::ToolStripMenuItem^ backMenuItem;

        System::Windows::Forms::DataGridView^ tripsDataGridView;
    private: System::Windows::Forms::DataGridViewCheckBoxColumn^ selectColumn;
    private: System::Windows::Forms::DataGridViewTextBoxColumn^ numColumn;
    private: System::Windows::Forms::DataGridViewTextBoxColumn^ startPointColumn;
    private: System::Windows::Forms::DataGridViewTextBoxColumn^ finishPointColumn;
    private: System::Windows::Forms::DataGridViewTextBoxColumn^ busColumn;
    private: System::Windows::Forms::DataGridViewTextBoxColumn^ depDateColumn;
    private: System::Windows::Forms::DataGridViewTextBoxColumn^ arrDateColumn;
    private: System::Windows::Forms::DataGridViewTextBoxColumn^ priceColumn;
    private: System::Windows::Forms::DataGridViewTextBoxColumn^ driverColumn;
           // Колонка для выбора одной поездки


           System::Windows::Forms::Button^ btnBuyTicket;

#pragma region Windows Form Designer generated code
           void InitializeComponent(void) {
               this->menuStrip = (gcnew System::Windows::Forms::MenuStrip());
               this->addTripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->deleteTripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->editTripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->searchMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->backMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->tripsDataGridView = (gcnew System::Windows::Forms::DataGridView());
               this->selectColumn = (gcnew System::Windows::Forms::DataGridViewCheckBoxColumn());
               this->numColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
               this->startPointColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
               this->finishPointColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
               this->busColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
               this->depDateColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
               this->arrDateColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
               this->priceColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
               this->driverColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
               this->btnBuyTicket = (gcnew System::Windows::Forms::Button());
               this->menuStrip->SuspendLayout();
               (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tripsDataGridView))->BeginInit();
               this->SuspendLayout();
               // 
               // menuStrip
               // 
               this->menuStrip->BackColor = System::Drawing::SystemColors::ActiveBorder;
               this->menuStrip->ImageScalingSize = System::Drawing::Size(20, 20);
               this->menuStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
                   this->addTripMenuItem, this->deleteTripMenuItem,
                       this->editTripMenuItem, this->searchMenuItem, this->backMenuItem
               });
               this->menuStrip->Location = System::Drawing::Point(0, 0);
               this->menuStrip->Name = L"menuStrip";
               this->menuStrip->Size = System::Drawing::Size(1300, 28);
               this->menuStrip->TabIndex = 0;
               // 
               // addTripMenuItem
               // 
               this->addTripMenuItem->Name = L"addTripMenuItem";
               this->addTripMenuItem->Size = System::Drawing::Size(149, 24);
               this->addTripMenuItem->Text = L"Добавить поездку";
               this->addTripMenuItem->Click += gcnew System::EventHandler(this, &TimingForm::AddTrip_Click);
               // 
               // deleteTripMenuItem
               // 
               this->deleteTripMenuItem->Name = L"deleteTripMenuItem";
               this->deleteTripMenuItem->Size = System::Drawing::Size(138, 24);
               this->deleteTripMenuItem->Text = L"Удалить поездку";
               this->deleteTripMenuItem->Click += gcnew System::EventHandler(this, &TimingForm::DeleteTrip_Click);
               // 
               // editTripMenuItem
               // 
               this->editTripMenuItem->Name = L"editTripMenuItem";
               this->editTripMenuItem->Size = System::Drawing::Size(184, 24);
               this->editTripMenuItem->Text = L"Редактировать поездку";
               this->editTripMenuItem->Click += gcnew System::EventHandler(this, &TimingForm::EditTrip_Click);
               // 
               // searchMenuItem
               // 
               this->searchMenuItem->Name = L"searchMenuItem";
               this->searchMenuItem->Size = System::Drawing::Size(66, 24);
               this->searchMenuItem->Text = L"Поиск";
               this->searchMenuItem->Click += gcnew System::EventHandler(this, &TimingForm::Search_Click);
               // 
               // backMenuItem
               // 
               this->backMenuItem->Name = L"backMenuItem";
               this->backMenuItem->Size = System::Drawing::Size(65, 24);
               this->backMenuItem->Text = L"Назад";
               this->backMenuItem->Click += gcnew System::EventHandler(this, &TimingForm::Back_Click);
               // 
               // tripsDataGridView
               // 
               this->tripsDataGridView->AllowUserToAddRows = false;
               this->tripsDataGridView->AllowUserToDeleteRows = false;
               this->tripsDataGridView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
               this->tripsDataGridView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(9) {
                   this->selectColumn,
                       this->numColumn, this->startPointColumn, this->finishPointColumn, this->busColumn, this->depDateColumn, this->arrDateColumn,
                       this->priceColumn, this->driverColumn
               });
               this->tripsDataGridView->Location = System::Drawing::Point(12, 40);
               this->tripsDataGridView->Name = L"tripsDataGridView";
               this->tripsDataGridView->RowHeadersWidth = 51;
               this->tripsDataGridView->RowTemplate->Height = 24;
               this->tripsDataGridView->Size = System::Drawing::Size(1276, 450);
               this->tripsDataGridView->TabIndex = 1;
               this->tripsDataGridView->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &TimingForm::tripsDataGridView_CellContentClick);
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
               this->numColumn->HeaderText = L"Номер поездки";
               this->numColumn->MinimumWidth = 6;
               this->numColumn->Name = L"numColumn";
               this->numColumn->Width = 125;
               // 
               // startPointColumn
               // 
               this->startPointColumn->HeaderText = L"Начальный пункт";
               this->startPointColumn->MinimumWidth = 6;
               this->startPointColumn->Name = L"startPointColumn";
               this->startPointColumn->Width = 125;
               // 
               // finishPointColumn
               // 
               this->finishPointColumn->HeaderText = L"Конечный пункт";
               this->finishPointColumn->MinimumWidth = 6;
               this->finishPointColumn->Name = L"finishPointColumn";
               this->finishPointColumn->Width = 125;
               // 
               // busColumn
               // 
               this->busColumn->HeaderText = L"Данные об автобусе";
               this->busColumn->MinimumWidth = 6;
               this->busColumn->Name = L"busColumn";
               this->busColumn->Width = 150;
               // 
               // depDateColumn
               // 
               this->depDateColumn->HeaderText = L"Дата отправления";
               this->depDateColumn->MinimumWidth = 6;
               this->depDateColumn->Name = L"depDateColumn";
               this->depDateColumn->Width = 125;
               // 
               // arrDateColumn
               // 
               this->arrDateColumn->HeaderText = L"Дата прибытия";
               this->arrDateColumn->MinimumWidth = 6;
               this->arrDateColumn->Name = L"arrDateColumn";
               this->arrDateColumn->Width = 125;
               // 
               // priceColumn
               // 
               this->priceColumn->HeaderText = L"Цена билета";
               this->priceColumn->MinimumWidth = 6;
               this->priceColumn->Name = L"priceColumn";
               this->priceColumn->Width = 125;
               // 
               // driverColumn
               // 
               this->driverColumn->HeaderText = L"Данные о водителе";
               this->driverColumn->MinimumWidth = 6;
               this->driverColumn->Name = L"driverColumn";
               this->driverColumn->Width = 150;
               // 
               // btnBuyTicket
               // 
               this->btnBuyTicket->BackColor = System::Drawing::Color::LightGreen;
               this->btnBuyTicket->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold));
               this->btnBuyTicket->Location = System::Drawing::Point(1062, 500);
               this->btnBuyTicket->Name = L"btnBuyTicket";
               this->btnBuyTicket->Size = System::Drawing::Size(226, 40);
               this->btnBuyTicket->TabIndex = 2;
               this->btnBuyTicket->Text = L"Купить билет";
               this->btnBuyTicket->UseVisualStyleBackColor = false;
               this->btnBuyTicket->Click += gcnew System::EventHandler(this, &TimingForm::BuyTicket_Click);
               // 
               // TimingForm
               // 
               this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
               this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
               this->BackColor = System::Drawing::SystemColors::InactiveCaption;
               this->ClientSize = System::Drawing::Size(1300, 550);
               this->Controls->Add(this->btnBuyTicket);
               this->Controls->Add(this->tripsDataGridView);
               this->Controls->Add(this->menuStrip);
               this->MainMenuStrip = this->menuStrip;
               this->Name = L"TimingForm";
               this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
               this->Text = L"Расписание поездок";
               this->menuStrip->ResumeLayout(false);
               this->menuStrip->PerformLayout();
               (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tripsDataGridView))->EndInit();
               this->ResumeLayout(false);
               this->PerformLayout();

           }
#pragma endregion

    public:
        void UpdateDataGridView();

    private:
        System::Void AddTrip_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void DeleteTrip_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void EditTrip_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void Search_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void Back_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void BuyTicket_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void tripsDataGridView_CellContentClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e);
    };
}