#include "BusValidator.h"
#include <regex>

using namespace InfSystBusStation;
using namespace System;
using namespace System::Text::RegularExpressions;

BusValidator::ValidationResult BusValidator::ValidateBrand(String^ brand) {
    if (String::IsNullOrEmpty(brand)) {
        return ValidationResult::Error("Марка автобуса не может быть пустой!");
    }

    if (brand->Length < 2) {
        return ValidationResult::Error("Марка автобуса слишком короткая!");
    }

    if (brand->Length > 50) {
        return ValidationResult::Error("Марка автобуса слишком длинная!");
    }

    return ValidationResult::Success();
}

BusValidator::ValidationResult BusValidator::ValidateModel(String^ model) {
    if (String::IsNullOrEmpty(model)) {
        return ValidationResult::Error("Модель автобуса не может быть пустой!");
    }

    if (model->Length < 1) {
        return ValidationResult::Error("Модель автобуса слишком короткая!");
    }

    if (model->Length > 50) {
        return ValidationResult::Error("Модель автобуса слишком длинная!");
    }

    return ValidationResult::Success();
}

BusValidator::ValidationResult BusValidator::ValidatePlaceCount(int placeCount) {
    if (placeCount <= 0) {
        return ValidationResult::Error("Количество мест должно быть больше 0!");
    }

    if (placeCount > 200) {
        return ValidationResult::Error("Количество мест не может быть больше 200!");
    }

    return ValidationResult::Success();
}

BusValidator::ValidationResult BusValidator::ValidateCode(String^ code) {
    if (String::IsNullOrEmpty(code)) {
        return ValidationResult::Error("Код автобуса не может быть пустым!");
    }

    // Формат кода: буква + 3 цифры + 2 буквы (например: А888АА)
    if (code->Length != 6) {
        return ValidationResult::Error("Код должен содержать 6 символов (например: А888АА)!");
    }

    // Проверяем формат: буква + 3 цифры + 2 буквы
    Regex^ pattern = gcnew Regex("^[А-ЯA-Z]\\d{3}[А-ЯA-Z]{2}$");
    if (!pattern->IsMatch(code)) {
        return ValidationResult::Error(
            "Неверный формат кода! Должен быть: буква/3 цифры/2 буквы\n" +
            "Пример: А888АА, В123МН, С456ОР");
    }

    return ValidationResult::Success();
}

BusValidator::ValidationResult BusValidator::ValidateTechCondition(String^ condition) {
    if (String::IsNullOrEmpty(condition)) {
        return ValidationResult::Error("Техническое состояние не может быть пустым!");
    }

    // Допустимые состояния
    array<String^>^ validConditions = {
        "Отличное", "Хорошее", "Удовлетворительное",
        "Неудовлетворительное", "Плохое", "Аварийное",
        "На обслуживании"
    };

    for each (String ^ validCondition in validConditions) {
        if (condition == validCondition) {
            return ValidationResult::Success();
        }
    }

    return ValidationResult::Error(
        "Недопустимое техническое состояние! Допустимые значения: " +
        "Отличное, Хорошее, Удовлетворительное, Неудовлетворительное, " +
        "Плохое, Аварийное, На обслуживании");
}

BusValidator::ValidationResult BusValidator::ValidateMaintenanceDate(String^ date) {
    if (String::IsNullOrEmpty(date)) {
        return ValidationResult::Success(); // Необязательное поле
    }

    // Проверяем формат даты DD/MM/YYYY
    Regex^ pattern = gcnew Regex("^\\d{2}/\\d{2}/\\d{4}$");

    if (!pattern->IsMatch(date)) {
        return ValidationResult::Error("Неверный формат даты! Используйте DD/MM/YYYY");
    }

    // Проверяем корректность даты
    try {
        DateTime maintenanceDate = DateTime::ParseExact(date, "dd/MM/yyyy",
            System::Globalization::CultureInfo::InvariantCulture);

        if (maintenanceDate > DateTime::Now) {
            return ValidationResult::Error("Дата ТО не может быть в будущем!");
        }
    }
    catch (Exception^) {
        return ValidationResult::Error("Некорректная дата! Пример: 15/03/2023");
    }

    return ValidationResult::Success();
}

BusValidator::ValidationResult BusValidator::ValidateBus(Bus^ bus) {
    // Проверяем все поля
    auto brandResult = ValidateBrand(bus->GetBrand());
    if (!brandResult.isValid) return brandResult;

    auto modelResult = ValidateModel(bus->GetModel());
    if (!modelResult.isValid) return modelResult;

    auto placeResult = ValidatePlaceCount(bus->GetPlaceCount());
    if (!placeResult.isValid) return placeResult;

    auto codeResult = ValidateCode(bus->GetCode());
    if (!codeResult.isValid) return codeResult;

    auto conditionResult = ValidateTechCondition(bus->GetTechCondition());
    if (!conditionResult.isValid) return conditionResult;

    auto dateResult = ValidateMaintenanceDate(bus->GetLastMaintenance());
    if (!dateResult.isValid) return dateResult;

    return ValidationResult::Success();
}


