// BusValidator.cpp
#include "BusValidator.hpp"
#include <regex>

using namespace InfSystBusStation;
using namespace System;
using namespace System::Text::RegularExpressions;
// Добавляем это пространство имен для атрибута [Out]
using namespace System::Runtime::InteropServices;

// Обязательные методы
bool BusValidator::Validate(Object^ item) {
    Bus^ bus = dynamic_cast<Bus^>(item);
    if (bus == nullptr) {
        _lastErrorMessage = "Неверный тип объекта! Ожидался Bus.";
        return false;
    }

    String^ error;
    bool isValid = ValidateBus(bus, error);
    if (!isValid) {
        _lastErrorMessage = error;
    }
    return isValid;
}

bool BusValidator::ValidateForAddition(Object^ item, Object^ container) {
    Bus^ bus = dynamic_cast<Bus^>(item);
    BusList^ busList = dynamic_cast<BusList^>(container);

    if (bus == nullptr) {
        _lastErrorMessage = "Неверный тип объекта! Ожидался Bus.";
        return false;
    }
    if (busList == nullptr) {
        _lastErrorMessage = "Неверный тип контейнера! Ожидался BusList.";
        return false;
    }

    // Сначала валидируем сам автобус
    String^ error;
    if (!ValidateBus(bus, error)) {
        _lastErrorMessage = error;
        return false;
    }

    // Проверка уникальности кода
    for each (Bus ^ existingBus in busList->AllBuses) {
        if (existingBus->GetCode() == bus->GetCode()) {
            _lastErrorMessage = "Автобус с таким кодом уже существует!";
            return false;
        }
    }

    _lastErrorMessage = "";
    return true;
}

// Специфичные методы
bool BusValidator::ValidateBrand(String^ brand, [Out] String^% errorMessage) {
    return ValidateString(brand, "Марка автобуса", 2, 50, errorMessage);
}

bool BusValidator::ValidateModel(String^ model, [Out] String^% errorMessage) {
    return ValidateString(model, "Модель автобуса", 1, 50, errorMessage);
}

bool BusValidator::ValidatePlaceCount(int places, [Out] String^% errorMessage) {
    return ValidateInt(places, "Количество мест", 1, 200, errorMessage);
}

bool BusValidator::ValidateCode(String^ code, [Out] String^% errorMessage) {
    // Сначала базовая проверка длины
    if (!ValidateString(code, "Код автобуса", 6, 6, errorMessage)) {
        return false;
    }

    // Затем проверка формата
    return ValidateRegex(code, "^[А-ЯA-Z]\\d{3}[А-ЯA-Z]{2}$",
        "Неверный формат кода! Пример: А888АА, В123МН", errorMessage);
}

bool BusValidator::ValidateTechCondition(String^ condition, [Out] String^% errorMessage) {
    if (String::IsNullOrEmpty(condition)) {
        errorMessage = "Техническое состояние не может быть пустым!";
        return false;
    }

    array<String^>^ validConditions = {
        "Отличное", "Хорошее", "Удовлетворительное",
        "Неудовлетворительное", "Плохое", "Аварийное",
        "На обслуживании"
    };

    for each (String ^ validCondition in validConditions) {
        if (condition == validCondition) {
            errorMessage = "";
            return true;
        }
    }

    errorMessage = "Недопустимое техническое состояние! Допустимые значения: " +
        "Отличное, Хорошее, Удовлетворительное, Неудовлетворительное, " +
        "Плохое, Аварийное, На обслуживании";
    return false;
}

bool BusValidator::ValidateMaintenanceDate(String^ date, [Out] String^% errorMessage) {
    if (String::IsNullOrEmpty(date)) {
        errorMessage = ""; // Необязательное поле
        return true;
    }

    // Проверяем формат даты DD/MM/YYYY
    Regex^ pattern = gcnew Regex("^\\d{2}/\\d{2}/\\d{4}$");
    if (!pattern->IsMatch(date)) {
        errorMessage = "Неверный формат даты! Используйте DD/MM/YYYY";
        return false;
    }

    // Проверяем корректность даты
    try {
        DateTime maintenanceDate = DateTime::ParseExact(date, "dd/MM/yyyy",
            System::Globalization::CultureInfo::InvariantCulture);

        if (maintenanceDate > DateTime::Now) {
            errorMessage = "Дата ТО не может быть в будущем!";
            return false;
        }
    }
    catch (Exception^) {
        errorMessage = "Некорректная дата! Пример: 15/03/2023";
        return false;
    }

    errorMessage = "";
    return true;
}

bool BusValidator::ValidateBus(Bus^ bus, [Out] String^% errorMessage) {
    if (bus == nullptr) {
        errorMessage = "Автобус не указан!";
        return false;
    }

    // Проверяем все поля
    String^ brandError, ^ modelError, ^ placesError, ^ codeError, ^ conditionError, ^ dateError;

    bool isValid =
        ValidateBrand(bus->GetBrand(), brandError) &&
        ValidateModel(bus->GetModel(), modelError) &&
        ValidatePlaceCount(bus->GetSeatCount(), placesError) &&
        ValidateCode(bus->GetCode(), codeError) &&
        ValidateTechCondition(bus->GetTechCondition(), conditionError) &&
        ValidateMaintenanceDate(bus->GetLastMaintenance(), dateError);

    if (!isValid) {
        // Возвращаем первую найденную ошибку
        if (!String::IsNullOrEmpty(brandError)) errorMessage = brandError;
        else if (!String::IsNullOrEmpty(modelError)) errorMessage = modelError;
        else if (!String::IsNullOrEmpty(placesError)) errorMessage = placesError;
        else if (!String::IsNullOrEmpty(codeError)) errorMessage = codeError;
        else if (!String::IsNullOrEmpty(conditionError)) errorMessage = conditionError;
        else if (!String::IsNullOrEmpty(dateError)) errorMessage = dateError;

        return false;
    }

    errorMessage = "";
    return true;
}

// Статические методы (просто вызывают методы экземпляра)
bool BusValidator::ValidateBrandStatic(String^ brand, [Out] String^% errorMessage) {
    BusValidator^ validator = gcnew BusValidator();
    return validator->ValidateBrand(brand, errorMessage);
}

bool BusValidator::ValidateModelStatic(String^ model, [Out] String^% errorMessage) {
    BusValidator^ validator = gcnew BusValidator();
    return validator->ValidateModel(model, errorMessage);
}

bool BusValidator::ValidateCodeStatic(String^ code, [Out] String^% errorMessage) {
    BusValidator^ validator = gcnew BusValidator();
    return validator->ValidateCode(code, errorMessage);
}

bool BusValidator::ValidatePlaceCountStatic(int places, [Out] String^% errorMessage) {
    BusValidator^ validator = gcnew BusValidator();
    return validator->ValidatePlaceCount(places, errorMessage);
}

bool BusValidator::ValidateTechConditionStatic(String^ condition, [Out] String^% errorMessage) {
    BusValidator^ validator = gcnew BusValidator();
    return validator->ValidateTechCondition(condition, errorMessage);
}

bool BusValidator::ValidateMaintenanceDateStatic(String^ date, [Out] String^% errorMessage) {
    BusValidator^ validator = gcnew BusValidator();
    return validator->ValidateMaintenanceDate(date, errorMessage);
}

bool BusValidator::ValidateBusStatic(Bus^ bus, [Out] String^% errorMessage) {
    BusValidator^ validator = gcnew BusValidator();
    return validator->ValidateBus(bus, errorMessage);
}

bool BusValidator::ValidateForAdditionStatic(Bus^ bus, BusList^ busList, [Out] String^% errorMessage) {
    BusValidator^ validator = gcnew BusValidator();
    return validator->ValidateForAddition(bus, busList);
}