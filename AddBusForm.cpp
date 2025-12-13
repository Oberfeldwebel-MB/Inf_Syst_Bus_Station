// AddBusForm.cpp
#include "AddBusForm.h"

using namespace InfSystBusStation;
using namespace System::Windows::Forms;

System::Void AddBusForm::AddBusButton_Click(System::Object^ sender, System::EventArgs^ e) {
    try {
        // === 1. Проверка инициализации ===
        if (busList == nullptr) {
            MessageBox::Show("Ошибка: система хранения данных не инициализирована!",
                "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        // === 2. Получение данных из формы ===
        String^ brand = BrandBox->Text->Trim();
        String^ model = ModelBox->Text->Trim();
        String^ code = BusNumBox->Text->Trim();

        if (String::IsNullOrEmpty(code) || code->Contains("_")) {
            MessageBox::Show("Введите полный код автобуса в формате А/888/АА!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            BusNumBox->Focus();
            BusNumBox->SelectAll();
            return;
        }

        int placeCount;
        if (!Int32::TryParse(CountPlaceBox->Text, placeCount)) {
            MessageBox::Show("Количество мест должно быть целым числом!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            CountPlaceBox->Focus();
            CountPlaceBox->SelectAll();
            return;
        }

        String^ techCondition = TechSostBox->Text->Trim();
        String^ lastMaintenance = DateTOAddBox->Text->Trim();

        // === 3. Вызов метода BusList для добавления ===
        if (busList->InternalAddBus(brand, model, placeCount, code,
            techCondition, lastMaintenance)) {
            // Успешно добавлено
            MessageBox::Show("Автобус успешно добавлен в систему!", "Успех",
                MessageBoxButtons::OK, MessageBoxIcon::Information);

            // Очистка формы
            BrandBox->Clear();
            ModelBox->Clear();
            CountPlaceBox->Clear();
            BusNumBox->Clear();
            TechSostBox->Clear();
            DateTOAddBox->Clear();
            BrandBox->Focus();

            // Генерация события
            DataAdded(this, EventArgs::Empty);

            // Закрываем форму с результатом OK
            this->DialogResult = System::Windows::Forms::DialogResult::OK;
        }
    }
    catch (Exception^ ex) {
        MessageBox::Show("Ошибка: " + ex->Message, "Ошибка системы",
            MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}