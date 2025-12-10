#include "DriversListForm.h"

using namespace InfSystBusStation;
using namespace System::Windows::Forms;  // Добавляем эту строку

// Обновление DataGridView
void DriversListForm::UpdateDataGridView() {
    driversDataGridView->Rows->Clear();

    if (driverList == nullptr) return;

    int rowNumber = 1;
    for each (Driver ^ driver in driverList->AllDrivers) {
        // Формируем строку паспортных данных
        String^ passportData = "";
        if (!String::IsNullOrEmpty(driver->GetPassportSeries()) &&
            !String::IsNullOrEmpty(driver->GetPassportNumber())) {
            passportData = driver->GetPassportSeries() + " " + driver->GetPassportNumber();
        }

        // Добавляем строку в DataGridView
        driversDataGridView->Rows->Add(
            rowNumber++,
            driver->GetFullName(),
            driver->GetGender(),
            driver->GetLicense(),
            passportData,
            driver->GetSalary().ToString("N0") + " руб.",
            driver->GetAvailability() ? "Доступен" : "Занят"
        );
    }

    // Обновляем счетчик
    driversCountLabel->Text = String::Format("Всего водителей: {0}", driverList->Count);
}

System::Void DriversListForm::AddDriver_Click(System::Object^ sender, System::EventArgs^ e) {
    AddDriverForm^ addForm = gcnew AddDriverForm();
    addForm->SetDriverList(driverList);

    // Используем полное имя DialogResult::OK
    if (addForm->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
        // Обновляем DataGridView
        UpdateDataGridView();
    }

    delete addForm;
}

System::Void DriversListForm::DeleteDriver_Click(System::Object^ sender, System::EventArgs^ e) {
    // Открываем красивую форму удаления
    DeleteDriverForm^ deleteForm = gcnew DeleteDriverForm(driverList);

    // Используем полное имя DialogResult::OK
    if (deleteForm->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
        // Обновляем DataGridView
        UpdateDataGridView();
    }

    delete deleteForm;
}

System::Void DriversListForm::DeleteContextMenu_Click(System::Object^ sender, System::EventArgs^ e) {
    // Вызываем удаление через контекстное меню
    DeleteDriver_Click(sender, e);
}

System::Void DriversListForm::driversDataGridView_CellDoubleClick(System::Object^ sender, DataGridViewCellEventArgs^ e) {
    // При двойном клике на строке - удаляем водителя
    if (e->RowIndex >= 0 && e->RowIndex < driversDataGridView->Rows->Count) {
        // Выбираем строку
        driversDataGridView->Rows[e->RowIndex]->Selected = true;
        // Вызываем удаление
        DeleteDriver_Click(sender, e);
    }
}

System::Void DriversListForm::Refresh_Click(System::Object^ sender, System::EventArgs^ e) {
    UpdateDataGridView();
}

System::Void DriversListForm::Back_Click(System::Object^ sender, System::EventArgs^ e) {
    this->Close();
}