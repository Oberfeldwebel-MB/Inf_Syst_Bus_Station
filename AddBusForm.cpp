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

        // Проверяем заполненность маски
        if (!BusNumBox->MaskCompleted) {
            MessageBox::Show("Введите полный код автобуса в формате А/888/АА!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            BusNumBox->Focus();
            BusNumBox->SelectAll();
            return;
        }

       
        String^ codeForValidation = code->Replace("/", "");

        // === 3. Проверка числовые поля ===
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

        // === 4. Создаем Bus через конструктор и сразу валидируем ===
        try {
            // Создаем объект Bus 
            Bus^ tempBus = gcnew Bus(brand, model, placeCount,
                codeForValidation, techCondition,
                lastMaintenance);

            // Валидируем весь объект
            String^ validationError;
            if (!BusValidator::ValidateBusStatic(tempBus, validationError)) {
                MessageBox::Show("Ошибка валидации: " + validationError, "Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }

            String^ additionError;
            if (!BusValidator::ValidateForAdditionStatic(tempBus, busList, additionError)) {
                MessageBox::Show("Ошибка: " + additionError, "Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Warning);
                BusNumBox->Focus();
                BusNumBox->SelectAll();
                return;
            }

            // === 5. Вызов метода BusList для добавления ===
            // (Если InternalAddBus принимает Bus^ объект, а не отдельные поля)
            if (busList->InternalAddBus(brand, model, placeCount, codeForValidation,
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
        catch (ArgumentException^ ex) {
            // Ловим исключения из конструктора Bus
            MessageBox::Show("Ошибка данных: " + ex->Message, "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
        }
    }
    
    catch (Exception^ ex) {
        MessageBox::Show("Ошибка: " + ex->Message, "Ошибка системы",
            MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}