// AddDriverForm.cpp
#include "AddDriverForm.h"

using namespace InfSystBusStation;

System::Void AddDriverForm::AddButtonDriver_Click(System::Object^ sender, System::EventArgs^ e) {
    try {
        // === 1. Проверка инициализации списка ===
        if (driverList == nullptr) {
            MessageBox::Show("Ошибка: система хранения данных не инициализирована!",
                "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        // === 2. Получение данных из формы ===

        // ФИО
        String^ fioStr = FIO_add->Text->Trim();
        if (String::IsNullOrEmpty(fioStr)) {
            MessageBox::Show("Введите ФИО водителя!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            FIO_add->Focus();
            FIO_add->SelectAll();
            return;
        }

        // Пол
        String^ genderStr = "";
        if (pol_add->GetItemChecked(0)) {
            genderStr = "М";
        }
        else if (pol_add->GetItemChecked(1)) {
            genderStr = "Ж";
        }

        if (String::IsNullOrEmpty(genderStr)) {
            MessageBox::Show("Выберите пол водителя!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }

        // Паспортные данные
        String^ passportStr = data_add->Text->Trim();
        String^ passportSeries = "";
        String^ passportNumber = "";

        if (!String::IsNullOrEmpty(passportStr)) {
            // Убираем возможные пробелы и символы
            passportStr = passportStr->Replace(" ", "")->Replace("-", "")->Replace("/", "");

            if (passportStr->Length >= 4) {
                passportSeries = passportStr->Substring(0, 4);
                if (passportStr->Length >= 10) {
                    passportNumber = passportStr->Substring(4, 6);
                }
            }
        }

        // Номер водительского удостоверения
        String^ licenseStr = maskedTextBox1->Text->Trim();
        if (String::IsNullOrEmpty(licenseStr)) {
            MessageBox::Show("Введите номер водительского удостоверения!",
                "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            maskedTextBox1->Focus();
            maskedTextBox1->SelectAll();
            return;
        }

        // Зарплата
        int salary = System::Decimal::ToInt32(ratingNumericUpDown->Value);

        // === 3. ВАЛИДАЦИЯ ДАННЫХ ===

        // Валидация ФИО
        auto fioValidation = DriverValidator::ValidateFIO(fioStr);
        if (!fioValidation.isValid) {
            MessageBox::Show(fioValidation.errorMessage, "Ошибка валидации",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            FIO_add->Focus();
            FIO_add->SelectAll();
            return;
        }

        // Валидация пола
        auto genderValidation = DriverValidator::ValidateGender(genderStr);
        if (!genderValidation.isValid) {
            MessageBox::Show(genderValidation.errorMessage, "Ошибка валидации",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }

        // Валидация прав
        auto licenseValidation = DriverValidator::ValidateLicense(licenseStr);
        if (!licenseValidation.isValid) {
            MessageBox::Show(licenseValidation.errorMessage, "Ошибка валидации",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            maskedTextBox1->Focus();
            maskedTextBox1->SelectAll();
            return;
        }

        // Валидация зарплаты
        auto salaryValidation = DriverValidator::ValidateSalary(salary);
        if (!salaryValidation.isValid) {
            MessageBox::Show(salaryValidation.errorMessage, "Ошибка валидации",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            ratingNumericUpDown->Focus();
            ratingNumericUpDown->Select(0, ratingNumericUpDown->Text->Length);
            return;
        }

        // Валидация паспорта (если введен)
        if (!String::IsNullOrEmpty(passportSeries) || !String::IsNullOrEmpty(passportNumber)) {
            auto passportValidation = DriverValidator::ValidatePassport(passportSeries, passportNumber);
            if (!passportValidation.isValid) {
                MessageBox::Show(passportValidation.errorMessage, "Ошибка валидации паспорта",
                    MessageBoxButtons::OK, MessageBoxIcon::Warning);
                data_add->Focus();
                data_add->SelectAll();
                return;
            }
        }

        // === 4. Проверка существующего водителя ===
        Driver^ existingDriver = driverList->FindDriverByName(fioStr);
        if (existingDriver != nullptr) {
            MessageBox::Show("Водитель с таким ФИО уже существует в системе!",
                "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            FIO_add->Focus();
            FIO_add->SelectAll();
            return;
        }

        // === 5. Создание водителя ===
        Driver^ newDriver = gcnew Driver(fioStr, genderStr, passportSeries,
            passportNumber, salary, licenseStr);

        // Полная валидация перед добавлением
        auto fullValidation = DriverValidator::ValidateForAddition(newDriver, driverList);
        if (!fullValidation.isValid) {
            MessageBox::Show(fullValidation.errorMessage, "Ошибка валидации",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }

        // === 6. Добавление водителя в систему ===
        try {
            driverList->AddDriver(newDriver);

            // === 7. Сообщение об успехе ===
            MessageBox::Show(
                "Водитель успешно добавлен в систему!\n\n" +
                "ФИО: " + fioStr + "\n" +
                "Пол: " + genderStr + "\n" +
                "ВУ: " + licenseStr + "\n" +
                "Зарплата: " + salary.ToString("N0") + " руб.",
                "Успешно добавлено",
                MessageBoxButtons::OK,
                MessageBoxIcon::Information
            );

            // === 8. Очистка формы ===
            FIO_add->Clear();
            pol_add->SetItemChecked(0, false);
            pol_add->SetItemChecked(1, false);
            data_add->Clear();
            maskedTextBox1->Clear();
            ratingNumericUpDown->Value = 30000;

            // Фокус на первое поле
            FIO_add->Focus();

            // === 9. Генерация события ===
            DataAdded(this, EventArgs::Empty);

        }
        catch (Exception^ ex) {
            MessageBox::Show(
                "Ошибка при добавлении водителя: " + ex->Message,
                "Ошибка данных",
                MessageBoxButtons::OK,
                MessageBoxIcon::Error
            );
        }
    }
    catch (Exception^ ex) {
        MessageBox::Show(
            "Ошибка: " + ex->Message,
            "Ошибка системы",
            MessageBoxButtons::OK,
            MessageBoxIcon::Error
        );
    }
}