#include "DriversListForm.h"

using namespace InfSystBusStation;
using namespace System::Windows::Forms; 

// Обновление DataGridView
void DriversListForm::UpdateDataGridView() {
    driversDataGridView->Rows->Clear();

    if (driverList == nullptr) {
        MessageBox::Show("driverList is null!", "Debug");
        return;
    }

    Console::WriteLine("=== НАЧАЛО ОТЛАДКИ ДРАЙВЕРОВ ===");
    Console::WriteLine("Всего драйверов: {0}", driverList->Count);

    int rowNumber = 1;
    for each (Driver ^ driver in driverList->AllDrivers) {
        Console::WriteLine("--- Драйвер #{0}: {1} ---", rowNumber, driver->GetFullName());

        // 1. Проверка самого объекта
        Console::WriteLine("  Объект Driver: {0}", driver != nullptr ? "VALID" : "NULL");

        // 2. Проверка типа
        Console::WriteLine("  Тип: {0}", driver->GetType()->FullName);

        // 3. Проверка паспортных данных через разные методы
        try {
            Workers^ worker = dynamic_cast<Workers^>(driver);
            if (worker != nullptr) {
                Console::WriteLine("  Cast to Workers: OK");
                array<System::Reflection::MethodInfo^>^ methods = worker->GetType()->GetMethods();
                bool hasPassportSeries = false;
                bool hasPassportNumber = false;

                for each (System::Reflection::MethodInfo ^ method in methods) {
                    if (method->Name->Contains("Passport")) {
                        Console::WriteLine("    Метод: {0}", method->Name);
                        if (method->Name->Contains("Series")) hasPassportSeries = true;
                        if (method->Name->Contains("Number")) hasPassportNumber = true;
                    }
                }

                Console::WriteLine("    Has PassportSeries method: {0}", hasPassportSeries);
                Console::WriteLine("    Has PassportNumber method: {0}", hasPassportNumber);

                // Пробуем вызвать
                if (hasPassportSeries) {
                    Object^ result = worker->GetType()->GetMethod("GetPassportSeries")->Invoke(worker, nullptr);
                    Console::WriteLine("    GetPassportSeries() result: '{0}'", result);
                }
            }
        }
        catch (Exception^ ex) {
            Console::WriteLine("  Ошибка при проверке Workers: {0}", ex->Message);
        }

        // 4. Прямой вызов (если добавили в Driver)
        try {
            String^ series = driver->GetPassportSeries();
            String^ number = driver->GetPassportNumber();
            Console::WriteLine("  Direct call: Series='{0}', Number='{1}'",
                series != nullptr ? series : "NULL",
                number != nullptr ? number : "NULL");
        }
        catch (Exception^ ex) {
            Console::WriteLine("  Ошибка прямого вызова: {0}", ex->Message);
        }

        // 5. Формируем данные для таблицы
        String^ passportData = "NO DATA";
        try {
            String^ series = driver->GetPassportSeries();
            String^ number = driver->GetPassportNumber();
            if (!String::IsNullOrEmpty(series) && !String::IsNullOrEmpty(number)) {
                passportData = series + " " + number;
            }
            else if (!String::IsNullOrEmpty(series)) {
                passportData = series;
            }
            else if (!String::IsNullOrEmpty(number)) {
                passportData = number;
            }
        }
        catch (...) {
            passportData = "ERROR";
        }

        Console::WriteLine("  Для таблицы: '{0}'", passportData);

        // Добавляем строку в таблицу
        driversDataGridView->Rows->Add(
            rowNumber++,
            driver->GetFullName(),
            driver->GetGender(),
            driver->GetLicense(),
            passportData,
            driver->GetSalary().ToString("N0") + " руб.",
            driver->IsAvailable() ? "Доступен" : "Занят"
        );
    }

    Console::WriteLine("=== КОНЕЦ ОТЛАДКИ ===");
    driversCountLabel->Text = String::Format("Всего водителей: {0}", driverList->Count);
}

System::Void DriversListForm::AddDriver_Click(System::Object^ sender, System::EventArgs^ e) {
    AddDriverForm^ addForm = gcnew AddDriverForm();
    addForm->SetDriverList(driverList);
    if (addForm->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
        // Обновляем DataGridView
        UpdateDataGridView();
    }

    delete addForm;
}

System::Void DriversListForm::DeleteDriver_Click(System::Object^ sender, System::EventArgs^ e) {
    DeleteDriverForm^ deleteForm = gcnew DeleteDriverForm(driverList);
    if (deleteForm->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
        // Обновляем DataGridView
        UpdateDataGridView();
    }

    delete deleteForm;
}

System::Void DriversListForm::DeleteContextMenu_Click(System::Object^ sender, System::EventArgs^ e) {
    DeleteDriver_Click(sender, e);
}

System::Void DriversListForm::driversDataGridView_CellDoubleClick(System::Object^ sender, DataGridViewCellEventArgs^ e) {
    if (e->RowIndex >= 0 && e->RowIndex < driversDataGridView->Rows->Count) {
        driversDataGridView->Rows[e->RowIndex]->Selected = true;
        DeleteDriver_Click(sender, e);
    }
}

System::Void DriversListForm::Refresh_Click(System::Object^ sender, System::EventArgs^ e) {
    UpdateDataGridView();
}

System::Void DriversListForm::Back_Click(System::Object^ sender, System::EventArgs^ e) {
    this->Close();
}