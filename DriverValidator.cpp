#include "DriverValidator.hpp"

using namespace InfSystBusStation;
using namespace System::Text::RegularExpressions;

DriverValidator::ValidationResult DriverValidator::ValidateFIO(String^ fio) {
    if (String::IsNullOrEmpty(fio)) {
        return ValidationResult::Error("ФИО не может быть пустым!");
    }

    if (fio->Length < 5) {
        return ValidationResult::Error("ФИО слишком короткое (минимум 5 символов)!");
    }

    if (fio->Length > 100) {
        return ValidationResult::Error("ФИО слишком длинное (максимум 100 символов)!");
    }

    return ValidationResult::Success();
}

DriverValidator::ValidationResult DriverValidator::ValidateSalary(int salary) {
    if (salary < 10000) {
        return ValidationResult::Error("Зарплата не может быть меньше 10000 руб.!");
    }

    if (salary > 500000) {
        return ValidationResult::Error("Зарплата не может быть больше 500000 руб.!");
    }

    return ValidationResult::Success();
}

DriverValidator::ValidationResult DriverValidator::ValidateGender(String^ gender) {
    if (gender != "М" && gender != "Ж") {
        return ValidationResult::Error("Пол должен быть 'М' или 'Ж'!");
    }

    return ValidationResult::Success();
}

DriverValidator::ValidationResult DriverValidator::ValidateLicense(String^ license) {
    if (String::IsNullOrEmpty(license)) {
        return ValidationResult::Error("Номер водительских прав не может быть пустым!");
    }

    // Проверка формата: 2 буквы + 6 цифр
    Regex^ pattern = gcnew Regex("^[А-ЯA-Z]{2}\\d{6}$");
    if (!pattern->IsMatch(license)) {
        return ValidationResult::Error("Неверный формат прав! Пример: АБ123456");
    }

    return ValidationResult::Success();
}

DriverValidator::ValidationResult DriverValidator::ValidatePassport(String^ series, String^ number) {
    // Если ничего не введено - это нормально (необязательное поле)
    if (String::IsNullOrEmpty(series) && String::IsNullOrEmpty(number)) {
        return ValidationResult::Success();
    }

    // Проверка серии (4 цифры)
    Regex^ seriesPattern = gcnew Regex("^\\d{4}$");
    if (!seriesPattern->IsMatch(series)) {
        return ValidationResult::Error("Серия паспорта должна содержать 4 цифры!");
    }

    // Проверка номера (6 цифр)
    Regex^ numberPattern = gcnew Regex("^\\d{6}$");
    if (!numberPattern->IsMatch(number)) {
        return ValidationResult::Error("Номер паспорта должен содержать 6 цифр!");
    }

    return ValidationResult::Success();
}

bool DriverValidator::IsDuplicateLicense(String^ license, DriversList^ driversList) {
    for each (Driver ^ driver in driversList->AllDrivers) {
        if (driver->GetLicense() == license) {
            return true;
        }
    }
    return false;
}

bool DriverValidator::IsDuplicateName(String^ name, DriversList^ driversList) {
    for each (Driver ^ driver in driversList->AllDrivers) {
        if (driver->GetFullName() == name) {
            return true;
        }
    }
    return false;
}

DriverValidator::ValidationResult DriverValidator::ValidateDriver(Driver^ driver) {
    // Проверка ФИО
    auto fioResult = ValidateFIO(driver->GetFullName());
    if (!fioResult.isValid) return fioResult;

    // Проверка зарплаты
    auto salaryResult = ValidateSalary(driver->GetSalary());
    if (!salaryResult.isValid) return salaryResult;

    // Проверка прав
    auto licenseResult = ValidateLicense(driver->GetLicense());
    if (!licenseResult.isValid) return licenseResult;

    // Проверка пола
    auto genderResult = ValidateGender(driver->GetGender());
    if (!genderResult.isValid) return genderResult;

    return ValidationResult::Success();
}

DriverValidator::ValidationResult DriverValidator::ValidateForAddition(Driver^ driver, DriversList^ driversList) {
    // Сначала базовые проверки
    auto basicValidation = ValidateDriver(driver);
    if (!basicValidation.isValid) return basicValidation;

    // Проверка уникальности ФИО
    if (IsDuplicateName(driver->GetFullName(), driversList)) {
        return ValidationResult::Error("Водитель с таким ФИО уже существует!");
    }

    // Проверка уникальности прав
    if (IsDuplicateLicense(driver->GetLicense(), driversList)) {
        return ValidationResult::Error("Водитель с таким номером прав уже существует!");
    }

    return ValidationResult::Success();
}

