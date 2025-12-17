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
    return ValidateString(fio, "ФИО водителя", 5, 100, errorMessage);
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

bool DriverValidator::ValidatePassport(String^ series, String^ number, [Out] String^% errorMessage) {
    // Если ничего не введено - это нормально (необязательное поле)
    if (String::IsNullOrEmpty(series) && String::IsNullOrEmpty(number)) {
        errorMessage = "";
        return true;
    }

    // Проверка серии (4 цифры)
    if (!String::IsNullOrEmpty(series)) {
        if (!ValidateRegex(series, "^\\d{4}$",
            "Серия паспорта должна содержать 4 цифры!", errorMessage)) {
            return false;
        }
    }

    // Проверка номера (6 цифр)
    if (!String::IsNullOrEmpty(number)) {
        if (!ValidateRegex(number, "^\\d{6}$",
            "Номер паспорта должен содержать 6 цифр!", errorMessage)) {
            return false;
        }
    }

    errorMessage = "";
    return true;
}

bool DriverValidator::ValidateDriver(Driver^ driver, [Out] String^% errorMessage) {
    if (driver == nullptr) {
        errorMessage = "Водитель не указан!";
        return false;
    }

    // Проверяем все обязательные поля
    String^ fioError, ^ salaryError, ^ genderError, ^ licenseError;

    bool isValid =
        ValidateFIO(driver->GetFullName(), fioError) &&
        ValidateSalary(driver->GetSalary(), salaryError) &&
        ValidateGender(driver->GetGender(), genderError) &&
        ValidateLicense(driver->GetLicense(), licenseError);

    if (!isValid) {
        // Возвращаем первую найденную ошибку
        if (!String::IsNullOrEmpty(fioError)) errorMessage = fioError;
        else if (!String::IsNullOrEmpty(salaryError)) errorMessage = salaryError;
        else if (!String::IsNullOrEmpty(genderError)) errorMessage = genderError;
        else if (!String::IsNullOrEmpty(licenseError)) errorMessage = licenseError;

        return false;
    }

    // Проверка паспорта (необязательное поле)
    String^ passportError;
    if (!ValidatePassport(driver->GetPassportSeries(), driver->GetPassportNumber(), passportError)) {
        errorMessage = passportError;
        return false;
    }

    errorMessage = "";
    return true;
}

// Статические методы
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