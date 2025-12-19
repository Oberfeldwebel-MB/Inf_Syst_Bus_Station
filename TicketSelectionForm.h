#pragma once

#include "Trip.hpp"
#include "Order.hpp"
#include "User.hpp"

namespace InfSystBusStation {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::Collections::Generic;

    public ref class TicketSelectionForm : public System::Windows::Forms::Form {
    public:
        TicketSelectionForm(Trip^ trip, Order^ order, User^ user) : selectedTrip(trip), currentOrder(order), currentUser(user), ticketAdded(false) {

            InitializeComponent();
            InitializeFormData();
        };

        property bool TicketAdded {
            bool get() { return ticketAdded; }
        }

    protected:
        ~TicketSelectionForm() {
            if (components) delete components;
        }

    private:
        Trip^ selectedTrip;
        Order^ currentOrder;
        bool ticketAdded = false;
        User^ currentUser;
        System::ComponentModel::Container^ components;

        // Элементы формы
        System::Windows::Forms::GroupBox^ gbTripInfo;
        System::Windows::Forms::Label^ lblTripInfo;
        System::Windows::Forms::GroupBox^ gbSeatSelection;
        System::Windows::Forms::Label^ lblSelectSeat;
        System::Windows::Forms::ComboBox^ cmbSeats;
        System::Windows::Forms::Label^ lblSelectedSeat;
        System::Windows::Forms::Button^ btnAddToOrder;
        System::Windows::Forms::Button^ btnCancel;
        System::Windows::Forms::Label^ lblPriceInfo;

    private:
#pragma region Windows Form Designer generated code
        void InitializeComponent(void) {
            this->gbTripInfo = (gcnew System::Windows::Forms::GroupBox());
            this->lblTripInfo = (gcnew System::Windows::Forms::Label());
            this->gbSeatSelection = (gcnew System::Windows::Forms::GroupBox());
            this->lblSelectedSeat = (gcnew System::Windows::Forms::Label());
            this->cmbSeats = (gcnew System::Windows::Forms::ComboBox());
            this->lblSelectSeat = (gcnew System::Windows::Forms::Label());
            this->btnAddToOrder = (gcnew System::Windows::Forms::Button());
            this->btnCancel = (gcnew System::Windows::Forms::Button());
            this->lblPriceInfo = (gcnew System::Windows::Forms::Label());
            this->gbTripInfo->SuspendLayout();
            this->gbSeatSelection->SuspendLayout();
            this->SuspendLayout();
            // 
            // gbTripInfo
            // 
            this->gbTripInfo->BackColor = System::Drawing::Color::AliceBlue;
            this->gbTripInfo->Controls->Add(this->lblTripInfo);
            this->gbTripInfo->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->gbTripInfo->Location = System::Drawing::Point(12, 12);
            this->gbTripInfo->Name = L"gbTripInfo";
            this->gbTripInfo->Size = System::Drawing::Size(560, 100);
            this->gbTripInfo->TabIndex = 0;
            this->gbTripInfo->TabStop = false;
            this->gbTripInfo->Text = L"Информация о поездке";
            // 
            // lblTripInfo
            // 
            this->lblTripInfo->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->lblTripInfo->Location = System::Drawing::Point(6, 26);
            this->lblTripInfo->Name = L"lblTripInfo";
            this->lblTripInfo->Size = System::Drawing::Size(548, 70);
            this->lblTripInfo->TabIndex = 0;
            this->lblTripInfo->Text = L"Информация...";
            // 
            // gbSeatSelection
            // 
            this->gbSeatSelection->BackColor = System::Drawing::Color::Honeydew;
            this->gbSeatSelection->Controls->Add(this->lblSelectedSeat);
            this->gbSeatSelection->Controls->Add(this->cmbSeats);
            this->gbSeatSelection->Controls->Add(this->lblSelectSeat);
            this->gbSeatSelection->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->gbSeatSelection->Location = System::Drawing::Point(12, 118);
            this->gbSeatSelection->Name = L"gbSeatSelection";
            this->gbSeatSelection->Size = System::Drawing::Size(560, 100);
            this->gbSeatSelection->TabIndex = 1;
            this->gbSeatSelection->TabStop = false;
            this->gbSeatSelection->Text = L"Выбор места";
            // 
            // lblSelectedSeat
            // 
            this->lblSelectedSeat->AutoSize = true;
            this->lblSelectedSeat->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->lblSelectedSeat->Location = System::Drawing::Point(300, 30);
            this->lblSelectedSeat->Name = L"lblSelectedSeat";
            this->lblSelectedSeat->Size = System::Drawing::Size(138, 18);
            this->lblSelectedSeat->TabIndex = 2;
            this->lblSelectedSeat->Text = L"Место не выбрано";
            // 
            // cmbSeats
            // 
            this->cmbSeats->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->cmbSeats->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->cmbSeats->FormattingEnabled = true;
            this->cmbSeats->Location = System::Drawing::Point(20, 50);
            this->cmbSeats->Name = L"cmbSeats";
            this->cmbSeats->Size = System::Drawing::Size(150, 28);
            this->cmbSeats->TabIndex = 1;
            this->cmbSeats->SelectedIndexChanged += gcnew System::EventHandler(this, &TicketSelectionForm::cmbSeats_SelectedIndexChanged);
            // 
            // lblSelectSeat
            // 
            this->lblSelectSeat->AutoSize = true;
            this->lblSelectSeat->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->lblSelectSeat->Location = System::Drawing::Point(17, 30);
            this->lblSelectSeat->Name = L"lblSelectSeat";
            this->lblSelectSeat->Size = System::Drawing::Size(128, 18);
            this->lblSelectSeat->TabIndex = 0;
            this->lblSelectSeat->Text = L"Выберите место:";
            // 
            // btnAddToOrder
            // 
            this->btnAddToOrder->BackColor = System::Drawing::Color::LightGreen;
            this->btnAddToOrder->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->btnAddToOrder->Location = System::Drawing::Point(336, 230);
            this->btnAddToOrder->Name = L"btnAddToOrder";
            this->btnAddToOrder->Size = System::Drawing::Size(236, 40);
            this->btnAddToOrder->TabIndex = 2;
            this->btnAddToOrder->Text = L"Добавить в заказ";
            this->btnAddToOrder->UseVisualStyleBackColor = false;
            this->btnAddToOrder->Click += gcnew System::EventHandler(this, &TicketSelectionForm::btnAddToOrder_Click);
            // 
            // btnCancel
            // 
            this->btnCancel->BackColor = System::Drawing::Color::LightGray;
            this->btnCancel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->btnCancel->Location = System::Drawing::Point(12, 286);
            this->btnCancel->Name = L"btnCancel";
            this->btnCancel->Size = System::Drawing::Size(236, 40);
            this->btnCancel->TabIndex = 3;
            this->btnCancel->Text = L"Отмена";
            this->btnCancel->UseVisualStyleBackColor = false;
            this->btnCancel->Click += gcnew System::EventHandler(this, &TicketSelectionForm::btnCancel_Click);
            // 
            // lblPriceInfo
            // 
            this->lblPriceInfo->AutoSize = true;
            this->lblPriceInfo->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->lblPriceInfo->ForeColor = System::Drawing::Color::DarkGreen;
            this->lblPriceInfo->Location = System::Drawing::Point(17, 240);
            this->lblPriceInfo->Name = L"lblPriceInfo";
            this->lblPriceInfo->Size = System::Drawing::Size(120, 20);
            this->lblPriceInfo->TabIndex = 4;
            this->lblPriceInfo->Text = L"Цена: 0 руб.";
            // 
            // TicketSelectionForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->BackColor = System::Drawing::SystemColors::Control;
            this->ClientSize = System::Drawing::Size(584, 338);
            this->Controls->Add(this->lblPriceInfo);
            this->Controls->Add(this->btnCancel);
            this->Controls->Add(this->btnAddToOrder);
            this->Controls->Add(this->gbSeatSelection);
            this->Controls->Add(this->gbTripInfo);
            this->MaximizeBox = false;
            this->MinimizeBox = false;
            this->Name = L"TicketSelectionForm";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->Text = L"Выбор билета";
            this->gbTripInfo->ResumeLayout(false);
            this->gbSeatSelection->ResumeLayout(false);
            this->gbSeatSelection->PerformLayout();
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion

    private:
        System::Void InitializeFormData();
        System::Void LoadAvailableSeats();
        System::Void UpdatePriceInfo();
        System::Void UpdateButtonsState();

        // === ОБРАБОТЧИКИ СОБЫТИЙ ===
        System::Void cmbSeats_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
        System::Void btnAddToOrder_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void btnCancel_Click(System::Object^ sender, System::EventArgs^ e);
    };
}