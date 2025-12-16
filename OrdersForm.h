#pragma once

#include "Order.hpp"

namespace InfSystBusStation {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::Collections::Generic;

    public ref class OrderForm : public System::Windows::Forms::Form {
    public:
        // Конструктор принимает Order
        OrderForm(Order^ order) {
            InitializeComponent();
            currentOrder = order;
            InitializeFormData();
            LoadTickets();
        }

    protected:
        ~OrderForm() {
            if (components) delete components;
        }

    private:
        Order^ currentOrder;
        System::ComponentModel::Container^ components;

        // Элементы формы
        System::Windows::Forms::GroupBox^ gbOrderInfo;
        System::Windows::Forms::Label^ lblOrderId;
        System::Windows::Forms::Label^ lblOrderDate;
        System::Windows::Forms::Label^ lblOrderStatus;
        System::Windows::Forms::Label^ lblPassengerName;
        System::Windows::Forms::Label^ lblTotalPrice;

        System::Windows::Forms::GroupBox^ gbTickets;
        System::Windows::Forms::DataGridView^ dgvTickets;
        System::Windows::Forms::DataGridViewCheckBoxColumn^ colSelect;
        System::Windows::Forms::DataGridViewTextBoxColumn^ colTicketNo;
        System::Windows::Forms::DataGridViewTextBoxColumn^ colPlace;
        System::Windows::Forms::DataGridViewTextBoxColumn^ colType;
        System::Windows::Forms::DataGridViewTextBoxColumn^ colRoute;
        System::Windows::Forms::DataGridViewTextBoxColumn^ colDate;
        System::Windows::Forms::DataGridViewTextBoxColumn^ colPrice;
        System::Windows::Forms::DataGridViewTextBoxColumn^ colStatus;

        System::Windows::Forms::Button^ btnPaySelected;
        System::Windows::Forms::Button^ btnRemoveSelected;
        System::Windows::Forms::Button^ btnSelectAll;
        System::Windows::Forms::Button^ btnDeselectAll;
        System::Windows::Forms::Button^ btnBack;
        System::Windows::Forms::Label^ lblStatistics;
        System::Windows::Forms::Label^ lblSelectedCount;

    private:
#pragma region Windows Form Designer generated code
        void InitializeComponent(void) {
            System::ComponentModel::ComponentResourceManager^ resources =
                (gcnew System::ComponentModel::ComponentResourceManager(OrderForm::typeid));
            this->gbOrderInfo = (gcnew System::Windows::Forms::GroupBox());
            this->lblOrderId = (gcnew System::Windows::Forms::Label());
            this->lblOrderDate = (gcnew System::Windows::Forms::Label());
            this->lblOrderStatus = (gcnew System::Windows::Forms::Label());
            this->lblPassengerName = (gcnew System::Windows::Forms::Label());
            this->lblTotalPrice = (gcnew System::Windows::Forms::Label());
            this->gbTickets = (gcnew System::Windows::Forms::GroupBox());
            this->dgvTickets = (gcnew System::Windows::Forms::DataGridView());
            this->colSelect = (gcnew System::Windows::Forms::DataGridViewCheckBoxColumn());
            this->colTicketNo = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->colPlace = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->colType = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->colRoute = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->colDate = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->colPrice = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->colStatus = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->btnPaySelected = (gcnew System::Windows::Forms::Button());
            this->btnRemoveSelected = (gcnew System::Windows::Forms::Button());
            this->btnSelectAll = (gcnew System::Windows::Forms::Button());
            this->btnDeselectAll = (gcnew System::Windows::Forms::Button());
            this->btnBack = (gcnew System::Windows::Forms::Button());
            this->lblStatistics = (gcnew System::Windows::Forms::Label());
            this->lblSelectedCount = (gcnew System::Windows::Forms::Label());
            this->gbOrderInfo->SuspendLayout();
            this->gbTickets->SuspendLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvTickets))->BeginInit();
            this->SuspendLayout();

            // gbOrderInfo
            this->gbOrderInfo->BackColor = System::Drawing::Color::AliceBlue;
            this->gbOrderInfo->Controls->Add(this->lblOrderId);
            this->gbOrderInfo->Controls->Add(this->lblOrderDate);
            this->gbOrderInfo->Controls->Add(this->lblOrderStatus);
            this->gbOrderInfo->Controls->Add(this->lblPassengerName);
            this->gbOrderInfo->Controls->Add(this->lblTotalPrice);
            this->gbOrderInfo->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9,
                System::Drawing::FontStyle::Bold));
            this->gbOrderInfo->Location = System::Drawing::Point(12, 12);
            this->gbOrderInfo->Name = L"gbOrderInfo";
            this->gbOrderInfo->Size = System::Drawing::Size(860, 100);
            this->gbOrderInfo->TabIndex = 0;
            this->gbOrderInfo->TabStop = false;
            this->gbOrderInfo->Text = L"Информация о заказе";

            // lblOrderId
            this->lblOrderId->AutoSize = true;
            this->lblOrderId->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9));
            this->lblOrderId->Location = System::Drawing::Point(10, 25);
            this->lblOrderId->Name = L"lblOrderId";
            this->lblOrderId->Size = System::Drawing::Size(81, 18);
            this->lblOrderId->TabIndex = 0;
            this->lblOrderId->Text = L"Заказ №:";

            // lblOrderDate
            this->lblOrderDate->AutoSize = true;
            this->lblOrderDate->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9));
            this->lblOrderDate->Location = System::Drawing::Point(10, 50);
            this->lblOrderDate->Name = L"lblOrderDate";
            this->lblOrderDate->Size = System::Drawing::Size(46, 18);
            this->lblOrderDate->TabIndex = 1;
            this->lblOrderDate->Text = L"Дата:";

            // lblOrderStatus
            this->lblOrderStatus->AutoSize = true;
            this->lblOrderStatus->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9));
            this->lblOrderStatus->Location = System::Drawing::Point(10, 75);
            this->lblOrderStatus->Name = L"lblOrderStatus";
            this->lblOrderStatus->Size = System::Drawing::Size(57, 18);
            this->lblOrderStatus->TabIndex = 2;
            this->lblOrderStatus->Text = L"Статус:";

            // lblPassengerName
            this->lblPassengerName->AutoSize = true;
            this->lblPassengerName->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9));
            this->lblPassengerName->Location = System::Drawing::Point(250, 25);
            this->lblPassengerName->Name = L"lblPassengerName";
            this->lblPassengerName->Size = System::Drawing::Size(79, 18);
            this->lblPassengerName->TabIndex = 3;
            this->lblPassengerName->Text = L"Пассажир:";

            // lblTotalPrice
            this->lblTotalPrice->AutoSize = true;
            this->lblTotalPrice->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10,
                System::Drawing::FontStyle::Bold));
            this->lblTotalPrice->ForeColor = System::Drawing::Color::Green;
            this->lblTotalPrice->Location = System::Drawing::Point(600, 40);
            this->lblTotalPrice->Name = L"lblTotalPrice";
            this->lblTotalPrice->Size = System::Drawing::Size(60, 20);
            this->lblTotalPrice->TabIndex = 4;
            this->lblTotalPrice->Text = L"Итого:";

            // gbTickets
            this->gbTickets->BackColor = System::Drawing::Color::Honeydew;
            this->gbTickets->Controls->Add(this->dgvTickets);
            this->gbTickets->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9,
                System::Drawing::FontStyle::Bold));
            this->gbTickets->Location = System::Drawing::Point(12, 118);
            this->gbTickets->Name = L"gbTickets";
            this->gbTickets->Size = System::Drawing::Size(860, 300);
            this->gbTickets->TabIndex = 1;
            this->gbTickets->TabStop = false;
            this->gbTickets->Text = L"Билеты в заказе";

            // dgvTickets
            this->dgvTickets->AllowUserToAddRows = false;
            this->dgvTickets->AllowUserToDeleteRows = false;
            this->dgvTickets->ColumnHeadersHeightSizeMode =
                System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
            this->dgvTickets->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(8) {
                this->colSelect, this->colTicketNo, this->colPlace, this->colType,
                    this->colRoute, this->colDate, this->colPrice, this->colStatus
            });
            this->dgvTickets->Location = System::Drawing::Point(10, 25);
            this->dgvTickets->Name = L"dgvTickets";
            this->dgvTickets->RowHeadersWidth = 51;
            this->dgvTickets->RowTemplate->Height = 24;
            this->dgvTickets->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
            this->dgvTickets->Size = System::Drawing::Size(840, 265);
            this->dgvTickets->TabIndex = 0;
            this->dgvTickets->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(
                this, &OrderForm::dgvTickets_CellContentClick);

            // colSelect
            this->colSelect->HeaderText = L"Выбрать";
            this->colSelect->MinimumWidth = 6;
            this->colSelect->Name = L"colSelect";
            this->colSelect->Width = 70;

            // colTicketNo
            this->colTicketNo->HeaderText = L"№";
            this->colTicketNo->MinimumWidth = 6;
            this->colTicketNo->Name = L"colTicketNo";
            this->colTicketNo->ReadOnly = true;
            this->colTicketNo->Width = 50;

            // colPlace
            this->colPlace->HeaderText = L"Место";
            this->colPlace->MinimumWidth = 6;
            this->colPlace->Name = L"colPlace";
            this->colPlace->ReadOnly = true;
            this->colPlace->Width = 70;

            // colType
            this->colType->HeaderText = L"Тип билета";
            this->colType->MinimumWidth = 6;
            this->colType->Name = L"colType";
            this->colType->ReadOnly = true;
            this->colType->Width = 100;

            // colRoute
            this->colRoute->HeaderText = L"Маршрут";
            this->colRoute->MinimumWidth = 6;
            this->colRoute->Name = L"colRoute";
            this->colRoute->ReadOnly = true;
            this->colRoute->Width = 200;

            // colDate
            this->colDate->HeaderText = L"Дата поездки";
            this->colDate->MinimumWidth = 6;
            this->colDate->Name = L"colDate";
            this->colDate->ReadOnly = true;
            this->colDate->Width = 120;

            // colPrice
            this->colPrice->HeaderText = L"Цена";
            this->colPrice->MinimumWidth = 6;
            this->colPrice->Name = L"colPrice";
            this->colPrice->ReadOnly = true;
            this->colPrice->Width = 80;

            // colStatus
            this->colStatus->HeaderText = L"Статус";
            this->colStatus->MinimumWidth = 6;
            this->colStatus->Name = L"colStatus";
            this->colStatus->ReadOnly = true;
            this->colStatus->Width = 90;

            // btnPaySelected
            this->btnPaySelected->BackColor = System::Drawing::Color::LightGreen;
            this->btnPaySelected->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10,
                System::Drawing::FontStyle::Bold));
            this->btnPaySelected->Location = System::Drawing::Point(12, 424);
            this->btnPaySelected->Name = L"btnPaySelected";
            this->btnPaySelected->Size = System::Drawing::Size(200, 40);
            this->btnPaySelected->TabIndex = 2;
            this->btnPaySelected->Text = L"Оплатить выбранные";
            this->btnPaySelected->UseVisualStyleBackColor = false;
            this->btnPaySelected->Click += gcnew System::EventHandler(this, &OrderForm::btnPaySelected_Click);

            // btnRemoveSelected
            this->btnRemoveSelected->BackColor = System::Drawing::Color::LightCoral;
            this->btnRemoveSelected->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
            this->btnRemoveSelected->Location = System::Drawing::Point(222, 424);
            this->btnRemoveSelected->Name = L"btnRemoveSelected";
            this->btnRemoveSelected->Size = System::Drawing::Size(200, 40);
            this->btnRemoveSelected->TabIndex = 3;
            this->btnRemoveSelected->Text = L"Удалить выбранные";
            this->btnRemoveSelected->UseVisualStyleBackColor = false;
            this->btnRemoveSelected->Click += gcnew System::EventHandler(this, &OrderForm::btnRemoveSelected_Click);

            // btnSelectAll
            this->btnSelectAll->BackColor = System::Drawing::Color::LightBlue;
            this->btnSelectAll->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9));
            this->btnSelectAll->Location = System::Drawing::Point(432, 424);
            this->btnSelectAll->Name = L"btnSelectAll";
            this->btnSelectAll->Size = System::Drawing::Size(100, 40);
            this->btnSelectAll->TabIndex = 4;
            this->btnSelectAll->Text = L"Выбрать все";
            this->btnSelectAll->UseVisualStyleBackColor = false;
            this->btnSelectAll->Click += gcnew System::EventHandler(this, &OrderForm::btnSelectAll_Click);

            // btnDeselectAll
            this->btnDeselectAll->BackColor = System::Drawing::Color::LightGray;
            this->btnDeselectAll->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9));
            this->btnDeselectAll->Location = System::Drawing::Point(542, 424);
            this->btnDeselectAll->Name = L"btnDeselectAll";
            this->btnDeselectAll->Size = System::Drawing::Size(100, 40);
            this->btnDeselectAll->TabIndex = 5;
            this->btnDeselectAll->Text = L"Снять все";
            this->btnDeselectAll->UseVisualStyleBackColor = false;
            this->btnDeselectAll->Click += gcnew System::EventHandler(this, &OrderForm::btnDeselectAll_Click);

            // btnBack
            this->btnBack->BackColor = System::Drawing::Color::LightGray;
            this->btnBack->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
            this->btnBack->Location = System::Drawing::Point(672, 424);
            this->btnBack->Name = L"btnBack";
            this->btnBack->Size = System::Drawing::Size(200, 40);
            this->btnBack->TabIndex = 6;
            this->btnBack->Text = L"Назад";
            this->btnBack->UseVisualStyleBackColor = false;
            this->btnBack->Click += gcnew System::EventHandler(this, &OrderForm::btnBack_Click);

            // lblStatistics
            this->lblStatistics->AutoSize = true;
            this->lblStatistics->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9));
            this->lblStatistics->Location = System::Drawing::Point(12, 480);
            this->lblStatistics->Name = L"lblStatistics";
            this->lblStatistics->Size = System::Drawing::Size(86, 18);
            this->lblStatistics->TabIndex = 7;
            this->lblStatistics->Text = L"Статистика:";

            // lblSelectedCount
            this->lblSelectedCount->AutoSize = true;
            this->lblSelectedCount->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9));
            this->lblSelectedCount->Location = System::Drawing::Point(12, 510);
            this->lblSelectedCount->Name = L"lblSelectedCount";
            this->lblSelectedCount->Size = System::Drawing::Size(136, 18);
            this->lblSelectedCount->TabIndex = 8;
            this->lblSelectedCount->Text = L"Выбрано билетов: 0";

            // OrderForm
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->BackColor = System::Drawing::SystemColors::Control;
            this->ClientSize = System::Drawing::Size(884, 541);
            this->Controls->Add(this->lblSelectedCount);
            this->Controls->Add(this->lblStatistics);
            this->Controls->Add(this->btnBack);
            this->Controls->Add(this->btnDeselectAll);
            this->Controls->Add(this->btnSelectAll);
            this->Controls->Add(this->btnRemoveSelected);
            this->Controls->Add(this->btnPaySelected);
            this->Controls->Add(this->gbTickets);
            this->Controls->Add(this->gbOrderInfo);
            this->MaximizeBox = false;
            this->MinimizeBox = false;
            this->Name = L"OrderForm";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->Text = L"Мой заказ";

            this->gbOrderInfo->ResumeLayout(false);
            this->gbOrderInfo->PerformLayout();
            this->gbTickets->ResumeLayout(false);
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvTickets))->EndInit();
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion

    private:
        void InitializeFormData();
        void LoadTickets();
        void UpdateStatistics();
        void UpdateSelectedCount();
        void UpdateButtonsState();

        // Обработчики событий
        System::Void btnPaySelected_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void btnRemoveSelected_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void btnSelectAll_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void btnDeselectAll_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void btnBack_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void dgvTickets_CellContentClick(System::Object^ sender,
            System::Windows::Forms::DataGridViewCellEventArgs^ e);
    };
}