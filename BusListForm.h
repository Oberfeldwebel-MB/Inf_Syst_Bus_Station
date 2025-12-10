#pragma once

#include "BusList.hpp"
#include "AddBusForm.h"

namespace InfSystBusStation {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

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

        // Ёлементы формы
        MenuStrip^ menuStrip;
        ToolStripMenuItem^ addBusMenuItem;
        ToolStripMenuItem^ deleteBusMenuItem;
        ToolStripMenuItem^ backMenuItem;

        DataGridView^ busesDataGridView;
        DataGridViewTextBoxColumn^ numColumn;
        DataGridViewTextBoxColumn^ codeColumn;
        DataGridViewTextBoxColumn^ brandColumn;
        DataGridViewTextBoxColumn^ modelColumn;
        DataGridViewTextBoxColumn^ placesColumn;
        DataGridViewTextBoxColumn^ conditionColumn;
        DataGridViewTextBoxColumn^ statusColumn;

        Label^ busesCountLabel;
        Label^ availableLabel;
        Button^ btnRefresh;

#pragma region Windows Form Designer generated code
        void InitializeComponent() {
          
        }
#pragma endregion

    public:
        void UpdateDataGridView();

    private:
        System::Void AddBus_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void DeleteBus_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void Back_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void Refresh_Click(System::Object^ sender, System::EventArgs^ e);
    };
}