// DriverValidator.h
#pragma once
#include "Driver.hpp"
#include "DriversList.hpp"
#include <regex>

namespace InfSystBusStation {

    public ref class DriverValidator {
    public:
        // Структура для результата валидации
        value struct ValidationResult {
            bool isValid;
            String^ errorMessage;

            ValidationResult(bool valid, String^ msg)
                : isValid(valid), errorMessage(msg) {
            }

            static ValidationResult Success() {
                return ValidationResult(true, "");
            }

            static ValidationResult Error(String^ msg) {
                return ValidationResult(false, msg);
            }

            operator bool() { return isValid; }
        };

        // Валидация отдельного водителя
        static ValidationResult ValidateDriver(Driver^ driver);

        // Валидация перед добавлением в список
        static ValidationResult ValidateForAddition(Driver^ driver, DriversList^ driversList);

        // Валидация отдельных полей
        static ValidationResult ValidateFIO(String^ fio);
        static ValidationResult ValidateSalary(int salary);
        static ValidationResult ValidateGender(String^ gender);
        static ValidationResult ValidateLicense(String^ license);
        static ValidationResult ValidatePassport(String^ series, String^ number);

    private:
        // Вспомогательные методы
        static bool IsDuplicateLicense(String^ license, DriversList^ driversList);
        static bool IsDuplicateName(String^ name, DriversList^ driversList);
    };
}