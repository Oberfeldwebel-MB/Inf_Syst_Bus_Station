// DriverValidator.cpp
#include "DriverValidator.hpp"
#include "DriversList.hpp"

using namespace InfSystBusStation;
using namespace System;
using namespace System::Text::RegularExpressions;
// Добавляем это пространство имен для атрибута [Out]
using namespace System::Runtime::InteropServices;

// Обязательные методы
bool DriverValidator::Validate(Object^ item) {
    Driver^ driver = dynamic_cast<Driver^>(item);
    if (driver == nullptr) {
        _lastErrorMessage = "Неверный тип объекта! Ожидался Driver.";
        return false;
    }

    String^ error;
    bool isValid = ValidateDriver(driver, error);
    if (!isValid) {
        _lastErrorMessage = error;
    }
    return isValid;
}

bool DriverValidator::ValidateForAddition(Object^ item, Object^ container) {
    Driver^ driver = dynamic_cast<Driver^>(item);
    DriversList^ driversList = dynamic_cast<DriversList^>(container);

    if (driver == nullptr) {
        _lastErrorMessage = "Неверный тип объекта! Ожидался Driver.";
        return false;
    }
    if (driversList == nullptr) {
        _lastErrorMessage = "Неверный тип контейнера! Ожидался DriversList.";
        return false;
    }

    // Сначала валидируем самого водителя
    String^ error;
    if (!ValidateDriver(driver, error)) {
        _lastErrorMessage = error;
        return false;
    }

    // Проверка уникальности ФИО
    for each (Driver ^ existingDriver in driversList->AllDrivers) {
        if (existingDriver->GetFullName() == driver->GetFullName()) {
            _lastErrorMessage = "Водитель с таким ФИО уже существует!";
            return false;
        }
    }

    // Проверка уникальности прав
    for each (Driver ^ existingDriver in driversList->AllDrivers) {
        if (existingDriver->GetLicense() == driver->GetLicense()) {
            _lastErrorMessage = "Водитель с таким номером прав уже существует!";
            return false;
        }
    }

    _lastErrorMessage = "";
    return true;
}

// Специфичные методы
bool DriverValidator::ValidateFIO(String^ fio, [Out] String^% errorMessage) {
    // Если fio приходит из MaskedTextBox, просто проверяем длину
    if (String::IsNullOrEmpty(fio)) {
        errorMessage = "ФИО не может быть пустым!";
        return false;
    }

    // Проверяем, что маска заполнена (нет символов '_')
    if (fio->Contains("_")) {
        errorMessage = "Заполните ФИО полностью!";
        return false;
    }

    // Дополнительно: минимальная длина (например, "Иванов И.И." - 10 символов)
    if (fio->Length < 5) {
        errorMessage = "ФИО слишком короткое!";
        return false;
    }

    errorMessage = "";
    return true;
}

bool DriverValidator::ValidateSalary(int salary, [Out] String^% errorMessage) {
    return ValidateInt(salary, "Зарплата", 10000, 500000, errorMessage);
}

bool DriverValidator::ValidateGender(String^ gender, [Out] String^% errorMessage) {
    if (String::IsNullOrEmpty(gender)) {
        errorMessage = "Пол не может быть пустым!";
        return false;
    }

    if (gender != "М" && gender != "Ж") {
        errorMessage = "Пол должен быть 'М' или 'Ж'!";
        return false;
    }

    errorMessage = "";
    return true;
}

bool DriverValidator::ValidateLicense(String^ license, [Out] String^% errorMessage) {
    // Сначала проверяем длину
    if (!ValidateString(license, "Номер водительских прав", 8, 8, errorMessage)) {
        return false;
    }

    // Проверяем формат: 2 буквы + 6 цифр
    return ValidateRegex(license, "^[А-ЯA-Z]{2}\\d{6}$",
        "Неверный формат прав! Пример: АБ123456", errorMessage);
}

bool DriverValidator::ValidatePassport(String^ passport, [Out] String^% errorMessage) {
    if (String::IsNullOrEmpty(passport)) {
        errorMessage = "";
        return true;
    }

    // Убираем пробелы и другие разделители
    String^ cleanPassport = passport->Replace(".", "");

    Console::WriteLine("Паспорт после очистки: '{0}'", cleanPassport);
    Console::WriteLine("Длина: {0}", cleanPassport->Length);

    // Проверяем длину (4 цифры серии + 6 цифр номера)
    if (cleanPassport->Length != 10) {
        errorMessage = "Паспорт должен содержать 10 цифр (серия 4 + номер 6)!";
        return false;
    }

    // Проверяем, что все символы - цифры
    return ValidateRegex(cleanPassport, "^\\d{10}$",
        "Паспорт должен содержать только цифры! Пример: 4500123456", errorMessage);
}


bool DriverValidator::ValidateAllFields(
    String^ fio,
    int salary,
    String^ gender,
    String^ license,
    String^ passport,
    [Out] String^% errorMessage) {

    // Проверяем ФИО
    String^ fioError;
    if (!ValidateFIO(fio, fioError)) {
        errorMessage = fioError;
        return false;
    }

    // Проверяем зарплату
    String^ salaryError;
    if (!ValidateSalary(salary, salaryError)) {
        errorMessage = salaryError;
        return false;
    }

    // Проверяем пол
    String^ genderError;
    if (!ValidateGender(gender, genderError)) {
        errorMessage = genderError;
        return false;
    }

    // Проверяем права
    String^ licenseError;
    if (!ValidateLicense(license, licenseError)) {
        errorMessage = licenseError;
        return false;
    }

    // Проверяем паспорт (если передан)
    if (!String::IsNullOrEmpty(passport)) {
        String^ passportError;
        if (!ValidatePassport(passport, passportError)) {
            errorMessage = passportError;
            return false;
        }
    }

    errorMessage = "";
    return true;
}


// Статические методы
bool DriverValidator::ValidateAllFieldsStatic(
    String^ fio,
    int salary,
    String^ gender,
    String^ license,
    String^ passport,
    [Out] String^% errorMessage) {

    DriverValidator^ validator = gcnew DriverValidator();
    return validator->ValidateAllFields(fio, salary, gender, license, passport, errorMessage);
}

bool DriverValidator::ValidateFIOStatic(String^ fio, [Out] String^% errorMessage) {
    DriverValidator^ validator = gcnew DriverValidator();
    return validator->ValidateFIO(fio, errorMessage);
}

bool DriverValidator::ValidateSalaryStatic(int salary, [Out] String^% errorMessage) {
    DriverValidator^ validator = gcnew DriverValidator();
    return validator->ValidateSalary(salary, errorMessage);
}

bool DriverValidator::ValidateGenderStatic(String^ gender, [Out] String^% errorMessage) {
    DriverValidator^ validator = gcnew DriverValidator();
    return validator->ValidateGender(gender, errorMessage);
}

bool DriverValidator::ValidateLicenseStatic(String^ license, [Out] String^% errorMessage) {
    DriverValidator^ validator = gcnew DriverValidator();
    return validator->ValidateLicense(license, errorMessage);
}

bool DriverValidator::ValidatePassportStatic(String^ series, String^ number, [Out] String^% errorMessage) {
    DriverValidator^ validator = gcnew DriverValidator();
    return validator->ValidatePassport(series, number, errorMessage);
}

bool DriverValidator::ValidateDriverStatic(Driver^ driver, [Out] String^% errorMessage) {
    DriverValidator^ validator = gcnew DriverValidator();
    return validator->ValidateDriver(driver, errorMessage);
}

bool DriverValidator::ValidateForAdditionStatic(Driver^ driver, DriversList^ driversList, [Out] String^% errorMessage) {
    DriverValidator^ validator = gcnew DriverValidator();
    return validator->ValidateForAddition(driver, driversList);
}