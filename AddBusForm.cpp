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

        // Марка
        String^ brand = BrandBox->Text->Trim();
        if (String::IsNullOrEmpty(brand)) {
            MessageBox::Show("Введите марку автобуса!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            BrandBox->Focus();
            BrandBox->SelectAll();
            return;
        }

        // Модель
        String^ model = ModelBox->Text->Trim();
        if (String::IsNullOrEmpty(model)) {
            MessageBox::Show("Введите модель автобуса!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            ModelBox->Focus();
            ModelBox->SelectAll();
            return;
        }

        // Код автобуса (из маскированного поля)
        String^ code = BusNumBox->Text->Trim();
        if (String::IsNullOrEmpty(code) || code->Contains("_")) {
            MessageBox::Show("Введите полный код автобуса в формате А/888/АА!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            BusNumBox->Focus();
            BusNumBox->SelectAll();
            return;
        }

        // Убираем символ '/' для хранения
        String^ codeWithoutSlash = code->Replace("/", "");

        // Количество мест
        if (String::IsNullOrEmpty(CountPlaceBox->Text)) {
            MessageBox::Show("Введите количество мест!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            CountPlaceBox->Focus();
            CountPlaceBox->SelectAll();
            return;
        }

        int placeCount;
        try {
            placeCount = Int32::Parse(CountPlaceBox->Text);
        }
        catch (Exception^) {
            MessageBox::Show("Количество мест должно быть целым числом!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            CountPlaceBox->Focus();
            CountPlaceBox->SelectAll();
            return;
        }

        // Техническое состояние
        String^ techCondition = TechSostBox->Text->Trim();
        if (String::IsNullOrEmpty(techCondition)) {
            MessageBox::Show("Введите техническое состояние!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            TechSostBox->Focus();
            TechSostBox->SelectAll();
            return;
        }

        // Дата последнего ТО (необязательное поле)
        String^ lastMaintenance = DateTOAddBox->Text->Trim();

        // === 3. ВАЛИДАЦИЯ ДАННЫХ ===

        // Валидация марки
        auto brandValidation = BusValidator::ValidateBrand(brand);
        if (!brandValidation.isValid) {
            MessageBox::Show(brandValidation.errorMessage, "Ошибка валидации",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            BrandBox->Focus();
            BrandBox->SelectAll();
            return;
        }

        // Валидация модели
        auto modelValidation = BusValidator::ValidateModel(model);
        if (!modelValidation.isValid) {
            MessageBox::Show(modelValidation.errorMessage, "Ошибка валидации",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            ModelBox->Focus();
            ModelBox->SelectAll();
            return;
        }

        // Валидация кода (используем код без '/')
        auto codeValidation = BusValidator::ValidateCode(codeWithoutSlash);
        if (!codeValidation.isValid) {
            MessageBox::Show(codeValidation.errorMessage, "Ошибка валидации",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            BusNumBox->Focus();
            BusNumBox->SelectAll();
            return;
        }

        // Валидация количества мест
        auto placeValidation = BusValidator::ValidatePlaceCount(placeCount);
        if (!placeValidation.isValid) {
            MessageBox::Show(placeValidation.errorMessage, "Ошибка валидации",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            CountPlaceBox->Focus();
            CountPlaceBox->SelectAll();
            return;
        }

        // Валидация технического состояния
        auto conditionValidation = BusValidator::ValidateTechCondition(techCondition);
        if (!conditionValidation.isValid) {
            MessageBox::Show(conditionValidation.errorMessage, "Ошибка валидации",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            TechSostBox->Focus();
            TechSostBox->SelectAll();
            return;
        }

        // Валидация даты ТО
        auto dateValidation = BusValidator::ValidateMaintenanceDate(lastMaintenance);
        if (!dateValidation.isValid) {
            MessageBox::Show(dateValidation.errorMessage, "Ошибка валидации",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            DateTOAddBox->Focus();
            DateTOAddBox->SelectAll();
            return;
        }

        // === 4. Проверка существующего автобуса ===
        // Проверяем по коду без '/'
        Bus^ existingBus = busList->FindBusByCode(codeWithoutSlash);
        if (existingBus != nullptr) {
            MessageBox::Show("Автобус с кодом '" + code + "' уже существует в системе!",
                "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            BusNumBox->Focus();
            BusNumBox->SelectAll();
            return;
        }

        // === 5. Создание автобуса ===
        // Храним код без '/' для удобства поиска
        Bus^ newBus = gcnew Bus(brand, model, placeCount, codeWithoutSlash,
            techCondition, lastMaintenance);

        // Полная валидация
        auto fullValidation = BusValidator::ValidateBus(newBus);
        if (!fullValidation.isValid) {
            MessageBox::Show(fullValidation.errorMessage, "Ошибка валидации",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }

        // === 6. Добавление автобуса в систему ===
        try {
            busList->AddBus(newBus);

            // === 7. Сообщение об успехе ===
            MessageBox::Show(
                "Автобус успешно добавлен в систему!\n\n" +
                "Марка: " + brand + "\n" +
                "Модель: " + model + "\n" +
                "Код: " + code + "\n" +
                "Мест: " + placeCount + "\n" +
                "Состояние: " + techCondition,
                "Успешно добавлено",
                MessageBoxButtons::OK,
                MessageBoxIcon::Information
            );

            // === 8. Очистка формы ===
            BrandBox->Clear();
            ModelBox->Clear();
            CountPlaceBox->Clear();
            BusNumBox->Clear();
            TechSostBox->Clear();
            DateTOAddBox->Clear();

            // Фокус на первое поле
            BrandBox->Focus();

            // === 9. Генерация события ===
            DataAdded(this, EventArgs::Empty);
        }
        catch (Exception^ ex) {
            MessageBox::Show(
                "Ошибка при добавлении автобуса: " + ex->Message,
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