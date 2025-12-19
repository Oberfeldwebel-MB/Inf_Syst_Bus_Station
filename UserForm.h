#pragma once

#include "User.hpp"           // Вместо Order.hpp
#include "TripList.hpp"
#include "BusList.hpp"
#include "DriversList.hpp"

namespace InfSystBusStation {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class UserForm : public System::Windows::Forms::Form {
    public:
        // Упрощенный конструктор - только User и списки данных
        UserForm(User^ user, TripList^ tripList, BusList^ busList, DriversList^ driverList) {
            InitializeComponent();
            this->currentUser = user;
            this->tripList = tripList;
            this->busList = busList;
            this->driverList = driverList;

            // Показываем имя пользователя
            lblWelcome->Text = "Добро пожаловать, " + currentUser->GetFullName() + "!";


            // Обновляем информацию о заказе
            UpdateOrderInfo();
        }

    protected:
        ~UserForm() {
            if (components) delete components;
        }

    private:
        User^ currentUser;          // Основной объект пользователя
        TripList^ tripList;         // Список рейсов
        BusList^ busList;           // Список автобусов
        DriversList^ driverList;    // Список водителей
        System::ComponentModel::Container^ components;

        // Элементы формы
        System::Windows::Forms::Label^ lblWelcome;
        System::Windows::Forms::Button^ btnSelectTrip;
        System::Windows::Forms::Button^ btnMyTickets;
        System::Windows::Forms::Button^ btnBack;
        System::Windows::Forms::Label^ lblOrderInfo;

    private:
#pragma region Windows Form Designer generated code
        void InitializeComponent(void) {
            System::ComponentModel::ComponentResourceManager^ resources =
                (gcnew System::ComponentModel::ComponentResourceManager(UserForm::typeid));
            this->lblWelcome = (gcnew System::Windows::Forms::Label());
            this->btnSelectTrip = (gcnew System::Windows::Forms::Button());
            this->btnMyTickets = (gcnew System::Windows::Forms::Button());
            this->btnBack = (gcnew System::Windows::Forms::Button());
            this->lblOrderInfo = (gcnew System::Windows::Forms::Label());
            this->SuspendLayout();

            // lblWelcome
            this->lblWelcome->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12,
                System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->lblWelcome->Location = System::Drawing::Point(12, 20);
            this->lblWelcome->Name = L"lblWelcome";
            this->lblWelcome->Size = System::Drawing::Size(460, 30);
            this->lblWelcome->TabIndex = 0;
            this->lblWelcome->Text = L"Добро пожаловать, Пользователь!";
            this->lblWelcome->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;

            // btnSelectTrip
            this->btnSelectTrip->BackColor = System::Drawing::Color::LightGreen;
            this->btnSelectTrip->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10,
                System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->btnSelectTrip->Location = System::Drawing::Point(50, 80);
            this->btnSelectTrip->Name = L"btnSelectTrip";
            this->btnSelectTrip->Size = System::Drawing::Size(180, 60);
            this->btnSelectTrip->TabIndex = 1;
            this->btnSelectTrip->Text = L"Выбрать поездку";
            this->btnSelectTrip->UseVisualStyleBackColor = false;
            this->btnSelectTrip->Click += gcnew System::EventHandler(this, &UserForm::btnSelectTrip_Click);

            // btnMyTickets
            this->btnMyTickets->BackColor = System::Drawing::Color::LightBlue;
            this->btnMyTickets->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10,
                System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->btnMyTickets->Location = System::Drawing::Point(250, 80);
            this->btnMyTickets->Name = L"btnMyTickets";
            this->btnMyTickets->Size = System::Drawing::Size(180, 60);
            this->btnMyTickets->TabIndex = 2;
            this->btnMyTickets->Text = L"Мои билеты";
            this->btnMyTickets->UseVisualStyleBackColor = false;
            this->btnMyTickets->Click += gcnew System::EventHandler(this, &UserForm::btnMyTickets_Click);

            // btnBack
            this->btnBack->BackColor = System::Drawing::Color::LightGray;
            this->btnBack->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9,
                System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->btnBack->Location = System::Drawing::Point(50, 200);
            this->btnBack->Name = L"btnBack";
            this->btnBack->Size = System::Drawing::Size(380, 40);
            this->btnBack->TabIndex = 3;
            this->btnBack->Text = L"Выйти из системы";
            this->btnBack->UseVisualStyleBackColor = false;
            this->btnBack->Click += gcnew System::EventHandler(this, &UserForm::btnBack_Click);

            // lblOrderInfo
            this->lblOrderInfo->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9,
                System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->lblOrderInfo->Location = System::Drawing::Point(50, 160);
            this->lblOrderInfo->Name = L"lblOrderInfo";
            this->lblOrderInfo->Size = System::Drawing::Size(380, 30);
            this->lblOrderInfo->TabIndex = 4;
            this->lblOrderInfo->Text = L"В вашем заказе: 0 билетов";
            this->lblOrderInfo->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;

            // UserForm
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->BackColor = System::Drawing::Color::LightCyan;
            this->ClientSize = System::Drawing::Size(484, 261);
            this->Controls->Add(this->lblOrderInfo);
            this->Controls->Add(this->btnBack);
            this->Controls->Add(this->btnMyTickets);
            this->Controls->Add(this->btnSelectTrip);
            this->Controls->Add(this->lblWelcome);
            this->Name = L"UserForm";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->Text = L"Пользовательский режим";
            this->ResumeLayout(false);
        }
#pragma endregion

    private:
        void UpdateOrderInfo();

        // Обработчики событий
        System::Void btnSelectTrip_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void btnMyTickets_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void btnBack_Click(System::Object^ sender, System::EventArgs^ e);
    };
}