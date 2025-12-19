#include "PassengerForm.h"
#include "User.hpp"
#include "UserForm.h"
#include "DriverValidator.hpp"
#include "Order.hpp"

using namespace InfSystBusStation;
using namespace System;
using namespace System::Windows::Forms;

System::Void PassengerForm::SaveButton_Click(System::Object^ sender, System::EventArgs^ e) {
    try {
        // 1. Проверка обязательных полей
        if (String::IsNullOrWhiteSpace(PassFioBox->Text)) {
            MessageBox::Show("Введите ФИО!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            PassFioBox->Focus();
            return;
        }

        if (String::IsNullOrWhiteSpace(EMAILBox->Text)) {
            MessageBox::Show("Введите Email!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            EMAILBox->Focus();
            return;
        }

        if (String::IsNullOrWhiteSpace(PhonePassBox->Text) || PhonePassBox->Text->Contains("_")) {
            MessageBox::Show("Введите корректный номер телефона!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            PhonePassBox->Focus();
            return;
        }

        // 2. Получаем данные из формы
        String^ fioFormatted = PassFioBox->Text;
        String^ email = EMAILBox->Text;
        String^ phone = PhonePassBox->Text;

        // 3. Пол (приводим к формату "М" или "Ж")
        String^ gender = "М"; // По умолчанию
        if (PolPassBox->CheckedItems->Count > 0) {
            String^ selectedGender = safe_cast<String^>(PolPassBox->CheckedItems[0]);
            if (selectedGender == "Мужской") gender = "М";
            else if (selectedGender == "Женский") gender = "Ж";
        }

        // 4. Паспортные данные
        String^ passportSeries = "";
        String^ passportNumber = "";
        if (!String::IsNullOrWhiteSpace(PassportPassBox->Text)) {
            String^ passport = PassportPassBox->Text;
            if (passport->Contains("/")) {
                array<String^>^ parts = passport->Split('/');
                if (parts->Length == 2) {
                    passportSeries = parts[0];
                    passportNumber = parts[1];
                }
            }
        }

        // 5. Валидация с DriverValidator
        String^ errorMessage;

        if (!DriverValidator::ValidateFIOStatic(fioFormatted, errorMessage)) {
            MessageBox::Show("Ошибка в ФИО: " + errorMessage, "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            PassFioBox->Focus();
            return;
        }

        if (!DriverValidator::ValidateGenderStatic(gender, errorMessage)) {
            MessageBox::Show("Ошибка в поле 'Пол': " + errorMessage, "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            PolPassBox->Focus();
            return;
        }

        if (!String::IsNullOrEmpty(passportSeries) || !String::IsNullOrEmpty(passportNumber)) {
            if (!DriverValidator::ValidatePassportStatic(passportSeries, passportNumber, errorMessage)) {
                MessageBox::Show("Ошибка в паспортных данных: " + errorMessage, "Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Warning);
                PassportPassBox->Focus();
                return;
            }
        }

        // 6. Создаем User
        createdUser = User::CreateFromRegistrationForm(
            fioFormatted, gender, passportSeries, passportNumber, email, phone);

        if (!createdUser->ValidateUserData()) {
            MessageBox::Show("Ошибка валидации данных пользователя!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Error);
            createdUser = nullptr;
            return;
        }

        // 2. Создаем Order отдельно
        Order^ userOrder = gcnew Order();
        userOrder->PassengerName = createdUser->GetFullName();

        // 3. Связываем Order с User
        createdUser->CurrentOrder = userOrder;

        // 4. Открываем UserForm с User и Order
        UserForm^ userForm = gcnew UserForm(createdUser, tripList, busList, driverList);

        MessageBox::Show("Регистрация успешна!", "Успех",
            MessageBoxButtons::OK, MessageBoxIcon::Information);

        this->Hide();
        userForm->ShowDialog();
        this->Close();
    }
    catch (Exception^ ex) {
        MessageBox::Show("Ошибка: " + ex->Message, "Ошибка",
            MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}

System::Void PassengerForm::BackButton_Click(System::Object^ sender, System::EventArgs^ e) {
    this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
    this->Close();
}