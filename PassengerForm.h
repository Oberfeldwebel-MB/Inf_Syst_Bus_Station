#pragma once
#include "User.hpp"  // ¬ключаем наш управл€емый класс User

namespace InfSystBusStation {

    public ref class PassengerForm : public System::Windows::Forms::Form {
    public:
        PassengerForm(void) {
            InitializeComponent();
            passenger = nullptr;
        }

        // —войство дл€ получени€ созданного User
        property User^ CreatedUser {
            User^ get() { return user; }
        }

    protected:
        ~PassengerForm() {
            if (components) delete components;
        }

    private:
        User^ user;  // Ѕудет создавать User, а не Passenger
        System::ComponentModel::Container^ components;

    private:
        // Ёлементы формы (оставл€ем как есть)
        System::Windows::Forms::MaskedTextBox^ PassFioBox;
        System::Windows::Forms::CheckedListBox^ PolPassBox;
        System::Windows::Forms::MaskedTextBox^ PassportPassBox;
        System::Windows::Forms::TextBox^ EMAILBox;
        System::Windows::Forms::MaskedTextBox^ PhonePassBox;
        System::Windows::Forms::Label^ label1;
        System::Windows::Forms::Label^ label2;
        System::Windows::Forms::Label^ label3;
        System::Windows::Forms::Label^ label4;
        System::Windows::Forms::Label^ label5;
        System::Windows::Forms::Button^ SaveButton;
        System::Windows::Forms::Button^ BackButton;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            // ... существующий код инициализации ...
            // ќставл€ем как есть
        }
#pragma endregion

    private:
        // ќбработчики событий
        System::Void SaveButton_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void BackButton_Click(System::Object^ sender, System::EventArgs^ e);
    };
}