
#include "AddDriverForm.h"

using namespace InfSystBusStation;

System::Void AddDriverForm::AddButtonDriver_Click(System::Object^ sender, System::EventArgs^ e) {
    try {
        // 1. Проверка инициализации списка
        if (driverList == nullptr) {
            MessageBox::Show("Ошибка: система хранения данных не инициализирована!",
                "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        // === 2. Получение данных из формы ===

        // ФИО
        String^ fioStr = FIO_add->Text->Trim();

        // Пол
        String^ genderStr = "";
        if (pol_add->GetItemChecked(0)) genderStr = "М";
        else if (pol_add->GetItemChecked(1)) genderStr = "Ж";

        // Паспортные данные (объединяем серию и номер)
        String^ passportStr = data_add->Text->Trim();
        if (!String::IsNullOrEmpty(passportStr)) {
            passportStr = passportStr->Replace(" ", "")->Replace("-", "")->Replace("/", "")->Replace(".", "");
        }

        // Номер водительского удостоверения
        String^ licenseStr = maskedTextBox1->Text->Trim();

        // Зарплата
        int salary = Decimal::ToInt32(ratingNumericUpDown->Value);

        // === 3. ЕДИНАЯ ВАЛИДАЦИЯ ВСЕХ ПОЛЕЙ ===
        String^ validationError;

        if (!DriverValidator::ValidateAllFieldsStatic(fioStr, salary, genderStr,
            licenseStr, passportStr, validationError)) {
            MessageBox::Show("Ошибка валидации: " + validationError, "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);

            // Устанавливаем фокус на проблемное поле
            if (validationError->Contains("ФИО")) {
                FIO_add->Focus();
                FIO_add->SelectAll();
            }
            else if (validationError->Contains("зарплат")) {
                ratingNumericUpDown->Focus();
                ratingNumericUpDown->Select(0, ratingNumericUpDown->Text->Length);
            }
            else if (validationError->Contains("пол")) {
                // Ничего не делаем, CheckedListBox не поддерживает фокус напрямую
            }
            else if (validationError->Contains("прав")) {
                maskedTextBox1->Focus();
                maskedTextBox1->SelectAll();
            }
            else if (validationError->Contains("паспорт")) {
                data_add->Focus();
                data_add->SelectAll();
            }

            return;
        }

        // === 4. Проверка уникальности ФИО ===
        Driver^ existingDriver = driverList->FindDriverByName(fioStr);
        if (existingDriver != nullptr) {
            MessageBox::Show("Водитель с таким ФИО уже существует в системе!",
                "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            FIO_add->Focus();
            FIO_add->SelectAll();
            return;
        }

        // === 5. Разделяем паспорт на серию и номер ===
        String^ passportSeries = "";
        String^ passportNumber = "";
        if (!String::IsNullOrEmpty(passportStr) && passportStr->Length == 10) {
            passportSeries = passportStr->Substring(0, 4);
            passportNumber = passportStr->Substring(4);
        }

        // === 6. Создание объекта Driver ===
        Driver^ newDriver = gcnew Driver(fioStr, genderStr, passportSeries,
            passportNumber, salary, licenseStr);

        // === 7. Проверка уникальности прав ===
        for each (Driver ^ driver in driverList->AllDrivers) {
            if (driver->GetLicense() == licenseStr) {
                MessageBox::Show("Водитель с таким номером прав уже существует!",
                    "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                maskedTextBox1->Focus();
                maskedTextBox1->SelectAll();
                return;
            }
        }

        // === 8. Добавление водителя в систему ===
        driverList->AddDriver(newDriver);
       
        MessageBox::Show(
            String::Format("Водитель успешно добавлен!\n\nФИО: {0}\nПол: {1}\nВУ: {2}\nЗарплата: {3:N0} руб.",
                fioStr, genderStr, licenseStr, salary),
            "Успех",
            MessageBoxButtons::OK,
            MessageBoxIcon::Information
        );

        // === 9. Очистка формы ===
        FIO_add->Clear();
        pol_add->SetItemChecked(0, false);
        pol_add->SetItemChecked(1, false);
        data_add->Clear();
        maskedTextBox1->Clear();
        ratingNumericUpDown->Value = 30000;
        FIO_add->Focus();


        DataAdded(this, EventArgs::Empty);

        
        this->DialogResult = Windows::Forms::DialogResult::OK;
    }

    catch (Exception^ ex) {
        MessageBox::Show("Ошибка: " + ex->Message, "Ошибка системы",
            MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}